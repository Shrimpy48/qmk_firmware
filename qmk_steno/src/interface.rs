use crate::std::fmt::Write;

use steno_engine::common::Stroke;

use crate::{engine_handle_stroke, QmkOled};

#[no_mangle]
pub unsafe extern "C" fn translate_chord(geminipr_packet: *const u8) -> u32 {
    Stroke::from_geminipr(unsafe { *(geminipr_packet as *const [u8; 6]) }).into()
}

#[no_mangle]
pub extern "C" fn handle_stroke(stroke: u32, host_os: u8) {
    let stroke = Stroke::try_from(stroke).unwrap();
    engine_handle_stroke(stroke)
}

#[no_mangle]
pub extern "C" fn oled_write_stroke(stroke: u32) {
    write!(QmkOled::new(), "{}", Stroke::try_from(stroke).unwrap()).unwrap()
}
