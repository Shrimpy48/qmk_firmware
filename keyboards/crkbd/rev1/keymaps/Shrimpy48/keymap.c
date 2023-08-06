#include QMK_KEYBOARD_H

#include "transactions.h"

#include "oneshot.h"
#include "swapper.h"
#include "snek.h"

enum layers {
    DEFAULT,
    LOWER,
    RAISE,
    ADJUST,
    GAMER,
};

enum keycodes {
    // Callum's oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,

    SW_WIN,  // Switch to next window         (alt-tab)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[DEFAULT] = LAYOUT_split_3x6_3(
            KC_GRV , KC_Q   , KC_W         , KC_F       , KC_P        , KC_B    ,    KC_J   , KC_L     , KC_U       , KC_Y   , KC_QUOT, KC_MINS,
            KC_ESC , KC_A   , KC_R         , KC_S       , KC_T        , KC_G    ,    KC_M   , KC_N     , KC_E       , KC_I   , KC_O   , KC_BSPC,
            KC_TAB , KC_Z   , KC_X         , KC_C       , KC_D        , KC_V    ,    KC_K   , KC_H     , KC_COMM    , KC_DOT , KC_SCLN, KC_DEL ,
                                             SH_MON     , MO(LOWER)   , KC_SPC  ,    KC_RSFT, MO(RAISE), SH_MON
            ),
	[LOWER] = LAYOUT_split_3x6_3(
            KC_NO  , KC_7   , KC_5         , KC_3       , KC_1        , KC_9    ,    KC_8   , KC_0     , KC_2       , KC_4   , KC_6   , KC_NO  ,
            KC_NO  , OS_SHFT, OS_CTRL      , OS_ALT     , OS_GUI      , KC_PSCR ,    KC_ENT , KC_LEFT  , KC_DOWN    , KC_UP  , KC_RGHT, KC_NO  ,
            KC_NO  , KC_NO  , SW_WIN       , RCS(KC_TAB), RCTL(KC_TAB), KC_NO   ,    KC_TAB , KC_HOME  , KC_PGDN    , KC_PGUP, KC_END , KC_NO  ,
                                             KC_TRNS    , KC_TRNS     , KC_TRNS ,    KC_TRNS, KC_TRNS  , KC_TRNS
            ),
	[RAISE] = LAYOUT_split_3x6_3(
            KC_NO  , KC_ESC , KC_LBRC      , KC_LCBR    , KC_LPRN     , KC_PIPE ,    KC_CIRC, KC_RPRN  , KC_RCBR    , KC_RBRC, KC_GRV , KC_NO  ,
            KC_NO  , KC_MINS, KC_ASTR      , KC_EQL     , KC_UNDS     , KC_DLR  ,    KC_NUHS, OS_GUI   , OS_ALT     , OS_CTRL, OS_SHFT, KC_NO  ,
            KC_NO  , KC_PLUS, LSFT(KC_NUBS), KC_DQUO    , KC_SLSH     , KC_PERC ,    KC_HASH, KC_NUBS  , KC_AMPR    , KC_QUES, KC_EXLM, KC_NO  ,
                                             KC_TRNS    , KC_TRNS     , KC_TRNS ,    KC_TRNS, KC_TRNS  , KC_TRNS
            ),
	[ADJUST] = LAYOUT_split_3x6_3(
            KC_F1  , KC_F2  , KC_F3        , KC_F4      , KC_F5       , KC_F6   ,    KC_F7  , KC_F8    , KC_F9      , KC_F10 , KC_F11 , KC_F12 ,
            RGB_SPI, RGB_SAI, RGB_HUI      , RGB_VAI    , RGB_TOG     , RGB_MOD ,    KC_MNXT, KC_MPLY  , KC_VOLU    , OS_CTRL, OS_ALT , KC_BRIU,
            RGB_SPD, RGB_SAD, RGB_HUD      , RGB_VAD    , RGB_M_R     , RGB_RMOD,    KC_MPRV, KC_MUTE  , KC_VOLD    , OS_GUI , OS_SHFT, KC_BRID,
                                             KC_TRNS    , KC_TRNS     , KC_TRNS ,    KC_TRNS, KC_TRNS  , DF(GAMER)
            ),
	[GAMER] = LAYOUT_split_3x6_3(
            KC_TAB , KC_Q   , KC_W         , KC_E       , KC_R        , KC_T    ,    KC_Y   , KC_U     , KC_I       , KC_O   , KC_P   , KC_BSPC,
            KC_LSFT, KC_A   , KC_S         , KC_D       , KC_F        , KC_G    ,    KC_H   , KC_J     , KC_K       , KC_L   , KC_SCLN, KC_QUOT,
            KC_LCTL, KC_Z   , KC_X         , KC_C       , KC_V        , KC_B    ,    KC_N   , KC_M     , KC_COMM    , KC_DOT , KC_SLSH, KC_ESC ,
                                             KC_LALT    , KC_SPC      , KC_LBRC ,    KC_ENT , KC_RBRC  , DF(DEFAULT)
            )
};

// shift-' = " like on US layout
const key_override_t quote_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, LSFT(KC_AT));

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &quote_key_override,
    NULL // Null terminate the array of overrides!
};

// Holding both layer keys puts you in adjust layer
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LOWER, RAISE, ADJUST);
}

// Callum's oneshot and swapper implementation
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case MO(LOWER):
    case MO(RAISE):
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO(LOWER):
    case MO(RAISE):
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

void update_snek(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return;
    }
    switch (keycode) {
        case KC_LEFT:
            snake_state.snake_dir = left;
            break;
        case KC_DOWN:
            snake_state.snake_dir = down;
            break;
        case KC_RIGHT:
            snake_state.snake_dir = right;
            break;
        case KC_UP:
            snake_state.snake_dir = up;
            break;
    } 
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LGUI, OS_GUI,
        keycode, record
    );

    update_snek(keycode, record);

    return true;
}

void user_sync_snek_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const snake_state_t *m2s = (const snake_state_t*)in_data;
    snake_state = *m2s;
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_SNEK, user_sync_snek_slave_handler);
}

// Send current snek state to the slave side
// void housekeeping_task_user(void) {
//     if (is_keyboard_master()) {
//         // Interact with slave every 500ms
//         static uint32_t last_sync = 0;
//         if (timer_elapsed32(last_sync) > 500) {
//             snake_state_t m2s = snake_state;
//             if(transaction_rpc_send(USER_SYNC_SNEK, sizeof(m2s), &m2s)) {
//                 last_sync = timer_read32();
//             }
//         }
//     }
// }

// // Layer indicator
// bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     if (get_highest_layer(layer_state) > 0) {
//         uint8_t layer = get_highest_layer(layer_state);
//
//         for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
//             for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
//                 uint8_t index = g_led_config.matrix_co[row][col];
//
//                 if (index >= led_min && index < led_max && index != NO_LED &&
//                 keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
//                     rgb_matrix_set_color(index, RGB_GREEN);
//                 }
//             }
//         }
//     }
//     return false;
// }

// OLED config
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180; // flips the right display 180 degrees so they both face towards the user
    }
    return OLED_ROTATION_0;
}

static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
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

static void oled_render_osm_state(void) {
    switch (os_shft_state) {
        case os_up_unqueued:
            oled_write_P(PSTR("     "), false);
            break;
        case os_up_queued:
        case os_down_unused:
        case os_down_used:
            oled_write_P(PSTR("SHFT "), false);
            break;
    }
    switch (os_ctrl_state) {
        case os_up_unqueued:
            oled_write_P(PSTR("     "), false);
            break;
        case os_up_queued:
        case os_down_unused:
        case os_down_used:
            oled_write_P(PSTR("CTRL "), false);
            break;
    }
    switch (os_alt_state) {
        case os_up_unqueued:
            oled_write_P(PSTR("    "), false);
            break;
        case os_up_queued:
        case os_down_unused:
        case os_down_used:
            oled_write_P(PSTR("ALT "), false);
            break;
    }
    switch (os_cmd_state) {
        case os_up_unqueued:
            oled_write_P(PSTR("   "), false);
            break;
        case os_up_queued:
        case os_down_unused:
        case os_down_used:
            oled_write_P(PSTR("GUI"), false);
            break;
    }
}

// static void oled_render_lock_state(void) {
//     led_t led_state = host_keyboard_led_state();
//     oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
//     oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
//     oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
// }

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
        oled_render_osm_state();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
