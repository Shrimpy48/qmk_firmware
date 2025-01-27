use crate::{queue_pop, std::fmt::Write};

use steno_engine::common::Stroke;
use steno_engine::keycode::Event;

#[cfg(feature = "qmk")]
use crate::{engine_handle_stroke, QmkOled};

#[no_mangle]
pub unsafe extern "C" fn translate_chord(geminipr_packet: *const u8) -> u32 {
    Stroke::from_geminipr(unsafe { *(geminipr_packet as *const [u8; 6]) }).into()
}

#[cfg(feature = "qmk")]
#[no_mangle]
pub extern "C" fn handle_stroke(stroke: u32, host_os: u8) {
    let stroke = Stroke::try_from(stroke).unwrap();
    engine_handle_stroke(stroke)
}

#[cfg(feature = "qmk")]
#[no_mangle]
pub extern "C" fn oled_write_stroke(stroke: u32) {
    write!(QmkOled::new(), "{}", Stroke::try_from(stroke).unwrap()).unwrap()
}

#[repr(C)]
pub struct NextKey {
    mode: u8,
    key: u8,
}

#[no_mangle]
pub extern "C" fn get_next_key() -> NextKey {
    match queue_pop() {
        Some(Event::Tap(kc)) => NextKey {
            mode: 1,
            key: kc.into(),
        },
        Some(Event::Press(kc)) => NextKey {
            mode: 2,
            key: kc.into(),
        },
        Some(Event::Release(kc)) => NextKey {
            mode: 3,
            key: kc.into(),
        },
        None => NextKey { mode: 0, key: 0 },
    }
}
