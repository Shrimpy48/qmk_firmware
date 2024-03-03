#include QMK_KEYBOARD_H

#include "keymap_uk.h"
#include "sendstring_uk.h"

#include "/home/philip/python/steno/rust/rust_steno_engine.h"

#ifdef RGB_MATRIX_CUSTOM_USER
#include "transactions.h"
#include "snek.h"
#endif // RGB_MATRIX_CUSTOM_USER

// #include "oneshot.h"
// #include "swapper.h"

enum layers {
    STN,
    GMR,
    // MID,
    // SEQ,
    FUN,
    MOU,
    AUX,
    ALF,
    SYM,
    NUM,
    EDT,
};

enum keycodes {
    DG_0_0 = SAFE_RANGE,
    DG_1_0,
    DG_2_0,
    DG_3_0,
    DG_4_0,
    DG_5_0,
    DG_0_1,
    DG_1_1,
    DG_2_1,
    DG_3_1,
    DG_4_1,
    DG_5_1,
    DG_0_2,
    DG_1_2,
    DG_2_2,
    DG_3_2,
    DG_4_2,
    DG_5_2,
    DG_BTN1,
    DG_BTN2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[STN] = LAYOUT_split_3x6_3(
        STN_N1 , STN_N2 , STN_N3 , STN_N4 , STN_N5 , STN_N6 ,    STN_N7 , STN_N8 , STN_N9 , STN_NA , STN_NB , STN_NC ,
        STN_FN , STN_S1 , STN_TL , STN_PL , STN_HL , STN_ST1,    STN_ST3, STN_FR , STN_PR , STN_LR , STN_TR , STN_DR ,
        STN_PWR, STN_S2 , STN_KL , STN_WL , STN_RL , STN_ST2,    STN_ST4, STN_RR , STN_BR , STN_GR , STN_SR , STN_ZR ,
                                   STN_A  , STN_O  , STN_RES1,   STN_RES2,STN_E  , STN_U
        ),
	[GMR] = LAYOUT_split_3x6_3(
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,    KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_ESC ,
        KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,    KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,    KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_BSPC,
                                   KC_LALT, KC_SPC , KC_LBRC,    KC_ENT , KC_RBRC, TO(STN)
        ),
	// [MID] = LAYOUT_split_3x6_3(
 //        MI_C   , MI_Cs  , MI_D   , MI_Ds  , MI_E   , MI_F   ,    MI_Fs  , MI_G   , MI_Gs  , MI_A   , MI_As  , MI_B   ,
 //        MI_C   , MI_Cs  , MI_D   , MI_Ds  , MI_E   , MI_F   ,    MI_Fs  , MI_G   , MI_Gs  , MI_A   , MI_As  , MI_B   ,
 //        MI_C   , MI_Cs  , MI_D   , MI_Ds  , MI_E   , MI_F   ,    MI_Fs  , MI_G   , MI_Gs  , MI_A   , MI_As  , MI_B   ,
 //                                   TO(STN), MI_OCTD, MI_SOFT,    MI_SUST, MI_OCTU, TO(STN) 
 //        ),
	// [SEQ] = LAYOUT_split_3x6_3(
 //        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,    KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
 //        KC_NO  , SQ_S(0), SQ_S(1), SQ_S(2), SQ_S(3), KC_NO  ,    SQ_RESU, SQ_S(8), SQ_S(9), SQ_S(10),SQ_S(11),KC_NO  ,
 //        KC_NO  , SQ_S(4), SQ_S(5), SQ_S(6), SQ_S(7), KC_NO  ,    SQ_RESD, SQ_S(12),SQ_S(13),SQ_S(14),SQ_S(15),KC_NO  ,
 //                                   TO(STN), SQ_TMPD, SQ_TOG ,    SQ_TOG , SQ_TMPU, TO(STN) 
 //        ),
	[FUN] = LAYOUT_split_3x6_3(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,    KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_TOG, RGB_MOD,    KC_MNXT, KC_MPLY, KC_VOLU, KC_BRIU, KC_PSCR, KC_PAUS,
        RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_M_R, RGB_RMOD,   KC_MPRV, KC_MUTE, KC_VOLD, KC_BRID, KC_INS , KC_APP ,
                                   TO(STN), KC_F13 , KC_F14 ,    KC_F15 , KC_F16 , TO(STN)
        ),
	[MOU] = LAYOUT_split_3x6_3(
        KC_ACL2, KC_BTN5, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4,    DG_0_0 , DG_1_0 , DG_2_0 , DG_3_0 , DG_4_0 , DG_5_0 ,
        KC_ACL1, KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, KC_BTN6,    DG_0_1 , DG_1_1 , DG_2_1 , DG_3_1 , DG_4_1 , DG_5_1 ,
        KC_ACL0, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_BTN7,    DG_0_2 , DG_1_2 , DG_2_2 , DG_3_2 , DG_4_2 , DG_5_2 ,
                                   TO(STN), KC_BTN2, KC_BTN1,    DG_BTN1, DG_BTN2, TO(STN)
        ),
	[AUX] = LAYOUT_split_3x6_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   TO(STN), XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, TO(STN)
        ),
	[ALF] = LAYOUT_split_3x6_3(
        KC_BSPC, UK_Q   , UK_W   , UK_F   , UK_P   , UK_B   ,    UK_J   , UK_L   , UK_U   , UK_Y   , UK_Z   , KC_DEL ,
        KC_BSPC, UK_A   , UK_R   , UK_S   , UK_T   , UK_G   ,    UK_M   , UK_N   , UK_E   , UK_I   , UK_O   , KC_DEL ,
        KC_BSPC, UK_QUOT, UK_X   , UK_C   , UK_D   , UK_V   ,    UK_K   , UK_H   , UK_COMM, UK_DOT , UK_COLN, KC_DEL ,
                            TO(STN), LT(SYM,KC_TAB), KC_SPC ,    MT(MOD_RSFT,KC_ENT), LT(NUM,KC_ESC), TO(STN)
        ),
	[SYM] = LAYOUT_split_3x6_3(
        _______, UK_LABK, UK_LBRC, UK_LCBR, UK_LPRN, UK_CIRC,    UK_DLR , UK_RPRN, UK_RCBR, UK_RBRC, UK_RABK, _______,
        _______, UK_PLUS, UK_AMPR, UK_QUES, UK_EXLM, UK_TILD,    UK_HASH, UK_UNDS, UK_EQL , UK_ASTR, UK_MINS, _______,
        _______, UK_NOT , UK_PIPE, UK_AT  , UK_SLSH, UK_PERC,    UK_GRV , UK_BSLS, UK_LABK, UK_RABK, UK_PND , _______,
                                   _______, XXXXXXX, _______,    _______, _______, _______
        ),
	[NUM] = LAYOUT_split_3x6_3(
        _______, UK_COMM, UK_7   , UK_8   , UK_9   , UK_DLR ,    UK_HASH, UK_MINS, UK_PLUS, UK_ASTR, UK_SLSH, _______,
        _______, KC_DOT , KC_4   , KC_5   , KC_6   , UK_PND ,    KC_UNDS, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,
        _______, KC_0   , UK_1   , UK_2   , UK_3   , KC_PERC,    UK_QUOT, KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______,
                                   _______, _______, _______,    _______, XXXXXXX, _______
        ),
	[EDT] = LAYOUT_split_3x6_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, XXXXXXX, _______,    _______, XXXXXXX, _______
        ),
};

// shift-' = " like on US layout
const key_override_t quote_key_override = ko_make_basic(MOD_MASK_SHIFT, UK_QUOT, UK_DQUO);
// swap : and ;
const key_override_t scln_key_override = ko_make_basic(MOD_MASK_SHIFT, UK_COLN, UK_SCLN);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &quote_key_override,
    &scln_key_override,
    NULL // Null terminate the array of overrides!
};

#ifdef COMBO_ENABLE
// Combo 2nd and 3rd row for left mods, 1st and 2nd for right mods
const uint16_t PROGMEM lls_combo[] = {UK_A, UK_QUOT, COMBO_END};
const uint16_t PROGMEM llc_combo[] = {UK_R, UK_X, COMBO_END};
const uint16_t PROGMEM lla_combo[] = {UK_S, UK_C, COMBO_END};
const uint16_t PROGMEM llg_combo[] = {UK_T, UK_D, COMBO_END};
const uint16_t PROGMEM rlg_combo[] = {UK_N, UK_H, COMBO_END};
const uint16_t PROGMEM rla_combo[] = {UK_E, UK_COMM, COMBO_END};
const uint16_t PROGMEM rlc_combo[] = {UK_I, UK_DOT, COMBO_END};
const uint16_t PROGMEM rls_combo[] = {UK_O, UK_COLN, COMBO_END};
const uint16_t PROGMEM lrs_combo[] = {UK_Q, UK_A, COMBO_END};
const uint16_t PROGMEM lrc_combo[] = {UK_W, UK_R, COMBO_END};
const uint16_t PROGMEM lra_combo[] = {UK_F, UK_S, COMBO_END};
const uint16_t PROGMEM lrg_combo[] = {UK_P, UK_T, COMBO_END};
const uint16_t PROGMEM rrg_combo[] = {UK_L, UK_N, COMBO_END};
const uint16_t PROGMEM rra_combo[] = {UK_U, UK_E, COMBO_END};
const uint16_t PROGMEM rrc_combo[] = {UK_Y, UK_I, COMBO_END};
const uint16_t PROGMEM rrs_combo[] = {UK_Z, UK_O, COMBO_END};
combo_t key_combos[] = {
    COMBO(lls_combo, KC_LSFT),
    COMBO(llc_combo, KC_LCTL),
    COMBO(lla_combo, KC_LALT),
    COMBO(llg_combo, KC_LGUI),
    COMBO(rls_combo, KC_LSFT),
    COMBO(rlc_combo, KC_LCTL),
    COMBO(rla_combo, KC_LALT),
    COMBO(rlg_combo, KC_LGUI),
    COMBO(lrs_combo, KC_RSFT),
    COMBO(lrc_combo, KC_RCTL),
    COMBO(lra_combo, KC_RALT),
    COMBO(lrg_combo, KC_RGUI),
    COMBO(rrs_combo, KC_RSFT),
    COMBO(rrc_combo, KC_RCTL),
    COMBO(rra_combo, KC_RALT),
    COMBO(rrg_combo, KC_RGUI),
};
#endif // COMBO_ENABLE

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

static bool steno_onboard = true;

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
        case STN:
            oled_write_P(PSTR("Steno"), false);
            if (steno_onboard) {
                oled_write_ln_P(PSTR(" [OB]"), false);
            } else {
                oled_advance_page(true);
            }
            break;
        case GMR:
            oled_write_ln_P(PSTR("Game"), false);
            break;
        // case MID:
        //     oled_write_ln_P(PSTR("MIDI"), false);
        //     break;
        // case SEQ:
        //     oled_write_ln_P(PSTR("Sequencer"), false);
        //     break;
        case FUN:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        case MOU:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case AUX:
            oled_write_ln_P(PSTR("Extra"), false);
            break;
        case ALF:
            oled_write_ln_P(PSTR("Alpha"), false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        case NUM:
            oled_write_ln_P(PSTR("Number"), false);
            break;
        case EDT:
            oled_write_ln_P(PSTR("Edit"), false);
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

#ifdef STENO_TAPE
#define STENO_TAPE_LEN 3
// In reverse order because reasons
static const char steno_chars[23] PROGMEM = {'Z', 'D', 'S', 'T', 'G', 'L', 'B', 'P', 'R', 'F', 'U', 'E', '*', 'O', 'A', 'R', 'H', 'W', 'P', 'K', 'T', 'S', '#'};

uint32_t steno_tape[STENO_TAPE_LEN] = {0};

uint32_t translate_chord(uint8_t chord[MAX_STROKE_SIZE]) {
    uint32_t num = ((chord[0] & 0b00111111) > 0) || ((chord[5] & 0b01111110) > 0);
    uint32_t s_l = (chord[1] & 0b01100000) > 0;
    uint32_t tkpwh_l = chord[1] & 0b00011111;
    uint32_t rao_l = (chord[2] & 0b01110000) >> 4;
    uint32_t star = ((chord[2] & 0b00001100) > 0) || ((chord[3] & 0b00110000) > 0);
    uint32_t eufr_r = chord[3] & 0b00001111;
    uint32_t pblgtsd_r = chord[4] & 0b01111111;
    uint32_t z_r = chord[5] & 0b00000001;
    return z_r | (pblgtsd_r << 1) | (eufr_r << 8) | (star << 12) | (rao_l << 13) | (tkpwh_l << 16) | (s_l << 21) | (num << 22);
}

bool post_process_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[MAX_STROKE_SIZE], int8_t n_pressed_keys) {
    // Only GeminiPR is supported because I'm lazy
    if (mode != STENO_MODE_GEMINI) {
        return true;
    }

    steno_tape[STENO_TAPE_LEN-1] = translate_chord(chord);

    if (!record->event.pressed && n_pressed_keys < 1) {
        // Advance the tape
        for (uint8_t i = 0; i < STENO_TAPE_LEN-1; i++) {
            steno_tape[i] = steno_tape[i+1];
        }
        steno_tape[STENO_TAPE_LEN-1] = 0;
    }

    return true;
}

void clear_steno_tape(void) {
    for (uint8_t i = 0; i < STENO_TAPE_LEN; i++) {
        steno_tape[i] = 0;
    }
}

void oled_render_steno_tape(void) {
    uint32_t one = 1;
    for (uint8_t row = 0; row < STENO_TAPE_LEN; row++) {
        for (int32_t i = 22; i > 12; i--) {
            if (steno_tape[row] & (one << i)) {
                char steno_char = pgm_read_byte(&steno_chars[i]);
                oled_write_char(steno_char, false);
            }
        }
        if (steno_tape[row] & (one << 12)) {
            char steno_char = pgm_read_byte(&steno_chars[12]);
            oled_write_char(steno_char, false);
        } else if (steno_tape[row]) {
            oled_write_char('-', false);
        }
        for (int32_t i = 11; i >= 0; i--) {
            if (steno_tape[row] & (one << i)) {
                char steno_char = pgm_read_byte(&steno_chars[i]);
                oled_write_char(steno_char, false);
            }
        }
        oled_advance_page(true);
    }
}
#endif // STENO_TAPE

bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[MAX_STROKE_SIZE]) {
    // bool fn_pressed = (chord[0] & 0b01000000) > 0;
    bool res1_pressed = (chord[2] & 0b00000010) > 0;
    bool res2_pressed = (chord[2] & 0b00000001) > 0;
    bool pwr_pressed = (chord[3] & 0b01000000) > 0;
    uint32_t parsed_chord = translate_chord(chord);
    if ((res1_pressed || res2_pressed) && !parsed_chord) {
        layer_move(ALF);
        return false;
    } else if ((res1_pressed || res2_pressed) && (parsed_chord == 0b00111100000000000000000 || parsed_chord == 0b00000000000000000010000)) {
        // G
        layer_move(GMR);
        return false;
    } else if ((res1_pressed || res2_pressed) && (parsed_chord == 0b00001010000000000000000 || parsed_chord == 0b00000000000000010100000)) {
        // M
        layer_move(MOU);
        return false;
    } else if ((res1_pressed || res2_pressed) && (parsed_chord == 0b00101000000000000000000 || parsed_chord == 0b00000000000001000000000)) {
        // F
        layer_move(FUN);
        return false;
    } else if ((res1_pressed || res2_pressed) && (parsed_chord == 0b00011000000000000000000 || parsed_chord == 0b00000000000000001010100)) {
        // X
        layer_move(AUX);
        return false;
    } else if (pwr_pressed && !parsed_chord) {
        steno_onboard = !steno_onboard;
        return false;
    }

    if (steno_onboard) {
        handle_chord(chord);
        return false;
    } else {
        return true;
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
        #ifdef STENO_TAPE
        oled_render_steno_tape();
        #endif
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE

uint8_t n_digitizer_pressed = 0;

void update_digitizer(uint16_t keycode, keyrecord_t *record) {
    if (keycode < DG_0_0 || keycode > DG_BTN2) {
        return;
    }
    switch (keycode) {
    case DG_BTN1:
        digitizer_state.tip = record->event.pressed;
        digitizer_state.dirty = true;
        digitizer_flush();
        return;
    case DG_BTN2:
        digitizer_state.barrel = record->event.pressed;
        digitizer_state.dirty = true;
        digitizer_flush();
        return;
    }
    if (record->event.pressed) {
        n_digitizer_pressed++;
        digitizer_in_range_on();
    } else {
        n_digitizer_pressed--;
        if (n_digitizer_pressed == 0) {
            digitizer_in_range_off();
        }
        return;
    }
    switch (keycode) {
    case DG_0_0:
        digitizer_set_position(0./5., 0./2.);
        break;
    case DG_1_0:
        digitizer_set_position(1./5., 0./2.);
        break;
    case DG_2_0:
        digitizer_set_position(2./5., 0./2.);
        break;
    case DG_3_0:
        digitizer_set_position(3./5., 0./2.);
        break;
    case DG_4_0:
        digitizer_set_position(4./5., 0./2.);
        break;
    case DG_5_0:
        digitizer_set_position(5./5., 0./2.);
        break;
    case DG_0_1:
        digitizer_set_position(0./5., 1./2.);
        break;
    case DG_1_1:
        digitizer_set_position(1./5., 1./2.);
        break;
    case DG_2_1:
        digitizer_set_position(2./5., 1./2.);
        break;
    case DG_3_1:
        digitizer_set_position(3./5., 1./2.);
        break;
    case DG_4_1:
        digitizer_set_position(4./5., 1./2.);
        break;
    case DG_5_1:
        digitizer_set_position(5./5., 1./2.);
        break;
    case DG_0_2:
        digitizer_set_position(0./5., 2./2.);
        break;
    case DG_1_2:
        digitizer_set_position(1./5., 2./2.);
        break;
    case DG_2_2:
        digitizer_set_position(2./5., 2./2.);
        break;
    case DG_3_2:
        digitizer_set_position(3./5., 2./2.);
        break;
    case DG_4_2:
        digitizer_set_position(4./5., 2./2.);
        break;
    case DG_5_2:
        digitizer_set_position(5./5., 2./2.);
        break;
    }
}

#ifdef RGB_MATRIX_CUSTOM_USER
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

    // if (keycode == OB_TOG && record->event.pressed) {
    //     steno_onboard = !steno_onboard;
    // }

    update_digitizer(keycode, record);

    update_snek(keycode, record);

    return true;
}
#endif // RGB_MATRIX_CUSTOM_USER

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef COMBO_ENABLE
    // Disable combos on special layers
    switch (get_highest_layer(state)) {
    case STN:
    case GMR:
    // case MID:
    // case SEQ:
        combo_disable();
        break;
    default: //  for any other layers
        combo_enable();
        break;
    }
#endif // COMBO_ENABLE

#ifdef STENO_TAPE
    clear_steno_tape();
#endif

    // Holding both inner layer keys puts you in edit layer
    state = update_tri_layer_state(state, NUM, SYM, EDT);
    return state;
}
