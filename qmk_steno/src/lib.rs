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

use queue::Queue;
use steno_engine::common::Stroke;
use steno_engine::dictionary::packed::{Dictionary, StaticDictionary};
use steno_engine::dictionary::{modifiers, numbers, symbols};
use steno_engine::engine::fixed;
use steno_engine::engine::fixed::Output;
use steno_engine::keycode::{keystrokes_to_type, Event, Keycode};

mod interface;
mod queue;

pub use interface::*;

extern "C" {
    // Not using because of crashing issues
    // fn register_code(kc: u8);
    // fn unregister_code(kc: u8);
    // fn tap_code(kc: u8);

    fn oled_write(data: *const std::ffi::c_char, invert: bool);

    // fn printf(fmt: *const std::ffi::c_char, ...) -> std::ffi::c_int;
}

#[cfg(all(not(feature = "std"), not(test)))]
#[panic_handler]
fn panic_handler(panic_info: &std::panic::PanicInfo) -> ! {
    let _ = writeln!(QmkOut::new(), "panic:\n{panic_info}");
    loop {}
}

const EVENT_DELAY_MS: u64 = 10;

struct WrapDebug<W> {
    inner: W,
}

impl<W> WrapDebug<W> {
    fn new(writer: W) -> Self {
        Self { inner: writer }
    }
}

impl<W: Write> Write for WrapDebug<W> {
    fn write_str(&mut self, s: &str) -> std::fmt::Result {
        write!(self.inner, "{:?}", s)
    }
}

impl<W: Write> Output for WrapDebug<W> {
    fn delete_n_last(&mut self, n: usize) -> std::fmt::Result {
        write!(self.inner, "del {n}")
    }

    fn emit_keys<I>(&mut self, it: I) -> std::fmt::Result
    where
        I: IntoIterator<Item = steno_engine::keycode::Event>,
    {
        for event in it {
            write!(self.inner, "emit {event:?}")?;
        }
        Ok(())
    }
}

struct QmkOut;

impl QmkOut {
    fn new() -> Self {
        Self
    }
}

impl Write for QmkOut {
    fn write_str(&mut self, s: &str) -> std::fmt::Result {
        self.emit_keys(keystrokes_to_type(s))
    }
}

impl Output for QmkOut {
    fn delete_n_last(&mut self, n: usize) -> std::fmt::Result {
        for _ in 0..n {
            // unsafe {
            //     tap_code(Keycode::Backspace.into());
            //     // wait_ms(EVENT_DELAY_MS);
            // }
            queue_push(Event::Tap(Keycode::Backspace));
        }
        Ok(())
    }

    fn emit_keys<I>(&mut self, it: I) -> std::fmt::Result
    where
        I: IntoIterator<Item = steno_engine::keycode::Event>,
    {
        for event in it {
            // unsafe {
            //     match event {
            //         Event::Tap(key) => tap_code(key.into()),
            //         Event::Press(key) => register_code(key.into()),
            //         Event::Release(key) => unregister_code(key.into()),
            //     }
            //     // wait_ms(EVENT_DELAY_MS);
            // }
            queue_push(event);
        }
        Ok(())
    }
}

struct QmkOled {
    buf: [u8; 16],
}

impl QmkOled {
    fn new() -> Self {
        Self { buf: [0; 16] }
    }
}

impl Write for QmkOled {
    fn write_str(&mut self, mut s: &str) -> std::fmt::Result {
        while !s.is_empty() {
            let chunk = if s.len() < self.buf.len() {
                s
            } else {
                let prefix = &s.as_bytes()[..self.buf.len() - 1];
                prefix.utf8_chunks().next().map(|c| c.valid()).unwrap_or("")
            };
            if chunk.is_empty() {
                return Err(std::fmt::Error);
            }
            s = &s[chunk.len()..];
            let dest = &mut self.buf[..chunk.len()];
            dest.copy_from_slice(chunk.as_bytes());
            self.buf[chunk.len()] = b'\0';
            let Ok(c_str) = std::ffi::CStr::from_bytes_with_nul(&self.buf[..=chunk.len()]) else {
                return Err(std::fmt::Error);
            };
            unsafe {
                oled_write(c_str.as_ptr(), false);
            }
        }
        Ok(())
    }
}

// struct QmkConsole {
//     buf: [u8; 64],
// }

// impl QmkConsole {
//     fn new() -> Self {
//         Self { buf: [0; 64] }
//     }
// }

// impl Write for QmkConsole {
//     fn write_str(&mut self, s: &str) -> std::fmt::Result {
//         if s.len() >= self.buf.len() {
//             return Err(std::fmt::Error);
//         }
//         let dest = &mut self.buf[..s.len()];
//         dest.copy_from_slice(s.as_bytes());
//         self.buf[s.len()] = 0;
//         let Ok(c_str) = std::ffi::CStr::from_bytes_with_nul(&self.buf[..=s.len()]) else {
//             return Err(std::fmt::Error);
//         };
//         unsafe {
//             printf(c_str.as_ptr());
//         }
//         Ok(())
//     }
// }

type Engine = fixed::Engine<
    (
        StaticDictionary,
        (
            numbers::Dictionary,
            symbols::DefDictionary,
            modifiers::DefDictionary,
        ),
    ),
    [u8; ACT_BUF_LEN],
    [u8; OUT_BUF_LEN],
>;

const ACT_BUF_LEN: usize = 64;
const OUT_BUF_LEN: usize = 64;
static mut ENGINE: Option<Engine> = None;

fn build() -> Engine {
    let d = Dictionary::from_bytes(include_bytes!("../dict.in")).unwrap();
    let num = numbers::Dictionary::default();
    let sym = symbols::Dictionary::default();
    let mods = modifiers::Dictionary::default();
    Engine::new((d, (num, sym, mods)), [0; ACT_BUF_LEN], [0; OUT_BUF_LEN])
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

static mut QUEUE: Option<Queue> = None;

pub(crate) fn take_queue() -> Queue {
    unsafe { QUEUE.take() }.unwrap_or_else(Queue::new)
}

pub(crate) fn replace_queue(q: Queue) {
    assert!(unsafe { QUEUE.replace(q) }.is_none())
}

pub(crate) fn queue_push(e: Event) {
    let mut q = take_queue();
    q.push(e);
    replace_queue(q);
}

pub(crate) fn queue_pop() -> Option<Event> {
    let mut q = take_queue();
    let out = q.pop();
    replace_queue(q);
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn asdf() {
        engine_handle_stroke(Stroke::H | Stroke::RL);
    }
}
