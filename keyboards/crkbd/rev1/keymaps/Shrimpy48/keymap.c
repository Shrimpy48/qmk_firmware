#include QMK_KEYBOARD_H

#include "keymap_uk.h"

#ifdef STENO_ENABLE
#include "keymap_steno.h"
#endif

#ifdef RGB_MATRIX_CUSTOM_USER
#include "transactions.h"
#include "snek.h"
#endif // RGB_MATRIX_CUSTOM_USER

// #include "oneshot.h"
// #include "swapper.h"

enum layers {
    DEF,
    SYM,
    NUM,
    FUN,
    GMR,
#ifdef STENO_ENABLE
    STN,
#endif
#ifdef MIDI_ENABLE
    MID,
#endif
};

// enum keycodes {
//     // Callum's oneshot mod implementation with no timers.
//     OS_SHFT = SAFE_RANGE,
//     OS_CTRL,
//     OS_ALT,
//     OS_GUI,

//     SW_WIN,  // Switch to next window         (alt-tab)
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[DEF] = LAYOUT_split_3x6_3(
            QK_REP , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B    ,    KC_J   , KC_L   , KC_U       , KC_Y        , KC_QUOT, QK_AREP,
            KC_ESC , KC_A   , KC_R   , KC_S   , KC_T   , KC_G    ,    KC_M   , KC_N   , KC_E       , KC_I        , KC_O   , KC_BSPC,
            KC_TAB , KC_Z   , KC_X   , KC_C   , KC_D   , KC_V    ,    KC_K   , KC_H   , KC_COMM    , KC_DOT      , KC_COLN, KC_ENT ,
                                       KC_WBAK, MO(SYM), KC_SPC  ,    KC_RSFT, MO(NUM), KC_WFWD
            ),
	[SYM] = LAYOUT_split_3x6_3(
            KC_TRNS, KC_ESC , KC_LBRC, KC_LCBR, KC_LPRN, UK_TILD ,    KC_CIRC, KC_RPRN, KC_RCBR    , KC_RBRC     , KC_BSPC, KC_TRNS,
            KC_TRNS, KC_PLUS, KC_AMPR, KC_QUES, KC_EXLM, KC_DLR  ,    UK_HASH, KC_UNDS, KC_EQL     , KC_ASTR     , KC_MINS, KC_TRNS,
            KC_TRNS, KC_TAB , UK_PIPE, UK_AT  , KC_SLSH, KC_PERC ,    KC_GRV , UK_BSLS, UK_LABK    , UK_RABK     , KC_ENT , KC_TRNS,
                                       KC_TRNS, KC_TRNS, KC_TRNS ,    KC_TRNS, KC_TRNS, KC_TRNS
            ),
	[NUM] = LAYOUT_split_3x6_3(
            KC_TRNS, KC_NO  , KC_7   , KC_8   , KC_9   , KC_ESC  ,    KC_BSPC, KC_NO  , RCS(KC_TAB), RCTL(KC_TAB), KC_NO  , KC_TRNS,
            KC_TRNS, KC_DOT , KC_4   , KC_5   , KC_6   , UK_PND  ,    KC_NO  , KC_LEFT, KC_DOWN    , KC_UP       , KC_RGHT, KC_TRNS,
            KC_TRNS, KC_0   , KC_1   , KC_2   , KC_3   , KC_TAB  ,    KC_ENT , KC_HOME, KC_PGDN    , KC_PGUP     , KC_END , KC_TRNS,
                                       KC_TRNS, KC_TRNS, KC_TRNS ,    KC_TRNS, KC_TRNS, KC_TRNS
            ),
	[FUN] = LAYOUT_split_3x6_3(
            KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6   ,    KC_F7  , KC_F8  , KC_F9      , KC_F10      , KC_F11 , KC_F12 ,
            RGB_SPI, RGB_SAI, RGB_HUI, RGB_VAI, RGB_TOG, RGB_MOD ,    KC_MNXT, KC_MPLY, KC_VOLU    , KC_PSCR     , KC_DEL , KC_BRIU,
            RGB_SPD, RGB_SAD, RGB_HUD, RGB_VAD, RGB_M_R, RGB_RMOD,    KC_MPRV, KC_MUTE, KC_VOLD    , KC_APP      , KC_INS , KC_BRID,
#ifdef STENO_ENABLE
                                       TG(STN), KC_TRNS, KC_TRNS ,    KC_TRNS, KC_TRNS, TG(GMR)
#elif MIDI_ENABLE
                                       TG(MID), KC_TRNS, KC_TRNS ,    KC_TRNS, KC_TRNS, TG(GMR)
#else
                                       KC_NO  , KC_TRNS, KC_TRNS ,    KC_TRNS, KC_TRNS, TG(GMR)
#endif
            ),
	[GMR] = LAYOUT_split_3x6_3(
            KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T    ,    KC_Y   , KC_U   , KC_I       , KC_O        , KC_P   , KC_ESC ,
            KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G    ,    KC_H   , KC_J   , KC_K       , KC_L        , KC_SCLN, KC_QUOT,
            KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B    ,    KC_N   , KC_M   , KC_COMM    , KC_DOT      , KC_SLSH, KC_BSPC,
                                       KC_LALT, KC_SPC , KC_LBRC ,    KC_ENT , KC_RBRC, TG(GMR)
            ),
#ifdef STENO_ENABLE
	[STN] = LAYOUT_split_3x6_3(
            STN_N1 , STN_N2 , STN_N3 , STN_N4 , STN_N5 , STN_N6  ,    STN_N7 , STN_N8 , STN_N9     , STN_NA      , STN_NB , STN_NC ,
            STN_FN , STN_S1 , STN_TL , STN_PL , STN_HL , STN_ST1 ,    STN_ST3, STN_FR , STN_PR     , STN_LR      , STN_TR , STN_DR ,
            KC_NO  , STN_S2 , STN_KL , STN_WL , STN_RL , STN_ST2 ,    STN_ST4, STN_RR , STN_BR     , STN_GR      , STN_SR , STN_ZR ,
                                       TG(STN), STN_A  , STN_O   ,    STN_E  , STN_U  , STN_PWR
            ),
#endif
#ifdef MIDI_ENABLE
	[MID] = LAYOUT_split_3x6_3(
            MI_C   , MI_Cs  , MI_D   , MI_Ds  , MI_E   , MI_F   ,    MI_Fs   , MI_G   , MI_Gs      , MI_A        , MI_As  , MI_B   ,
            MI_C   , MI_Cs  , MI_D   , MI_Ds  , MI_E   , MI_F   ,    MI_Fs   , MI_G   , MI_Gs      , MI_A        , MI_As  , MI_B   ,
            MI_C   , MI_Cs  , MI_D   , MI_Ds  , MI_E   , MI_F   ,    MI_Fs   , MI_G   , MI_Gs      , MI_A        , MI_As  , MI_B   ,
                                       TG(MID), KC_NO  , MI_SOFT,    MI_SUST , KC_NO  , KC_NO 
            ),
#endif
};

// shift-' = " like on US layout
const key_override_t quote_key_override = ko_make_basic(MOD_MASK_SHIFT, UK_QUOT, UK_DQUO);
// swapped ; and :
const key_override_t colon_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COLN, KC_SCLN);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &quote_key_override,
    &colon_key_override,
    NULL // Null terminate the array of overrides!
};

#ifdef COMBO_ENABLE
// Combo 2nd and 3rd row for modifiers
const uint16_t PROGMEM ls_combo[] = {KC_A, KC_Z, COMBO_END};
const uint16_t PROGMEM lc_combo[] = {KC_R, KC_X, COMBO_END};
const uint16_t PROGMEM la_combo[] = {KC_S, KC_C, COMBO_END};
const uint16_t PROGMEM lg_combo[] = {KC_T, KC_D, COMBO_END};
const uint16_t PROGMEM rg_combo[] = {KC_N, KC_H, COMBO_END};
const uint16_t PROGMEM ra_combo[] = {KC_E, KC_COMM, COMBO_END};
const uint16_t PROGMEM rc_combo[] = {KC_I, KC_DOT, COMBO_END};
const uint16_t PROGMEM rs_combo[] = {KC_O, KC_COLN, COMBO_END};
combo_t key_combos[] = {
    COMBO(ls_combo, KC_LSFT),
    COMBO(lc_combo, KC_LCTL),
    COMBO(la_combo, KC_LALT),
    COMBO(lg_combo, KC_LGUI),
    COMBO(rs_combo, KC_LSFT),
    COMBO(rc_combo, KC_LCTL),
    COMBO(ra_combo, KC_LALT),
    COMBO(rg_combo, KC_LGUI),
};
#endif // COMBO_ENABLE

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef COMBO_ENABLE
    // Disable combos on alternate layers
    switch (get_highest_layer(state)) {
#ifdef MIDI_ENABLE
    case MID:
#endif
#ifdef STENO_ENABLE
    case STN:
#endif
    case GMR:
        combo_disable();
        break;
    default: //  for any other layers, or the default layer
        combo_enable();
        break;
    }
#endif // COMBO_ENABLE

    // Holding both layer keys puts you in adjust layer
    return update_tri_layer_state(state, NUM, SYM, FUN);
}

// // Callum's oneshot and swapper implementation
// bool is_oneshot_cancel_key(uint16_t keycode) {
//     switch (keycode) {
//     case MO(NUM):
//     case MO(SYM):
//         return true;
//     default:
//         return false;
//     }
// }

// bool is_oneshot_ignored_key(uint16_t keycode) {
//     switch (keycode) {
//     case MO(NUM):
//     case MO(SYM):
//     case KC_LSFT:
//     case OS_SHFT:
//     case OS_CTRL:
//     case OS_ALT:
//     case OS_GUI:
//         return true;
//     default:
//         return false;
//     }
// }

// bool sw_win_active = false;

// oneshot_state os_shft_state = os_up_unqueued;
// oneshot_state os_ctrl_state = os_up_unqueued;
// oneshot_state os_alt_state = os_up_unqueued;
// oneshot_state os_cmd_state = os_up_unqueued;

#ifdef RGB_MATRIX_ENABLE

#ifdef RGB_MATRIX_CUSTOM_USER

coord_t matrix_to_snake(keypos_t matrix_pos) {
    coord_t out;
    if (matrix_pos.row < 4) {
        out.row = matrix_pos.row;
        out.col = matrix_pos.col;
    } else {
        out.row = matrix_pos.row - 4;
        out.col = 11 - matrix_pos.col;
    }
    return out;
}

dir_t turn_towards(coord_t target, coord_t source, dir_t banned_dir) {
    dir_t preferred;
    dir_t secondary;
    uint8_t x_dist;
    uint8_t y_dist;
    if (target.col <= source.col) {
        x_dist = source.col - target.col;
        preferred = left;
    } else {
        x_dist = target.col - source.col;
        preferred = right;
    }
    if (target.row <= source.row) {
        y_dist = source.row - target.row;
        if (y_dist >= x_dist) {
            secondary = preferred;
            preferred = up;
        } else {
            secondary = up;
        }
    } else {
        y_dist = target.row - source.row;
        if (y_dist >= x_dist) {
            secondary = preferred;
            preferred = down;
        } else {
            secondary = down;
        }
    }
    if (preferred != banned_dir) {
        return preferred;
    } else {
        return secondary;
    }
}

void update_snek(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return;
    }
    coord_t press_pos = matrix_to_snake(record->event.key);
    coord_t head_pos = snake_state.snake_cells[snake_state.snake_head];
    snake_state.snake_dir = turn_towards(press_pos, head_pos, tail_dir());
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // update_swapper(
    //     &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
    //     keycode, record
    // );

    // update_oneshot(
    //     &os_shft_state, KC_LSFT, OS_SHFT,
    //     keycode, record
    // );
    // update_oneshot(
    //     &os_ctrl_state, KC_LCTL, OS_CTRL,
    //     keycode, record
    // );
    // update_oneshot(
    //     &os_alt_state, KC_LALT, OS_ALT,
    //     keycode, record
    // );
    // update_oneshot(
    //     &os_cmd_state, KC_LGUI, OS_GUI,
    //     keycode, record
    // );

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
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            snake_state_t m2s = snake_state;
            if(transaction_rpc_send(USER_SYNC_SNEK, sizeof(m2s), &m2s)) {
                last_sync = timer_read32();
            }
        }
    }
}

#endif // RGB_MATRIX_CUSTOM_USER

// Layer indicator
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv_blue = {HSV_BLUE};
    hsv_blue.v = rgb_matrix_get_val();
    RGB rgb_blue = hsv_to_rgb(hsv_blue);
    #ifdef STENO_ENABLE
    HSV hsv_green = {HSV_GREEN};
    hsv_green.v = rgb_matrix_get_val();
    RGB rgb_green = hsv_to_rgb(hsv_green);
    #endif // STENO_ENABLE

    if (IS_LAYER_ON_STATE(layer_state, GMR)) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED) { 
                    uint16_t keycode = keymap_key_to_keycode(GMR, (keypos_t){col,row});
                    if (keycode == KC_W || keycode == KC_A || keycode == KC_S || keycode == KC_D) {
                        rgb_matrix_set_color(index, rgb_blue.r, rgb_blue.g, rgb_blue.b);
                    }
                }
            }
        }
    } 
    #ifdef STENO_ENABLE
    else if (IS_LAYER_ON_STATE(layer_state, STN)) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED) { 
                    uint16_t keycode = keymap_key_to_keycode(STN, (keypos_t){col,row});
                    if (keycode >= STN_S1 && keycode <= STN_RL) {
                        // Start consonants
                        rgb_matrix_set_color(index, rgb_blue.r, rgb_blue.g, rgb_blue.b);
                    } else if (keycode == STN_ST1 || keycode == STN_ST2 || keycode == STN_ST3 || keycode == STN_ST4) {
                        // Star
                        rgb_matrix_set_color(index, rgb_green.r, rgb_green.g, rgb_green.b);
                    } else if (keycode == STN_A || keycode == STN_O || keycode == STN_E || keycode == STN_U) {
                        // Vowels
                        rgb_matrix_set_color(index, rgb_blue.r, rgb_blue.g, rgb_blue.b);
                    } else if ((keycode >= STN_FR && keycode <= STN_DR) || keycode == STN_ZR) {
                        // End consonants
                        rgb_matrix_set_color(index, rgb_blue.r, rgb_blue.g, rgb_blue.b);
                    } else if ((keycode >= STN_N1 && keycode <= STN_N6) || (keycode >= STN_N7 && keycode <= STN_NC)) {
                        // Number bar
                    } else if (keycode >= STN__MIN && keycode <= STN__MAX) {
                        // Other steno keys
                    }
                }
            }
        }
    }
    #endif // STENO_ENABLE

    return false;
}

#endif // RGB_MATRIX_ENABLE

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
    switch (get_highest_layer(layer_state)) {
        case DEF:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case NUM:
            oled_write_ln_P(PSTR("Num/Nav"), false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        case FUN:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        case GMR:
            oled_write_ln_P(PSTR("Gamer"), false);
            break;
        #ifdef STENO_ENABLE
        case STN:
            oled_write_ln_P(PSTR("Steno"), false);
            break;
        #endif
        #ifdef MIDI_ENABLE
        case MID:
            oled_write_ln_P(PSTR("MIDI"), false);
            break;
        #endif
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
            break;
    }
}

// static void oled_render_osm_state(void) {
//     switch (os_shft_state) {
//         case os_up_unqueued:
//             oled_write_P(PSTR("     "), false);
//             break;
//         case os_up_queued:
//         case os_down_unused:
//         case os_down_used:
//             oled_write_P(PSTR("SHFT "), false);
//             break;
//     }
//     switch (os_ctrl_state) {
//         case os_up_unqueued:
//             oled_write_P(PSTR("     "), false);
//             break;
//         case os_up_queued:
//         case os_down_unused:
//         case os_down_used:
//             oled_write_P(PSTR("CTRL "), false);
//             break;
//     }
//     switch (os_alt_state) {
//         case os_up_unqueued:
//             oled_write_P(PSTR("    "), false);
//             break;
//         case os_up_queued:
//         case os_down_unused:
//         case os_down_used:
//             oled_write_P(PSTR("ALT "), false);
//             break;
//     }
//     switch (os_cmd_state) {
//         case os_up_unqueued:
//             oled_write_P(PSTR("   "), false);
//             break;
//         case os_up_queued:
//         case os_down_unused:
//         case os_down_used:
//             oled_write_P(PSTR("GUI"), false);
//             break;
//     }
// }

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
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
