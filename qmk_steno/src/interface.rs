use steno_engine::Stroke;

use crate::handle_stroke;

#[no_mangle]
pub unsafe extern "C" fn handle_chord(geminipr_packet: *const u8) {
    handle_stroke(Stroke::from_geminipr(unsafe {
        *(geminipr_packet as *const [u8; 6])
    }))
}
