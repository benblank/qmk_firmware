/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    BASE,
    WASD,
    MCTL,
    FN,
    NUM_LAYERS,
};

// This is just so the columns still line up (it's one character shorter).
#define TG_MCTL TG(MCTL)

const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [BASE] = LAYOUT_tkl_ansi(
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_MUTE, KC_PSCR, KC_ASST, KC_CALC,
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_INS , KC_HOME, KC_PGUP,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL , KC_END , KC_PGDN,
        KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,
        KC_LSFT,          KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT,          KC_UP  ,
        KC_LCTL, KC_LCMD, KC_LALT,                            KC_SPC ,                            KC_RALT, KC_RWIN, MO(FN) , KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [WASD] = LAYOUT_tkl_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_Y   , KC_Q   , KC_SPC , KC_E   , KC_R   , KC_T   , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_H   , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , _______, _______, _______, _______, _______,          _______,
        _______,          KC_B   , KC_Z   , KC_X   , KC_C   , KC_V   , KC_N   , _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______,                            KC_W   ,                            _______, _______, _______, _______, _______, _______, _______
    ),

    [MCTL] = LAYOUT_tkl_ansi(
        _______, _______, _______, _______, _______, KC_F5  , KC_F7  , KC_F9  , KC_F12 , KC_MPRV, KC_MRWD, KC_MFFD, KC_MNXT, KC_MPLY, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______
    ),

    [FN] = LAYOUT_tkl_ansi(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TG_MCTL, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______
    ),
    // clang-format on
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[NUM_LAYERS][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WASD] = {ENCODER_CCW_CW(_______, _______)},
    [MCTL] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

#if defined(DIP_SWITCH_ENABLE)
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        if (active) {
            layer_on(WASD);
        } else {
            layer_off(WASD);
        }

        return false;
    }

    return true;
}
#endif // DIP_SWITCH_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

#if defined(RGB_MATRIX_ENABLE)
bool rgb_matrix_indicators_user() {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(50, RGB_RED);
    }

    if (IS_LAYER_ON(WASD)) {
        rgb_matrix_set_color(36, RGB_BLUE); // E
        rgb_matrix_set_color(52, RGB_BLUE); // S
        rgb_matrix_set_color(53, RGB_BLUE); // D
        rgb_matrix_set_color(54, RGB_BLUE); // F
    }

    if (IS_LAYER_ON(MCTL)) {
        rgb_matrix_set_color(5, RGB_GREEN); // F5
        rgb_matrix_set_color(6, RGB_GREEN); // F6
        rgb_matrix_set_color(7, RGB_GREEN); // F7
        rgb_matrix_set_color(8, RGB_GREEN); // F8
        rgb_matrix_set_color(9, RGB_BLUE);  // F9
        rgb_matrix_set_color(10, RGB_BLUE); // F10
        rgb_matrix_set_color(11, RGB_BLUE); // F11
        rgb_matrix_set_color(12, RGB_BLUE); // F12
    }

    return false;
}
#endif // RGB_MATRIX_ENABLE
