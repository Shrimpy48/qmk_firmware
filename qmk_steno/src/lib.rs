#![no_std]
#![crate_type = "staticlib"]

// We always pull in `std` during tests, because it's just easier
// to write tests when you can assume you're on a capable platform
#[cfg(any(feature = "std", test))]
#[macro_use]
extern crate std;

// When we're building for a no-std target, we pull in `core`, but alias
// it as `std` so the `use` statements are the same between `std` and `core`.
#[cfg(all(not(feature = "std"), not(test)))]
#[macro_use]
extern crate core as std;

mod interface;

use crate::std::fmt::Write;

pub use interface::*;

#[cfg(all(not(feature = "std"), not(test)))]
#[panic_handler]
fn panic_handler(panic_info: &std::panic::PanicInfo) -> ! {
    let msg = std::ffi::CStr::from_bytes_with_nul(b"panic\n\0").unwrap();
    unsafe {
        send_string(msg.as_ptr());
    }
    let _ = write!(SendString::new(), "{panic_info}");
    loop {}
}

struct SendString {
    buf: [u8; 128],
}

impl SendString {
    fn new() -> Self {
        Self { buf: [0; 128] }
    }
}

impl std::fmt::Write for SendString {
    fn write_str(&mut self, s: &str) -> std::fmt::Result {
        if s.len() >= self.buf.len() {
            return Err(std::fmt::Error);
        }
        let dest = &mut self.buf[..s.len()];
        dest.copy_from_slice(s.as_bytes());
        self.buf[s.len()] = 0;
        let Ok(c_str) = std::ffi::CStr::from_bytes_with_nul(&self.buf[..=s.len()]) else {
            return Err(std::fmt::Error);
        };
        unsafe {
            send_string(c_str.as_ptr());
        }
        Ok(())
    }
}

use steno_engine::dictionary::{Dictionary, PackedCommand, PackedStates};
use steno_engine::engine::fixed::Engine;
use steno_engine::keycode::{Event, Keycode::*};
use steno_engine::Stroke;

extern "C" {
    fn send_string(string: *const std::ffi::c_char);

    fn register_code(kc: u8);
    fn unregister_code(kc: u8);
    fn tap_code(kc: u8);
}

const DICT_NODES: &[u8] = include_bytes!("../nodes.in");
const DICT_TRANSLATIONS: &[u8] = include_bytes!("../translations.in");
const DICT_COMMANDS: &[PackedCommand] = &[PackedCommand {
    stroke: Stroke::STAR,
    packed_states: PackedStates { bitmap: 0 },
    keys_start: 0,
    keys_len: 0,
}];
const DICT_KEYS: &[Event] = &[];

pub(crate) const DICTIONARY: Dictionary<'static> =
    Dictionary::new(DICT_NODES, DICT_TRANSLATIONS, DICT_COMMANDS, DICT_KEYS);

const ACT_BUF_LEN: usize = 128;
const OUT_BUF_LEN: usize = 128;
pub(crate) static mut ENGINE: Option<Engine<ACT_BUF_LEN, OUT_BUF_LEN>> = None;

pub(crate) fn init() {
    let e = unsafe { &mut ENGINE };
    *e = Some(Engine::new(DICTIONARY));
}

pub(crate) fn handle_stroke(stroke: Stroke) {
    let e = unsafe { &ENGINE };
    if e.is_none() {
        init();
    }
    let e = unsafe { &mut ENGINE };
    let mut e = e.as_mut().unwrap().as_mut();
    let (n_delete, output_1, output_2) = e.handle(stroke);

    unsafe {
        for _ in 0..n_delete {
            tap_code(Backspace as u8);
        }
        send_string(output_1.as_ptr());
        if let Some(part2) = output_2 {
            send_string(part2.as_ptr());
        }
    }
}
