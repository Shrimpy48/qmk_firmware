#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(KC_LGUI, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT, KC_ENT, KC_ESC, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_SLSH, KC_TAB, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SCLN, KC_BSPC, KC_LCTL, MO(1), KC_SPC, KC_RSFT, MO(2), KC_RGUI),
	[1] = LAYOUT_split_3x6_3(KC_NO, KC_7, KC_5, KC_3, KC_1, KC_9, KC_8, KC_0, KC_2, KC_4, KC_6, KC_NO, KC_NO, OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), KC_ENT, KC_ENT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, LSA(KC_TAB), LALT(KC_TAB), RCS(KC_TAB), RCTL(KC_TAB), KC_NO, KC_INS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT_split_3x6_3(KC_NO, KC_ENT, KC_LBRC, KC_LCBR, KC_LPRN, KC_PIPE, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV, KC_NO, KC_NO, KC_MINS, KC_ASTR, KC_EQL, KC_UNDS, KC_DLR, KC_NUHS, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), KC_NO, KC_NO, KC_PLUS, LSFT(KC_NUBS), KC_DQUO, KC_SLSH, KC_PERC, KC_HASH, KC_NUBS, KC_AMPR, KC_QUES, KC_EXLM, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT_split_3x6_3(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, RGB_SPI, RGB_SAI, RGB_HUI, RGB_VAI, RGB_TOG, RGB_MOD, KC_MNXT, KC_MPLY, KC_VOLU, OSM(MOD_LCTL), OSM(MOD_LALT), KC_BRIU, RGB_SPD, RGB_SAD, RGB_HUD, RGB_VAD, RGB_M_R, RGB_RMOD, KC_MPRV, KC_MUTE, KC_VOLD, OSM(MOD_LGUI), OSM(MOD_LSFT), KC_BRID, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

// shift-' = " like on US layout
const key_override_t quote_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, LSFT(KC_AT));

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &quote_key_override,
    NULL // Null terminate the array of overrides!
};

// Holding both layer keys puts you in layer 3
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 2, 3);
}
