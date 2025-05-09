/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_uk.h"

// Left-hand home row mods
#define MOD_A LGUI_T(KC_A)
#define MOD_R LALT_T(KC_R)
#define MOD_S LSFT_T(KC_S)
#define MOD_T LCTL_T(KC_T)

// Right-hand home row mods
#define MOD_N RCTL_T(KC_N)
#define MOD_E RSFT_T(KC_E)
#define MOD_I LALT_T(KC_I)
#define MOD_O RGUI_T(KC_O)

enum layers {
    DEF,
    NUM,
    SYM,
    FUN,
    STN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS,   MOD_A,   MOD_R,   MOD_S,   MOD_T,    KC_G,                         KC_M,   MOD_N,   MOD_E,   MOD_I,   MOD_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UK_BSLS,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  QK_REP,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_ESC, MO(NUM),  KC_SPC,     KC_ENT, MO(SYM), CW_TOGG
                                      //`--------------------------'  `--------------------------'

  ),

    [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,   KC_P7,   KC_P8,   KC_P9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LEFT,   KC_UP, KC_DOWN,KC_RIGHT, XXXXXXX,                      XXXXXXX,   KC_P4,   KC_P5,   KC_P6, KC_PDOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,                      XXXXXXX,   KC_P1,   KC_P2,   KC_P3, XXXXXXX,  KC_NUM,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,  KC_SPC,     KC_ENT, MO(FUN),   KC_P0
                                      //`--------------------------'  `--------------------------'
  ),

    [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM, UK_DQUO,  UK_PND,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       UK_NOT, UK_TILD, KC_LCBR, KC_RCBR, KC_PLUS, KC_UNDS,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, UK_HASH,  UK_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       UK_GRV, UK_HASH, KC_LBRC, KC_RBRC,  KC_EQL, KC_MINS,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, UK_TILD,  UK_NOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, MO(FUN),  KC_SPC,     KC_ENT, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [FUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                      KC_MNXT, KC_MPLY, KC_VOLU, XXXXXXX, KC_PSCR,   DT_UP,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, TO(STN),                      KC_MPRV, KC_MUTE, KC_VOLD, XXXXXXX, DT_PRNT, DT_DOWN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,  KC_SPC,     KC_ENT, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [STN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,                       STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL, STN_ST1,                      STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      STN_PWR,  STN_S2,  STN_KL,  STN_WL,  STN_RL, STN_ST2,                      STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            STN_A,   STN_O,STN_RES1,   STN_RES2,   STN_E,   STN_U
                                      //`--------------------------'  `--------------------------'
  )
};

bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[MAX_STROKE_SIZE]) {
    // Only pwr
    const uint8_t EXIT_CHORD[MAX_STROKE_SIZE] = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b01000000,
        0b00000000,
        0b00000000
    };
    if (memcmp(chord, EXIT_CHORD, MAX_STROKE_SIZE) == 0) {
        layer_move(0);
        return false;
    }
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180; // flip the right display 180 degrees so they both face towards the user
    }
    return OLED_ROTATION_0;
}
#endif // OLED_ENABLE

static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case DEF:
            oled_write_ln_P(PSTR("Alpha"), false);
            break;
        case STN:
            oled_write_ln_P(PSTR("Steno"), false);
            break;
        case FUN:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        case NUM:
            oled_write_ln_P(PSTR("Number"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
            break;
    }
}

__attribute__((weak)) void oled_render_logo(void) {
    // clang-format off
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    // clang-format on
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        oled_render_logo();
    }
    return false;
}
