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

use std::fmt::Write;

use steno_engine::common::Stroke;
use steno_engine::dictionary::numbers;
use steno_engine::dictionary::packed::Dictionary;
use steno_engine::engine::fixed;
use steno_engine::keycode::{Event, Keycode};

mod interface;

pub use interface::*;

extern "C" {
    fn send_string(string: *const std::ffi::c_char);

    fn register_code(kc: u8);
    fn unregister_code(kc: u8);
    fn tap_code(kc: u8);

    fn oled_write(data: *const std::ffi::c_char, invert: bool);
}

#[cfg(all(not(feature = "std"), not(test)))]
#[panic_handler]
fn panic_handler(panic_info: &std::panic::PanicInfo) -> ! {
    unsafe {
        let msg = std::ffi::CStr::from_bytes_with_nul(b"panic\n\0").unwrap_unchecked();
        send_string(msg.as_ptr());
    }
    let _ = write!(QmkOut::new(), "{panic_info}");
    loop {}
}

struct QmkOut {
    buf: [u8; 256],
}

impl QmkOut {
    fn new() -> Self {
        Self { buf: [0; 256] }
    }
}

impl std::fmt::Write for QmkOut {
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

impl fixed::Output for QmkOut {
    fn delete_n_last(&mut self, n: usize) -> std::fmt::Result {
        for _ in 0..n {
            unsafe { tap_code(Keycode::Backspace.into()) }
        }
        Ok(())
    }

    fn emit_keys<I>(&mut self, it: I) -> std::fmt::Result
    where
        I: IntoIterator<Item = steno_engine::keycode::Event>,
    {
        for event in it {
            unsafe {
                match event {
                    Event::Tap(key) => tap_code(key.into()),
                    Event::Press(key) => register_code(key.into()),
                    Event::Release(key) => unregister_code(key.into()),
                }
            }
        }
        Ok(())
    }
}

struct QmkOled {
    buf: [u8; 32],
}

impl QmkOled {
    fn new() -> Self {
        Self { buf: [0; 32] }
    }
}

impl std::fmt::Write for QmkOled {
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
            oled_write(c_str.as_ptr(), false);
        }
        Ok(())
    }
}

type Engine = fixed::Engine<
    (Dictionary<&'static [u8]>, numbers::Dictionary),
    [u8; ACT_BUF_LEN],
    [u8; OUT_BUF_LEN],
>;

const ACT_BUF_LEN: usize = 256;
const OUT_BUF_LEN: usize = 128;
static mut ENGINE: Option<Engine> = None;

fn build() -> Engine {
    let d = Dictionary::from_bytes(include_bytes!("../dict.in")).unwrap();
    let num = numbers::Dictionary::new();
    Engine::new((d, num), [0; ACT_BUF_LEN], [0; OUT_BUF_LEN])
}

pub(crate) fn take() -> Engine {
    unsafe { ENGINE.take() }.unwrap_or_else(build)
}

pub(crate) fn replace(e: Engine) {
    assert!(unsafe { ENGINE.replace(e) }.is_none())
}

pub(crate) fn engine_handle_stroke(stroke: Stroke) {
    let mut e = take();
    e.handle_stroke(stroke, QmkOut::new()).unwrap();
    replace(e);
}
