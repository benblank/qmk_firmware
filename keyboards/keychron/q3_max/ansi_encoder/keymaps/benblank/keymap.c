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

#include "keyboard.h"
#include "quantum.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

#include "./aliases.h"

enum layers {
    /** The base layer.
     *
     * Uses the encoder for volume/mute and uses the Fn key to activate the FN
     * layer while held. The Pause/Break key is replaced with Calculator.
     *
     * Caps Lock is indicated by changing its color to red and Caps Word by
     * changing Left Shift's color to green.
     */
    BASE,

    /** WASD mode.
     *
     * I'm used to a weird variant of WASD which both shifts it to ESDF *and*
     * swaps the W/E and Space keys. In order to accomodate games which don't
     * support remapping their controls that way (or for which I decide it's too
     * much trouble), WASD mode adapts the keyboard instead.
     *
     * Specifically, it rotates left the first six alpha keys in the Q row, the
     * first six keys in the A row, and the first *five* keys in the Z row (N is
     * left as-is on the theory that many games use B for "backpack", so since
     * I'm rearranging things anyway, I might as well put it somewhere handy).
     * The W key is also swapped with Space.
     *
     * Activated by the keyboard's "Mac/Win" DIP switch; "Win" activates WASD
     * Mode, while "Mac" disables it. Identified by ESDF changing to blue.
     */
    WASD,

    /** Media control mode.
     *
     * Remaps F9-F12 to Previous Track, Rewind¹, Fast Forward¹, and Next Track
     * and the encoder press to Play. Because F9 and F12 are useful in many
     * games, F5-F8 are also remapped to F5, F7, F8, and F12. (Yes, F5 is
     * "remapped" to F5.)
     *
     * Activated by pressing Fn+Encoder. Identified by F5-F8 changing to green
     * and F9-F12 changing to blue.
     *
     * ¹ I haven't had much luck with media players responding to the Rewind and
     * Fast Forward keys, unfortunately.
     */
    MEDIA,

    /** Function layer.
     *
     * Not heavily used, right now, but toggles media control by pressing the
     * encoder, toggles autocorrect with A, and enters boot mode with Escape.
     * The brightness of the default key backlights can be adjusted with the
     * encoder.
     */
    FN,

    NUM_LAYERS,
};

const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [BASE] = LAYOUT_tkl_ansi(
//┌──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┐┌──────┬──────┬──────┐
    ESC_ ,  _F1_ , _F2_ , _F3_ , _F4_ ,  _F5_ , _F6_ , _F7_ , _F8_ ,  _F9_ , F10_ , F11_ , F12_ ,  MUTE ,  PSCR , SCRL , CALC ,
//└──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┘└──────┴──────┴──────┘
//┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────────┐┌──────┬──────┬──────┐
    GRV_ , _1__ , _2__ , _3__ , _4__ , _5__ , _6__ , _7__ , _8__ , _9__ , _0__ , MINU , EQL_ ,   BACK   ,  INS_ , HOME , PGUP ,
//├──────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────────┤├──────┼──────┼──────┤
     TAB_  , _Q__ , _W__ , _E__ , _R__ , _T__ , _Y__ , _U__ , _I__ , _O__ , _P__ , LBRC , RBRC ,  BSLS  ,  DEL_ , END_ , PGDN ,
//├────────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴────────┤└──────┴──────┴──────┘
      CAPS   , _A__ , _S__ , _D__ , _F__ , _G__ , _H__ , _J__ , _K__ , _L__ , SEMI , QUOT ,    ENT_     ,
//├──────────┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴─────────────┤       ┌──────┐
        SHF_     , _Z__ , _X__ , _C__ , _V__ , _B__ , _N__ , _M__ , COMM , DOT_ , SLSH ,      _SHF      ,         _UP_ ,
//├────────┬─────┴──┬───┴──┬───┴──────┴──────┴──────┴──────┴──────┴─────┬┴─────┬┴──────┴┬──────┬────────┤┌──────┼──────┼──────┐
     CTL_  ,  GUI_  , ALT_ ,                     SPC_                   , _ALT ,  _GUI  , H_FN ,  _CTL  ,  LEFT , DOWN , RGHT
//└────────┴────────┴──────┴────────────────────────────────────────────┴──────┴────────┴──────┴────────┘└──────┴──────┴──────┘
    ),

    [WASD] = LAYOUT_tkl_ansi(
//┌──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┐┌──────┬──────┬──────┐
    ____ ,  ____ , ____ , ____ , ____ ,  ____ , ____ , ____ , ____ ,  ____ , ____ , ____ , ____  , ____ ,  ____ , ____ , ____ ,
//└──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┘└──────┴──────┴──────┘
//┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────────┐┌──────┬──────┬──────┐
    ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ ,   ____   ,  ____ , ____ , ____ ,
//├──────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────────┤├──────┼──────┼──────┤
     ____  , _Y__ , _Q__ , SPC_ , _E__ , _R__ , _T__ , ____ , ____ , ____ , ____ , ____ , ____ ,  ____  ,  ____ , ____ , ____ ,
//├────────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴────────┤└──────┴──────┴──────┘
      ____   , _H__ , _A__ , _S__ , _D__ , _F__ , _G__ , ____ , ____ , ____ , ____ , ____ ,    ____     ,
//├──────────┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴─────────────┤       ┌──────┐
        ____     , _B__ , _Z__ , _X__ , _C__ , _V__ , ____ , ____ , ____ , ____ , ____ ,      ____      ,         ____ ,
//├────────┬─────┴──┬───┴──┬───┴──────┴──────┴──────┴──────┴──────┴─────┬┴─────┬┴──────┴┬──────┬────────┤┌──────┼──────┼──────┐
     ____  ,  ____  , ____ ,                    _W__                    , ____ ,  ____  , ____ ,  ____  ,  ____ , ____ , ____
//└────────┴────────┴──────┴────────────────────────────────────────────┴──────┴────────┴──────┴────────┘└──────┴──────┴──────┘
    ),

    [MEDIA] = LAYOUT_tkl_ansi(
//┌──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┐┌──────┬──────┬──────┐
    ____ ,  ____ , ____ , ____ , ____ ,  _F5_ , _F7_ , _F8_ , F12_ ,  PREV , REW_ , FWD_ , NEXT ,  PLAY ,  ____ , ____ , ____ ,
//└──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┘└──────┴──────┴──────┘
//┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────────┐┌──────┬──────┬──────┐
    ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ ,   ____   ,  ____ , ____ , ____ ,
//├──────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────────┤├──────┼──────┼──────┤
     ____  , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ ,  ____  ,  ____ , ____ , ____ ,
//├────────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴────────┤└──────┴──────┴──────┘
      ____   , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ ,    ____     ,
//├──────────┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴─────────────┤       ┌──────┐
        ____     , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ , ____ ,      ____      ,         ____ ,
//├────────┬─────┴──┬───┴──┬───┴──────┴──────┴──────┴──────┴──────┴─────┬┴─────┬┴──────┴┬──────┬────────┤┌──────┼──────┼──────┐
     ____  ,  ____  , ____ ,                    ____                    , ____ ,  ____  , ____ ,  ____  ,  ____ , ____ , ____
//└────────┴────────┴──────┴────────────────────────────────────────────┴──────┴────────┴──────┴────────┘└──────┴──────┴──────┘
    ),

    [FN] = LAYOUT_tkl_ansi(
//┌──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┬──────┬──────┬──────┐┌──────┐┌──────┬──────┬──────┐
    BOOT ,  NONE , NONE , NONE , NONE ,  NONE , NONE , NONE , NONE ,  NONE , NONE , NONE , NEXT ,  T_MC ,  NONE , NONE , NONE ,
//└──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┴──────┴──────┴──────┘└──────┘└──────┴──────┴──────┘
//┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────────┐┌──────┬──────┬──────┐
    NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE ,   NONE   ,  NONE , NONE , NONE ,
//├──────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────────┤├──────┼──────┼──────┤
     NONE  , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE ,  NONE  ,  NONE , NONE , NONE ,
//├────────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴────────┤└──────┴──────┴──────┘
      NONE   , T_AC , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE ,    NONE     ,
//├──────────┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴─────────────┤       ┌──────┐
        NONE     , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE , NONE ,      NONE      ,         NONE ,
//├────────┬─────┴──┬───┴──┬───┴──────┴──────┴──────┴──────┴──────┴─────┬┴─────┬┴──────┴┬──────┬────────┤┌──────┼──────┼──────┐
     NONE  ,  NONE  , NONE ,                    KMGC                    , NONE ,  NONE  , NONE ,  NONE  ,  NONE , NONE , NONE
//└────────┴────────┴──────┴────────────────────────────────────────────┴──────┴────────┴──────┴────────┘└──────┴──────┴──────┘
    ),
    // clang-format on
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[NUM_LAYERS][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE]  = {ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP)},
    [WASD]  = {ENCODER_CCW_CW(KC_TRANSPARENT, KC_TRANSPARENT)},
    [MEDIA] = {ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP)},
    [FN]    = {ENCODER_CCW_CW(RGB_BRIGHTNESS_DOWN, RGB_BRIGHTNESS_UP)},
};
#endif // ENCODER_MAP_ENABLE

#if defined(COMBO_ENABLE)
enum combos {
#    if defined(KEY_LOCK_ENABLE)
    MOD_LOCK,
#    endif
    NUM_COMBOS,
};

#    if defined(KEY_LOCK_ENABLE)
const uint16_t PROGMEM mod_lock[] = {KC_LEFT_SHIFT, KC_RIGHT_SHIFT, COMBO_END};
#    endif

combo_t key_combos[NUM_COMBOS] = {
#    if defined(KEY_LOCK_ENABLE)
    [MOD_LOCK] = COMBO(mod_lock, QK_LOCK),
#    endif
};
#endif

// TODO?: disable caps lock in caps_word_set_user(true)

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

void keyboard_post_init_user() {
#if defined(AUTOCORRECT_ENABLE)
    autocorrect_enable();
#endif
}

#if defined(RGB_MATRIX_ENABLE)
bool rgb_matrix_indicators_user() {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(LED_CAPS, RGB_RED);
    }

    if (is_caps_word_on()) {
        rgb_matrix_set_color(LED_LSFT, RGB_GREEN);
    }

#    if defined(KEY_LOCK_ENABLE)
    // TODO?: figure out a way to use get_locked_keys() to change the color of *all* locked keys

    if (is_key_locked(KC_LSFT)) rgb_matrix_set_color(LED_LSFT, RGB_RED);
    if (is_key_locked(KC_RSFT)) rgb_matrix_set_color(LED_RSFT, RGB_RED);
    if (is_key_locked(KC_LCTL)) rgb_matrix_set_color(LED_LCTL, RGB_RED);
    if (is_key_locked(KC_LGUI)) rgb_matrix_set_color(LED_LGUI, RGB_RED);
    if (is_key_locked(KC_LALT)) rgb_matrix_set_color(LED_LALT, RGB_RED);
    if (is_key_locked(KC_RALT)) rgb_matrix_set_color(LED_RALT, RGB_RED);
    if (is_key_locked(KC_RGUI)) rgb_matrix_set_color(LED_RGUI, RGB_RED);
    if (is_key_locked(KC_RCTL)) rgb_matrix_set_color(LED_RCTL, RGB_RED);
#    endif

    if (IS_LAYER_ON(WASD)) {
        rgb_matrix_set_color(LED_E, RGB_BLUE);
        rgb_matrix_set_color(LED_S, RGB_BLUE);
        rgb_matrix_set_color(LED_D, RGB_BLUE);
        rgb_matrix_set_color(LED_F, RGB_BLUE);
    }

    if (IS_LAYER_ON(MEDIA)) {
        rgb_matrix_set_color(LED_F5, RGB_GREEN);
        rgb_matrix_set_color(LED_F6, RGB_GREEN);
        rgb_matrix_set_color(LED_F7, RGB_GREEN);
        rgb_matrix_set_color(LED_F8, RGB_GREEN);
        rgb_matrix_set_color(LED_F9, RGB_CYAN);
        rgb_matrix_set_color(LED_F10, RGB_BLUE);
        rgb_matrix_set_color(LED_F11, RGB_BLUE);
        rgb_matrix_set_color(LED_F12, RGB_CYAN);
    }

    return false;
}
#endif // RGB_MATRIX_ENABLE
