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

you should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <stdint.h>

#define CUSTOM_SAFE_RANGE SAFE_RANGE
#include "lang_shift/include.h"

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_CUR 5
#define L_SYM 6
#define L_SPEC 7
#define L_ADJUST 8

// English layer
//
// Left-hand home row mods
#define H_O LALT_T(KC_O)
#define H_H LGUI_T(KC_H)
#define H_E LCTL_T(KC_E)
#define H_A LSFT_T(KC_A)

// Right-hand home row mods
#define H_R RSFT_T(KC_R)
#define H_T RCTL_T(KC_T)
#define H_N RGUI_T(KC_N)
#define H_S LALT_T(KC_S)

// Symbol layer
//
// Left-hand home row mods
#define H_SLSH TD(ALT_SL)
#define H_MINS TD(GUI_MN)
#define H_LCBR TD(CTL_LB)
#define H_RCBR TD(SFT_RB)

// Right-hand home row mods
#define H_LPRN TD(SFT_LP)
#define H_RPRN TD(CTL_RP)
#define H_QUOT TD(GUI_QT)
#define H_COLN TD(ALT_CL)

// Cursor layer
//
// Left-hand home row mods
#define H_HOME LALT_T(KC_HOME)
#define H_LEFT LGUI_T(KC_LEFT)
#define H_DOWN LCTL_T(KC_DOWN)
#define H_RIGHT LSFT_T(KC_RIGHT)

// Right-hand home row mods
#define H_4 RSFT_T(KC_4)
#define H_5 RCTL_T(KC_5)
#define H_6 RGUI_T(KC_6)
#define H_NO LALT_T(KC_NO)

// Mod key
#define CUR_SPC LT(L_CUR, KC_SPC)
#define SYM_ENT LT(L_SYM, KC_ENT)
#define SPEC_PSCR LT(L_SPEC, KC_PSCR)

enum custom_keycodes {
    KEYCODES_START = CUSTOM_SAFE_RANGE,

    CTL_PGU,
    CTL_PGD,
};

// Tap Dance keycodes
enum td_keycodes {
    ALT_SL,
    GUI_MN,
    CTL_LB,
    SFT_RB,

    SFT_LP,
    CTL_RP,
    GUI_QT,
    ALT_CL,
};

// Define a type containing as many tap-dance states as you need
typedef enum { TD_NONE, TD_UNKNOWN, TD_SINGLE_TAP, TD_SINGLE_HOLD, TD_DOUBLE_SINGLE_TAP } td_state_t;

// Create a global instance of the tap-dance state type
static td_state_t td_state;

// Declare your tap-dance functions:

// Function to determine the current tap-dance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tap-dance keycode
void altsl_finished(qk_tap_dance_state_t *state, void *user_data);
void altsl_reset(qk_tap_dance_state_t *state, void *user_data);
void guimn_finished(qk_tap_dance_state_t *state, void *user_data);
void guimn_reset(qk_tap_dance_state_t *state, void *user_data);
void ctllb_finished(qk_tap_dance_state_t *state, void *user_data);
void ctllb_reset(qk_tap_dance_state_t *state, void *user_data);
void sftrb_finished(qk_tap_dance_state_t *state, void *user_data);
void sftrb_reset(qk_tap_dance_state_t *state, void *user_data);

void sftlp_finished(qk_tap_dance_state_t *state, void *user_data);
void sftlp_reset(qk_tap_dance_state_t *state, void *user_data);
void ctlrp_finished(qk_tap_dance_state_t *state, void *user_data);
void ctlrp_reset(qk_tap_dance_state_t *state, void *user_data);
void guiqt_finished(qk_tap_dance_state_t *state, void *user_data);
void guiqt_reset(qk_tap_dance_state_t *state, void *user_data);
void altcl_finished(qk_tap_dance_state_t *state, void *user_data);
void altcl_reset(qk_tap_dance_state_t *state, void *user_data);

//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_F,    KC_U,    KC_Y,    KC_Z,                         KC_X,    KC_K,    KC_C,    KC_W,    KC_B, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,     H_O,     H_H,     H_E,     H_A,    KC_I,                         KC_D,     H_R,     H_T,     H_N,     H_S, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, AG_COMM,    KC_M,  AG_DOT,    KC_J, AG_SCLN,                         KC_G,    KC_L,    KC_P,    KC_V, KC_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, KC_TAB, SYM_ENT,   CUR_SPC, SPEC_PSCR,  KC_CAPS
                                      //`--------------------------'  `--------------------------'
  ),
  [L_SPEC] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL, KC_PGDN,                      XXXXXXX,    AG_1,    AG_2,    AG_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,  H_HOME,  H_LEFT,  H_DOWN, H_RIGHT,  KC_END,                         AG_0,     H_4,     H_5,     H_6,    H_NO, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, CTL_PGU, CTL_PGD, XXXXXXX,                      XXXXXXX,    AG_7,    AG_8,    AG_9, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, KC_ESC, SYM_ENT,  XXXXXXX,   XXXXXXX,    XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
  [L_CUR] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL, KC_PGDN,                      LA_CHNG,    AG_1,    AG_2,    AG_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,  H_HOME,  H_LEFT,  H_DOWN, H_RIGHT,  KC_END,                         AG_0,     H_4,     H_5,     H_6,    H_NO, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, CTL_PGU, CTL_PGD, XXXXXXX,                      LA_SYNC,    AG_7,    AG_8,    AG_9, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           XXXXXXX, KC_ESC, SYM_ENT,  XXXXXXX,   XXXXXXX,    XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
  [L_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, AG_DQUO, AG_UNDS, EN_LBRC, EN_RBRC, EN_CIRC,                      AG_EXCL,   EN_LT,   EN_GT,  AG_EQL, EN_AMPR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, H_SLSH,  H_MINS,  H_LCBR,  H_RCBR,  AG_ASTR,                      AG_QUES,   H_LPRN, H_RPRN,  H_QUOT,  H_COLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, EN_HASH,  EN_DLR, EN_PIPE, EN_TILD,  EN_GRV,                      AG_PLUS, AG_PERC, AG_BSLS,   EN_AT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,  CUR_SPC,   XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};
// Determine the tapdance state to return
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
        return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

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
            register_mods(MOD_BIT(KC_RCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
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
            unregister_mods(MOD_BIT(KC_RCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_RPRN);
            break;
        default:
            break;
    }
}

void guiqt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RGUI)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_QUOT);
            register_code16(KC_QUOT);
            break;
        default:
            break;
    }
}

void guiqt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RGUI)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_QUOT);
            break;
        default:
            break;
    }
}

void altcl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
//            register_code16(KC_COLN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
//            tap_code16(KC_COLN);
//            register_code16(KC_COLN);
            break;
        default:
            break;
    }
}

void altcl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_COLN);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_COLN);
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
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
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
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
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
            register_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
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
            unregister_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        default:
            break;
    }
}

void guimn_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_MINS);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_MINS);
            register_code16(KC_MINS);
            break;
        default:
            break;
    }
}

void guimn_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_MINS);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_MINS);
            break;
        default:
            break;
    }
}

void altsl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_SLSH);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_SLSH);
            register_code16(KC_SLSH);
            break;
        default:
            break;
    }
}

void altsl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_SLSH);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SLSH);
            break;
        default:
            break;
    }
}
qk_tap_dance_action_t tap_dance_actions[] = {[ALT_SL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altsl_finished, altsl_reset), [GUI_MN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guimn_finished, guimn_reset), [CTL_LB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctllb_finished, ctllb_reset), [SFT_RB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftrb_finished, sftrb_reset), [SFT_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftlp_finished, sftlp_reset), [CTL_RP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctlrp_finished, ctlrp_reset), [GUI_QT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guiqt_finished, guiqt_reset), [ALT_CL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altcl_finished, altcl_reset)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!lang_shift_process_record(keycode, record)) return false;

    switch (keycode) {
        case CTL_PGU:
            if (record->event.pressed) {
                register_code(KC_LCTRL);
                register_code(KC_PGUP);
                unregister_code(KC_LCTRL);
                unregister_code(KC_PGUP);
            }
            return false;
        case CTL_PGD:
            if (record->event.pressed) {
                register_code(KC_LCTRL);
                register_code(KC_PGDN);
                unregister_code(KC_LCTRL);
                unregister_code(KC_PGDN);
            }
            return false;
    }
    return true;
}

void user_timer(void) {
    lang_shift_user_timer();
}

void matrix_scan_user(void) {
    user_timer();
}
