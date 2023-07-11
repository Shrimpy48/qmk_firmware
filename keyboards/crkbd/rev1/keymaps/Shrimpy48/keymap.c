#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(KC_GRV, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT, KC_SLSH, KC_ESC, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_MINS, KC_TAB, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SCLN, KC_BSPC, KC_LCTL, MO(1), KC_SPC, KC_RSFT, MO(2), KC_RGUI),
	[1] = LAYOUT_split_3x6_3(KC_NO, KC_7, KC_5, KC_3, KC_1, KC_9, KC_8, KC_0, KC_2, KC_4, KC_6, KC_NO, KC_NO, OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), KC_PSCR, KC_ENT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, LSA(KC_TAB), LALT(KC_TAB), RCS(KC_TAB), RCTL(KC_TAB), KC_NO, KC_INS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT_split_3x6_3(KC_NO, KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, KC_PIPE, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV, KC_NO, KC_NO, KC_MINS, KC_ASTR, KC_EQL, KC_UNDS, KC_DLR, KC_NUHS, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), KC_NO, KC_NO, KC_PLUS, LSFT(KC_NUBS), KC_DQUO, KC_SLSH, KC_PERC, KC_HASH, KC_NUBS, KC_AMPR, KC_QUES, KC_EXLM, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT_split_3x6_3(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, RGB_SPI, RGB_SAI, RGB_HUI, RGB_VAI, RGB_TOG, RGB_MOD, KC_MNXT, KC_MPLY, KC_VOLU, OSM(MOD_LCTL), OSM(MOD_LALT), KC_BRIU, RGB_SPD, RGB_SAD, RGB_HUD, RGB_VAD, RGB_M_R, RGB_RMOD, KC_MPRV, KC_MUTE, KC_VOLD, OSM(MOD_LGUI), OSM(MOD_LSFT), KC_BRID, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(4)),
	[4] = LAYOUT_split_3x6_3(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC, KC_LALT, KC_SPC, KC_LBRC, KC_ENT, KC_RBRC, DF(0))
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

// OLED config
#ifdef OLED_ENABLE

// oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
//     if (!is_keyboard_master()) {
//         return OLED_ROTATION_180; // flips the display 180 degrees if offhand
//     }
//     return rotation;
// }

static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        case 4:
            oled_write_ln_P(PSTR("Gamer"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
}

static void oled_render_lock_state(void) {
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}

// char     key_name = ' ';
// uint16_t last_keycode;
// uint8_t  last_row;
// uint8_t  last_col;

// static const char PROGMEM code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

// static void set_keylog(uint16_t keycode, keyrecord_t *record) {
//     key_name     = ' ';
//     last_keycode = keycode;
//     if (IS_QK_MOD_TAP(keycode)) {
//         if (record->tap.count) {
//             keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
//         } else {
//             keycode = 0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10);
//         }
//     } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
//         keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
//     } else if (IS_QK_MODS(keycode)) {
//         keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
//     } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
//         keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
//     }
//     if (keycode > ARRAY_SIZE(code_to_name)) {
//         return;
//     }

//     // update keylog
//     key_name = pgm_read_byte(&code_to_name[keycode]);
//     last_row = record->event.key.row;
//     last_col = record->event.key.col;
// }

// static const char *depad_str(const char *depad_str, char depad_char) {
//     while (*depad_str == depad_char)
//         ++depad_str;
//     return depad_str;
// }

// static void oled_render_keylog(void) {
//     const char *last_row_str = get_u8_str(last_row, ' ');
//     oled_write(depad_str(last_row_str, ' '), false);
//     oled_write_P(PSTR("x"), false);
//     const char *last_col_str = get_u8_str(last_col, ' ');
//     oled_write(depad_str(last_col_str, ' '), false);
//     oled_write_P(PSTR(", k"), false);
//     const char *last_keycode_str = get_u16_str(last_keycode, ' ');
//     oled_write(depad_str(last_keycode_str, ' '), false);
//     oled_write_P(PSTR(":"), false);
//     oled_write_char(key_name, false);
// }

// static void render_bootmagic_status(bool status) {
//     /* Show Ctrl-Gui Swap options */
//     static const char PROGMEM logo[][2][3] = {
//         {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
//         {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
//     };
//     if (status) {
//         oled_write_ln_P(logo[0][0], false);
//         oled_write_ln_P(logo[0][1], false);
//     } else {
//         oled_write_ln_P(logo[1][0], false);
//         oled_write_ln_P(logo[1][1], false);
//     }
// }

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
        oled_render_lock_state();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
