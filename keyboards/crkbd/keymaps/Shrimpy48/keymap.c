#include QMK_KEYBOARD_H
#include "keymap_uk.h"
#include "sendstring_uk.h"
#include "os_detection.h"
#include "transactions.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif // CONSOLE_ENABLE

#ifdef RGB_MATRIX_CUSTOM_USER
#include "snek.h"
#endif // RGB_MATRIX_CUSTOM_USER

#include "qmk_steno/qmk_steno.h"

// --- Keymap ---

enum layers {
    ALF,
    SYM,
    NUM,
    FUN,
    STN,
    GMR,
    // MID,
    // SEQ,
    MOU,
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
	[ALF] = LAYOUT_split_3x6_3(
        TO(STN), UK_Q   , UK_W   , UK_F   , UK_P   , UK_B   ,    UK_J   , UK_L   , UK_U   , UK_Y   , UK_Z   , TO(MOU),
        KC_BSPC, UK_A   , UK_R   , UK_S   , UK_T   , UK_G   ,    UK_M   , UK_N   , UK_E   , UK_I   , UK_O   , KC_DEL ,
        KC_BSPC, UK_QUOT, UK_X   , UK_C   , UK_D   , UK_V   ,    UK_K   , UK_H   , UK_COMM, UK_DOT , UK_COLN, KC_DEL ,
                            XXXXXXX, LT(SYM,KC_TAB), KC_SPC ,    MT(MOD_RSFT,KC_ENT), LT(NUM,KC_ESC), XXXXXXX
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
	[FUN] = LAYOUT_split_3x6_3(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,    KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_TOG, RGB_MOD,    KC_MNXT, KC_MPLY, KC_VOLU, KC_BRIU, KC_PSCR, KC_PAUS,
        RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_M_R, RGB_RMOD,   KC_MPRV, KC_MUTE, KC_VOLD, KC_BRID, KC_INS , TO(GMR),
                                   XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX
        ),
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
                                   KC_LALT, KC_SPC , KC_LBRC,    KC_ENT , KC_RBRC, TO(ALF)
        ),
	// [MID] = LAYOUT_split_3x6_3(
 //        MI_C   , MI_Cs  , MI_D   , MI_Ds  , MI_E   , MI_F   ,    MI_Fs  , MI_G   , MI_Gs  , MI_A   , MI_As  , MI_B   ,
 //        MI_C   , MI_Cs  , MI_D   , MI_Ds  , MI_E   , MI_F   ,    MI_Fs  , MI_G   , MI_Gs  , MI_A   , MI_As  , MI_B   ,
 //        MI_C   , MI_Cs  , MI_D   , MI_Ds  , MI_E   , MI_F   ,    MI_Fs  , MI_G   , MI_Gs  , MI_A   , MI_As  , MI_B   ,
 //                                   XXXXXXX, MI_OCTD, MI_SOFT,    MI_SUST, MI_OCTU, TO(ALF)
 //        ),
	// [SEQ] = LAYOUT_split_3x6_3(
 //        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,    KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
 //        KC_NO  , SQ_S(0), SQ_S(1), SQ_S(2), SQ_S(3), KC_NO  ,    SQ_RESU, SQ_S(8), SQ_S(9), SQ_S(10),SQ_S(11),KC_NO  ,
 //        KC_NO  , SQ_S(4), SQ_S(5), SQ_S(6), SQ_S(7), KC_NO  ,    SQ_RESD, SQ_S(12),SQ_S(13),SQ_S(14),SQ_S(15),KC_NO  ,
 //                                   XXXXXXX, SQ_TMPD, SQ_TOG ,    SQ_TOG , SQ_TMPU, TO(ALF)
 //        ),
	[MOU] = LAYOUT_split_3x6_3(
        KC_ACL2, KC_BTN5, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4,    DG_0_0 , DG_1_0 , DG_2_0 , DG_3_0 , DG_4_0 , DG_5_0 ,
        KC_ACL1, KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, KC_BTN6,    DG_0_1 , DG_1_1 , DG_2_1 , DG_3_1 , DG_4_1 , DG_5_1 ,
        KC_ACL0, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_BTN7,    DG_0_2 , DG_1_2 , DG_2_2 , DG_3_2 , DG_4_2 , DG_5_2 ,
                                   XXXXXXX, KC_BTN2, KC_BTN1,    DG_BTN1, DG_BTN2, TO(ALF)
        ),
};

// --- State ---

static bool steno_onboard = true;

// --- Key Overrides ---
#ifdef KEY_OVERRIDE_ENABLE
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
#endif // KEY_OVERRIDE_ENABLE

// --- Combos ---
#ifdef COMBO_ENABLE
// Combo 2nd and 3rd row for left mods, 1st and 2nd for right mods
const uint16_t PROGMEM ls_combo[] = {UK_A, UK_QUOT, COMBO_END};
const uint16_t PROGMEM la_combo[] = {UK_R, UK_X, COMBO_END};
const uint16_t PROGMEM lc_combo[] = {UK_S, UK_C, COMBO_END};
const uint16_t PROGMEM lg_combo[] = {UK_T, UK_D, COMBO_END};
const uint16_t PROGMEM rg_combo[] = {UK_N, UK_H, COMBO_END};
const uint16_t PROGMEM rc_combo[] = {UK_E, UK_COMM, COMBO_END};
const uint16_t PROGMEM ra_combo[] = {UK_I, UK_DOT, COMBO_END};
const uint16_t PROGMEM rs_combo[] = {UK_O, UK_COLN, COMBO_END};
combo_t key_combos[] = {
    COMBO(ls_combo, KC_LSFT),
    COMBO(la_combo, KC_LALT),
    COMBO(lc_combo, KC_LCTL),
    COMBO(lg_combo, KC_LGUI),
    COMBO(rs_combo, KC_RSFT),
    COMBO(ra_combo, KC_LALT),
    COMBO(rc_combo, KC_RCTL),
    COMBO(rg_combo, KC_LGUI),
};
#endif // COMBO_ENABLE

// --- OS detection ---
#ifdef OS_DETECTION_ENABLE
os_variant_t host_os = OS_UNSURE;
bool host_os_dirty = false;

void user_sync_os_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const os_variant_t *m2s = (const os_variant_t*)in_data;
    host_os = *m2s;
}
#endif // OS_DETECTION_ENABLE

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
#endif // RGB_MATRIX_CUSTOM_USER

// --- OLED ---
#ifdef OLED_ENABLE

static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case STN:
            oled_write_P(PSTR("Steno"), false);
            if (steno_onboard) {
                oled_write_ln_P(PSTR(" [OB]"), false);
            } else {
                oled_write_ln_P(PSTR(" [  ]"), false);
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
        case ALF:
            oled_write_ln_P(PSTR("Alpha"), false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        case NUM:
            oled_write_ln_P(PSTR("Number"), false);
            break;
    }
}

#ifdef STENO_TAPE
#define STENO_TAPE_LEN 3
uint32_t steno_hist[STENO_TAPE_LEN] = {0};
bool tape_dirty = false;

void user_sync_tape_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const uint32_t *m2s = (const uint32_t*)in_data;
    for (uint8_t i = 0; i < STENO_TAPE_LEN; i++) {
        steno_hist[i] = m2s[i];
    }
}

void clear_steno_tape(void) {
    for (uint8_t i = 0; i < STENO_TAPE_LEN; i++) {
        steno_hist[i] = 0;
    }
    tape_dirty = true;
}

void oled_render_steno_tape(void) {
    for (uint8_t row = 0; row < STENO_TAPE_LEN; row++) {
        if (steno_hist[row]) {
            oled_write_stroke(steno_hist[row]);
        }
        oled_advance_page(true);
    }
}
#endif // STENO_TAPE

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

#ifdef OS_DETECTION_ENABLE

void oled_render_windows_logo(void) {
    // clang-format off
    static const char PROGMEM win_logo[] = {
        0x80, 0x80, 0x80, 0x97, 0x98, 0x80, 0x80, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa0, 0xa0, 0xb7, 0xb8, 0xa0, 0xa0, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    // clang-format on
    oled_write_P(win_logo, false);
}

void oled_render_linux_logo(void) {
    // clang-format off
    static const char PROGMEM tux_logo[] = {
        0x80, 0x80, 0x80, 0x99, 0x9a, 0x80, 0x80, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa0, 0xa0, 0xb9, 0xba, 0xa0, 0xa0, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    // clang-format on
    oled_write_P(tux_logo, false);
}

void oled_render_apple_logo(void) {
    // clang-format off
    static const char PROGMEM apple_logo[] = {
        0x80, 0x80, 0x80, 0x95, 0x96, 0x80, 0x80, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa0, 0xa0, 0xb5, 0xb6, 0xa0, 0xa0, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    // clang-format on
    oled_write_P(apple_logo, false);
}

#endif // OS_DETECTION_ENABLE
#endif // OLED_ENABLE

// --- Digitizer ---
#ifdef DIGITIZER_ENABLE
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
#endif // DIGITIZER_ENABLE

// --- Callbacks ---

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_CUSTOM_USER
    transaction_register_rpc(USER_SYNC_SNEK, user_sync_snek_slave_handler);
#endif // RGB_MATRIX_CUSTOM_USER
#ifdef OS_DETECTION_ENABLE
    transaction_register_rpc(USER_SYNC_OS, user_sync_os_slave_handler);
#endif // OS_DETECTION_ENABLE
#ifdef STENO_TAPE
    transaction_register_rpc(USER_SYNC_TAPE, user_sync_tape_slave_handler);
#endif // STENO_TAPE
#ifdef CONSOLE_ENABLE
    debug_enable=true;
    debug_keyboard=true;
#endif
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180; // flip the right display 180 degrees so they both face towards the user
    }
    return OLED_ROTATION_0;
}
#endif // OLED_ENABLE

#ifdef OS_DETECTION_ENABLE
bool process_detected_host_os_user(os_variant_t detected_os) {
    host_os = detected_os;
    host_os_dirty = true;
    return true;
}
#endif // OS_DETECTION_ENABLE

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {

#ifdef RGB_MATRIX_CUSTOM_USER
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            snake_state_t m2s = snake_state;
            if (transaction_rpc_send(USER_SYNC_SNEK, sizeof(m2s), &m2s)) {
                last_sync = timer_read32();
            }
        }
#endif // RGB_MATRIX_CUSTOM_USER

#ifdef OS_DETECTION_ENABLE
        if (host_os_dirty) {
            if (transaction_rpc_send(USER_SYNC_OS, sizeof(host_os), &host_os)) {
                host_os_dirty = false;
            }
        } else {
            os_variant_t detected_os = detected_host_os();
            if (detected_os != host_os) {
                host_os = detected_os;
                host_os_dirty = true;
            }
        }
#endif // OS_DETECTION_ENABLE

#ifdef STENO_TAPE
        if (tape_dirty) {
            if (transaction_rpc_send(USER_SYNC_TAPE, sizeof(steno_hist), &steno_hist)) {
                tape_dirty = false;
            }
        }
#endif // STENO_TAPE

    }
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
#ifdef STENO_TAPE
        oled_render_steno_tape();
#endif
    } else {
#ifdef OS_DETECTION_ENABLE
        switch (host_os) {
        case OS_WINDOWS:
            oled_render_windows_logo();
            break;
        case OS_LINUX:
            oled_render_linux_logo();
            break;
        case OS_MACOS:
        case OS_IOS:
            oled_render_apple_logo();
            break;
        case OS_UNSURE:
        default:
            oled_render_logo();
            break;
        }
#else // OS_DETECTION_ENABLE
        oled_render_logo();
#endif // OS_DETECTION_ENABLE
    }
    return false;
}
#endif // OLED_ENABLE

#ifdef STENO_TAPE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state|default_layer_state) != STN) {
        return false;
    }
    uint32_t stroke = steno_hist[STENO_TAPE_LEN-1];
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index < led_max && index != NO_LED) {
                uint16_t kc = keymap_key_to_keycode(STN, (keypos_t){col,row});
                HSV hsv = rgb_matrix_config.hsv;
                hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                hsv.s = 255;
                if ((stroke & (1<<22)) && ((STN_N1 <= kc && kc <= STN_N6) || (STN_N7 <= kc && kc <= STN_NC))) {
                    hsv.h = 11 * 0;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<21)) && STN_S1 <= kc && kc <= STN_S2) {
                    hsv.h = 11 * 1;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<20)) && kc == STN_TL) {
                    hsv.h = 11 * 2;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<19)) && kc == STN_KL) {
                    hsv.h = 11 * 3;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<18)) && kc == STN_PL) {
                    hsv.h = 11 * 4;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<17)) && kc == STN_WL) {
                    hsv.h = 11 * 5;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<16)) && kc == STN_HL) {
                    hsv.h = 11 * 6;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<15)) && kc == STN_RL) {
                    hsv.h = 11 * 7;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<14)) && kc == STN_A) {
                    hsv.h = 11 * 8;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<13)) && kc == STN_O) {
                    hsv.h = 11 * 9;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<12)) && ((STN_ST1 <= kc && kc <= STN_ST2) || (STN_ST3 <= kc && kc <= STN_ST4))) {
                    hsv.h = 11 * 10;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<11)) && kc == STN_E) {
                    hsv.h = 11 * 11;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<10)) && kc == STN_U) {
                    hsv.h = 11 * 12;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<9)) && kc == STN_FR) {
                    hsv.h = 11 * 13;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<8)) && kc == STN_RR) {
                    hsv.h = 11 * 14;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<7)) && kc == STN_PR) {
                    hsv.h = 11 * 15;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<6)) && kc == STN_BR) {
                    hsv.h = 11 * 16;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<5)) && kc == STN_LR) {
                    hsv.h = 11 * 17;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<4)) && kc == STN_GR) {
                    hsv.h = 11 * 18;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<3)) && kc == STN_TR) {
                    hsv.h = 11 * 19;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<2)) && kc == STN_SR) {
                    hsv.h = 11 * 20;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<1)) && kc == STN_DR) {
                    hsv.h = 11 * 21;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if ((stroke & (1<<0)) && kc == STN_ZR) {
                    hsv.h = 11 * 22;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                }
            }
        }
    }
    return false;
}

bool post_process_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[MAX_STROKE_SIZE], int8_t n_pressed_keys) {
    // Only GeminiPR is supported because I'm lazy
    if (mode != STENO_MODE_GEMINI) {
        return true;
    }

    steno_hist[STENO_TAPE_LEN-1] = translate_chord(chord);

    if (!record->event.pressed && n_pressed_keys < 1) {
        // Advance the tape
        for (uint8_t i = 0; i < STENO_TAPE_LEN-1; i++) {
            steno_hist[i] = steno_hist[i+1];
        }
        steno_hist[STENO_TAPE_LEN-1] = 0;
    }

    tape_dirty = true;

    return true;
}
#endif // STENO_TAPE

bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[MAX_STROKE_SIZE]) {
    // Only GeminiPR is supported because I'm lazy
    if (mode != STENO_MODE_GEMINI) {
        return true;
    }

    // Only pwr
    const uint8_t QUIT_CHORD[MAX_STROKE_SIZE] = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b01000000,
        0b00000000,
        0b00000000
    };
    if (memcmp(chord, QUIT_CHORD, MAX_STROKE_SIZE) == 0) {
        layer_move(ALF);
        return false;
    }

    // Only fn
    const uint8_t TOGGLE_OB_CHORD[MAX_STROKE_SIZE] = {
        0b01000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    if (memcmp(chord, TOGGLE_OB_CHORD, MAX_STROKE_SIZE) == 0) {
        steno_onboard = !steno_onboard;
        return false;
    }

    if (steno_onboard) {
        uint32_t stroke = translate_chord(chord);
#ifdef CONSOLE_ENABLE
        uprintf("handling %ld\n", stroke);
#endif // CONSOLE_ENABLE
        handle_stroke(stroke, host_os);
        struct NextKey res;
        do {
            res = get_next_key();
            switch (res.mode) {
            case 1:
                tap_code(res.key);
                break;
            case 2:
                register_code(res.key);
                break;
            case 3:
                unregister_code(res.key);
                break;
            }
        } while (res.mode != 0);
        return false;
    } else {
#ifdef CONSOLE_ENABLE
        uprint("passing stroke on to QMK\n");
#endif // CONSOLE_ENABLE
        return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef DIGITIZER_ENABLE
    update_digitizer(keycode, record);
#endif // DIGITIZER_ENABLE

#ifdef RGB_MATRIX_CUSTOM_USER
    update_snek(keycode, record);
#endif // RGB_MATRIX_CUSTOM_USER

    return true;
}

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
    state = update_tri_layer_state(state, NUM, SYM, FUN);
    return state;
}
