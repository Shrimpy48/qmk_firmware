#include QMK_KEYBOARD_H


/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT, KC_BSPC, KC_NO, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_SLSH, KC_ESC, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SCLN, KC_ENT, KC_LGUI, MO(1), KC_SPC, OSM(MOD_LSFT), MO(2), KC_RCTL),
	[1] = LAYOUT_split_3x6_3(KC_TRNS, KC_TAB, KC_NO, RCS(KC_TAB), LCTL(KC_TAB), KC_VOLU, RGB_VAI, KC_HOME, KC_UP, KC_END, KC_DEL, KC_TRNS, KC_NO, OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), KC_VOLD, RGB_VAD, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, RGB_SPI, KC_TRNS, RGB_TOG, RGB_MOD, RGB_RMOD, KC_NO, KC_MPLY, KC_NO, KC_PGDN, KC_PGUP, KC_NO, KC_ENT, RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT_split_3x6_3(KC_TAB, KC_ESC, KC_LBRC, KC_LCBR, KC_LPRN, KC_PIPE, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV, KC_BSPC, KC_NO, KC_MINS, KC_ASTR, KC_EQL, KC_UNDS, KC_DLR, KC_NUHS, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), RGB_HUI, KC_LSFT, KC_PLUS, LSFT(KC_NUBS), KC_DQUO, KC_SLSH, KC_PERC, KC_NO, KC_NUBS, KC_AMPR, KC_QUES, KC_EXLM, RGB_HUD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT_split_3x6_3(KC_NO, KC_7, KC_5, KC_3, KC_1, KC_9, KC_8, KC_0, KC_2, KC_4, KC_6, KC_NO, KC_NO, OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), KC_F11, KC_F10, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), KC_NO, KC_NO, KC_F7, KC_F5, KC_F3, KC_F1, KC_F9, KC_F8, KC_F12, KC_F2, KC_F4, KC_F6, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

const key_override_t quote_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, LSFT(KC_AT));

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &quote_key_override,
    NULL // Null terminate the array of overrides!
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, 1, 2, 3);
}
