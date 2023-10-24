#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

enum layers {
    DEF,
    NUM,
    SYM,
    FUN,
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
	[DEF] = LAYOUT_split_3x5_2(
            KC_Q   , KC_W         , KC_F       , KC_P        , KC_B   ,    KC_J   , KC_L     , KC_U   , KC_Y   , KC_QUOT,
            KC_A   , KC_R         , KC_S       , KC_T        , KC_G   ,    KC_M   , KC_N     , KC_E   , KC_I   , KC_O   ,
            KC_Z   , KC_X         , KC_C       , KC_D        , KC_V   ,    KC_K   , KC_H     , KC_COMM, KC_DOT , KC_SCLN,
                                                 MO(NUM)     , KC_SPC ,    KC_RSFT, MO(SYM)
            ),
	[NUM] = LAYOUT_split_3x5_2(
            KC_7   , KC_5         , KC_3       , KC_1        , KC_9   ,    KC_8   , KC_0     , KC_2   , KC_4   , KC_6   ,
            OS_SHFT, OS_CTRL      , OS_ALT     , OS_GUI      , KC_PSCR,    KC_ENT , KC_LEFT  , KC_DOWN, KC_UP  , KC_RGHT,
            KC_NO  , SW_WIN       , RCS(KC_TAB), RCTL(KC_TAB), KC_NO  ,    KC_TAB , KC_HOME  , KC_PGDN, KC_PGUP, KC_END ,
                                                 KC_TRNS     , KC_TRNS,    KC_TRNS, KC_TRNS
            ),
	[SYM] = LAYOUT_split_3x5_2(
            KC_ESC , KC_LBRC      , KC_LCBR    , KC_LPRN     , KC_PIPE,    KC_CIRC, KC_RPRN  , KC_RCBR, KC_RBRC, KC_GRV ,
            KC_MINS, KC_ASTR      , KC_EQL     , KC_UNDS     , KC_DLR ,    KC_NUHS, OS_GUI   , OS_ALT , OS_CTRL, OS_SHFT,
            KC_PLUS, LSFT(KC_NUBS), KC_DQUO    , KC_SLSH     , KC_PERC,    KC_HASH, KC_NUBS  , KC_AMPR, KC_QUES, KC_EXLM,
                                                 KC_TRNS     , KC_TRNS,    KC_TRNS, KC_TRNS
            ),
	[FUN] = LAYOUT_split_3x5_2(
            KC_F1  , KC_F2        , KC_F3      , KC_F4       , KC_NO  ,    KC_NO  , OS_GUI   , OS_ALT , OS_CTRL, OS_SHFT,
            KC_F5  , KC_F6        , KC_F7      , KC_F8       , KC_NO  ,    KC_MNXT, KC_MPLY  , KC_VOLU, KC_NO  , KC_BSPC,
            KC_F9  , KC_F10       , KC_F11     , KC_F12      , KC_NO  ,    KC_MPRV, KC_MUTE  , KC_VOLD, KC_NO  , KC_DEL ,
                                                 KC_TRNS     , KC_TRNS,    KC_TRNS, KC_TRNS
            ),
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
    return update_tri_layer_state(state, NUM, SYM, FUN);
}

// Combo 2nd and 3rd row for modifiers
const uint16_t PROGMEM ls_combo[] = {KC_A, KC_Z, COMBO_END};
const uint16_t PROGMEM lc_combo[] = {KC_R, KC_X, COMBO_END};
const uint16_t PROGMEM la_combo[] = {KC_S, KC_C, COMBO_END};
const uint16_t PROGMEM lg_combo[] = {KC_T, KC_D, COMBO_END};
const uint16_t PROGMEM rg_combo[] = {KC_N, KC_H, COMBO_END};
const uint16_t PROGMEM ra_combo[] = {KC_E, KC_COMM, COMBO_END};
const uint16_t PROGMEM rc_combo[] = {KC_I, KC_DOT, COMBO_END};
const uint16_t PROGMEM rs_combo[] = {KC_O, KC_SCLN, COMBO_END};
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

// Callum's oneshot and swapper implementation
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case MO(NUM):
    case MO(SYM):
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO(NUM):
    case MO(SYM):
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

    return true;
}

