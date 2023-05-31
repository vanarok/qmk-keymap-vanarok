#include QMK_KEYBOARD_H

#define CUSTOM_SAFE_RANGE SAFE_RANGE

#include <stdio.h>
#include <stdint.h>

#define L_BASE 0
#define L_CUR 2
#define L_SYM 5
#define L_GAME 8
#define L_GAME_CUR 10

// Base layer
#define H_O LALT_T(KC_O)
#define H_H LGUI_T(KC_H)
#define H_E LCTL_T(KC_E)
#define H_A LSFT_T(KC_A)

#define H_R RSFT_T(KC_R)
#define H_T RCTL_T(KC_T)
#define H_N RGUI_T(KC_N)
#define H_S LALT_T(KC_S)

// Symbol layer
#define H_SLSH LALT_T(KC_SLSH)
#define H_MINS LGUI_T(KC_MINS)
#define H_LCBR TD(CTL_LB)
#define H_RCBR TD(SFT_RB)

#define H_LPRN TD(SFT_LP)
#define H_RPRN TD(CTL_RP)
#define H_QUOT RGUI_T(KC_QUOT)

// Cursor layer
#define H_HOME LALT_T(KC_HOME)
#define H_LEFT LGUI_T(KC_LEFT)
#define H_DOWN LCTL_T(KC_DOWN)
#define H_RIGHT LSFT_T(KC_RIGHT)

#define H_4 RSFT_T(KC_4)
#define H_5 RCTL_T(KC_5)
#define H_6 RGUI_T(KC_6)
#define H_NO LALT_T(KC_NO)

// Layer keys
#define CUR_SPC LT(L_CUR, KC_SPC)
#define SYM_ENT LT(L_SYM, KC_ENT)

enum custom_keycodes {
    KEYCODES_START = CUSTOM_SAFE_RANGE,

    CTL_PGU,
    CTL_PGD,
};

// Tap Dance keycodes
enum td_keycodes {
    CTL_LB,
    SFT_RB,

    SFT_LP,
    CTL_RP,
};

// Define a type containing as many tap-dance states as you need
typedef enum { TD_NONE, TD_UNKNOWN, TD_SINGLE_TAP, TD_SINGLE_HOLD, TD_DOUBLE_SINGLE_TAP } td_state_t;

// Create a global instance of the tap-dance state type
static td_state_t td_state;

// Function to determine the current tap-dance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tap-dance keycode
void ctllb_finished(qk_tap_dance_state_t *state, void *user_data);
void ctllb_reset(qk_tap_dance_state_t *state, void *user_data);
void sftrb_finished(qk_tap_dance_state_t *state, void *user_data);
void sftrb_reset(qk_tap_dance_state_t *state, void *user_data);

void sftlp_finished(qk_tap_dance_state_t *state, void *user_data);
void sftlp_reset(qk_tap_dance_state_t *state, void *user_data);
void ctlrp_finished(qk_tap_dance_state_t *state, void *user_data);
void ctlrp_reset(qk_tap_dance_state_t *state, void *user_data);

#define TG_GAME TG(L_GAME)
#define MO_GAME_CUR MO(L_GAME_CUR)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      TG_GAME,    KC_Q,    KC_F,    KC_U,    KC_Y,    KC_Z,                         KC_X,    KC_K,    KC_C,    KC_W,    KC_B, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSLS,     H_O,     H_H,     H_E,     H_A,    KC_I,                         KC_D,     H_R,     H_T,     H_N,     H_S, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_COMM,    KC_M,  KC_DOT,    KC_J, KC_SCLN,                         KC_G,    KC_L,    KC_P,    KC_V, KC_LBRC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, KC_TAB, SYM_ENT,   CUR_SPC, KC_PSCR,  KC_CAPS
                                      //`--------------------------'  `--------------------------'
  ),
  [L_CUR] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL, KC_PGDN,                      XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  H_HOME,  H_LEFT,  H_DOWN, H_RIGHT,  KC_END,                         KC_0,     H_4,     H_5,     H_6, KC_LALT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, CTL_PGU, CTL_PGD, XXXXXXX,                      XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _______, KC_ESC, _______,  _______, _______,  _______
                                      //`--------------------------'  `--------------------------'
  ),
  [L_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_DQUO, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC,                      KC_EXLM,   KC_LT,   KC_GT,  KC_EQL, KC_AMPR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, H_SLSH,  H_MINS,  H_LCBR,  H_RCBR,  KC_ASTR,                      KC_QUES,   H_LPRN, H_RPRN,  H_QUOT, KC_LALT, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_HASH, KC_DLR, KC_PIPE, KC_TILD,  KC_GRV,                       KC_PLUS,  KC_PERC, KC_BSLS,   KC_AT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,  _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
  [L_GAME] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      TG_GAME,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,       KC_O, KC_P, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,        KC_K,    KC_L, KC_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM,    KC_DOT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_SPC, KC_TAB, SYM_ENT,   MO_GAME_CUR, KC_PSCR, KC_CAPS
                                      //`--------------------------'  `--------------------------'
  ),
  [L_GAME_CUR] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_PGUP, KC_BSPC, KC_UP,  KC_DEL,  KC_PGDN,                      XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, H_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,                         KC_0,     H_4,     H_5,     H_6,    H_NO, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, CTL_PGU, CTL_PGD, XXXXXXX,                      XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_ESC, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case L_CUR:
            oled_write_ln_P(PSTR("Cur"), false);
            break;
        case L_SYM:
            oled_write_ln_P(PSTR("Sym"), false);
            break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return TD_SINGLE_TAP;
        else
            return TD_SINGLE_HOLD;
    }

    if (state->count == 2)
        return TD_DOUBLE_SINGLE_TAP;
    else
        return TD_UNKNOWN;
}

void sftlp_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_LPRN);
            register_code16(KC_LPRN);
            break;
        default:
            break;
    }
}

void sftlp_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        default:
            break;
    }
}

void ctlrp_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_RPRN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_RPRN);
            register_code16(KC_RPRN);
            break;
        default:
            break;
    }
}

void ctlrp_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_RPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_RPRN);
            break;
        default:
            break;
    }
}

void sftrb_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_RCBR);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_RCBR);
            register_code16(KC_RCBR);
            break;
        default:
            break;
    }
}

void sftrb_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_RCBR);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_RCBR);
            break;
        default:
            break;
    }
}

void ctllb_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LCBR);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_LCBR);
            register_code16(KC_LCBR);
            break;
        default:
            break;
    }
}

void ctllb_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        default:
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [CTL_LB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctllb_finished, ctllb_reset),
    [SFT_RB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftrb_finished, sftrb_reset),

    [SFT_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftlp_finished, sftlp_reset),
    [CTL_RP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctlrp_finished, ctlrp_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    switch (keycode) {
        case KEYCODES_START:
            if (record->event.pressed) {
            }
            return false;
        case CTL_PGU:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_PGUP);
                unregister_code(KC_LCTL);
                unregister_code(KC_PGUP);
            }
            return false;
        case CTL_PGD:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_PGDN);
                unregister_code(KC_LCTL);
                unregister_code(KC_PGDN);
            }
            return false;
    }
    return true;
}
