// #include QMK_KEYBOARD_H

// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// 	LAYOUT(
// 		KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
// 		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
// 		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
// 		KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO,
// 		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_RALT, MO(2), KC_NO, MO(1), KC_RCTL),

// 	LAYOUT(
// 		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_DEL,
// 		KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
// 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
// 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC, BL_TOGG, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
// 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

// 	LAYOUT(
// 		KC_TRNS, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12), KC_TRNS, KC_TRNS,
// 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
// 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
// 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
// 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
// };

// using as reference
// https://docs.qmk.fm/#/keymap

// thanks to atlacat, hailbreno, itsaferbie and weeheavy...

// and special thanks to  AGausmann and drashna for the layer-activated RGB underglow
// https://www.reddit.com/r/olkb/comments/6t1vdu/update_layeractivated_rgb_underglow/
// https://github.com/AGausmann/qmk_firmware/blob/agausmann-v3.x/keyboards/nyquist/keymaps/agausmann/keymap.c

#include QMK_KEYBOARD_H
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0


typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

//Tap dance enums
enum {
  ALT = 0,
  BASE_SPACE = 1,
  NUM_SPACE = 2,
  BASE_ENT = 3,
  ARW_ENT = 4
};

int cur_dance (qk_tap_dance_state_t *state);
void base_space_finished (qk_tap_dance_state_t *state, void *user_data);
void base_space_reset (qk_tap_dance_state_t *state, void *user_data);
void base_ent_finished (qk_tap_dance_state_t *state, void *user_data);
void base_ent_reset (qk_tap_dance_state_t *state, void *user_data);
void arrows_finished (qk_tap_dance_state_t *state, void *user_data);
void arrows_reset (qk_tap_dance_state_t *state, void *user_data);
void numbers_finished (qk_tap_dance_state_t *state, void *user_data);
void numbers_reset (qk_tap_dance_state_t *state, void *user_data);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);


/* LAYOUT_60_ansi_iso_split
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐2d  │
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │1e │    │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │   30   │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d        │
 * ├────┬───┴┬──┴─┬─┴───┴──┬┴───┼───┴───┴──┬┴───┼───┴┬────┬────┤
 * │40  │41  │43  │44      │46  │48        │4a  │4b  │4d  │4e  │
 * └────┴────┴────┴────────┴────┴──────────┴────┴────┴────┴────┘
*/
#define LAYOUT_minivan( \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,      \
    k40, k41,      k43, k44,            k48,      k4a, k4b,      k4d \
) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO,KC_NO,KC_NO }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,KC_NO,   KC_NO   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,KC_NO,   KC_NO }, \
    { k30,  KC_NO,   k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   KC_NO }, \
    { k40,  k41,   KC_NO, k43,  k44,   KC_NO, KC_NO, KC_NO, k48,   KC_NO, k4a,  k4b,  KC_NO, k4d,   KC_NO   } \
}

/*
* Each layer gets a name for readability.
* The underscores don't mean anything - you can
* have a layer called STUFF or any other name.
* Layer names don't all need to be of the same
* length, and you can also skip them entirely
* and just use numbers.
*
*/
#define BASE 0     // Base Layer
#define NUMBERS 1         // Secondary Layer
#define ARROWS 2         // Mouse Layer
#define FN 4         // Function Layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap BL: Base Layer (Default Layer)
   *
   * ,-----------------------------------------------------------.
   * | ' | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | =|ESC|Back|
   * |-----------------------------------------------------------|
   * | Tab | q | w | e | r | t | y | u | i | o | p | [ | ] |Enter|
   * |------------------------------------------------------     |
   * | Back  | a | s | d | f | g | h | j | k | l | ; | ' | \ |   |
   * |-----------------------------------------------------------|
   * |Shft    | z | x | c | v | b | n | m | , | . | / |  Shift   |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt | Space  | AK |  Enter |FN |Alt | Menu |Ctrl |
   * `-----------------------------------------------------------'
   */
   [BASE] = LAYOUT_minivan(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        KC_TAB ,   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,
        KC_BSPC,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,
        KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,
        KC_LCTL,   KC_LGUI,   TD(ALT), LT(NUMBERS, KC_SPC),     LT(ARROWS, KC_ENT),    MO(FN),  TO(NUMBERS),   TO(ARROWS)),

  /* Keymap Secondary: Numbers
   *
   * ,-----------------------------------------------------------.
   * |ESC|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|ESC|BAK|
   * |-----------------------------------------------------------|
   * |     | hm| u |end|pup|   |   |   |   |   |   |   |   |      |
   * |------------------------------------------------------     |
   * |       | l | d | r |pdn|   |   | l | d | u | r |   |   |   |
   * |-----------------------------------------------------------|
   * |         |   |   |   |   |   |   |    |   |   |   |         |
   * |-----------------------------------------------------------|
   * |    |    |    |        |    |         |    |    |    |     |
   * `-----------------------------------------------------------'
   */
   [NUMBERS] = LAYOUT_minivan(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        KC_MINS,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_EQL,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,              KC_ENT,    _______,   TO(BASE),   _______),

  /* Keymap FN: Mouse Layer
   *
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |------------------------------------------------------     |
   * |       |   |   |   |   |   |   |   |   |   |   |   |   |   |
   * |-----------------------------------------------------------|
   * |    |   |   |   |   |   |   |   |    |   |   |   |         |
   * |-----------------------------------------------------------|
   * |    |    |    |        |    |         |    |    |    |     |
   * `-----------------------------------------------------------'
   */
   [ARROWS] = LAYOUT_minivan(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        KC_ESC,    KC_HOME,   KC_UP,     KC_END,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_RBRC,
        KC_DELT,   KC_LEFT,   KC_DOWN,   KC_RIGHT,  _______,   _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______,   KC_GRAVE,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_BSLS,   _______,
        _______,   _______,   _______,   KC_SPC,               _______,   _______,   _______,   TO(BASE)),

  /* Keymap FN: Function Layer
   *
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
   * |-----------------------------------------------------------|
   * |     |MUT|VDN|VUP|   |   |   |   |   |   |   |RGB|RGB|     |
   * |------------------------------------------------------     |
   * |       |MPR|MPA|MNX|   |   |   |   |   |   |   |   |   |   |
   * |-----------------------------------------------------------|
   * |         |BRD|BRU|   |   |   |   |   |    |   |   |   |    |
   * |-----------------------------------------------------------|
   * |    |    |    |        |    |         |    |    |    |     |
   * `-----------------------------------------------------------'
   */

   [FN] = LAYOUT_minivan(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        KC_F11,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F12,
        _______,   KC_MUTE,   KC_VOLD,   KC_VOLU,   _______,   _______,   _______,   _______,   _______,   RGB_VAD,   RGB_VAI,   _______,
        _______,   KC_MPRV,   KC_MPLY,   KC_MNXT,   _______,   _______,   _______,   _______,   _______,   KC_BRID,   KC_BRIU,   _______,
        RESET,     _______,   _______,   _______,              _______,   _______,   _______,   _______)

};

//   _____            ___
//  |_   _|_ _ _ __  |   \ __ _ _ _  __ ___
//    | |/ _` | '_ \ | |) / _` | ' \/ _/ -_)
//    |_|\__,_| .__/ |___/\__,_|_||_\__\___|
//            |_|


int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [ALT]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset),
  [BASE_SPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,base_space_finished, base_space_reset),
  [BASE_ENT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,base_ent_finished, base_ent_reset),
  [NUM_SPACE]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL,numbers_finished, numbers_reset),
  [ARW_ENT]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL,arrows_finished, arrows_reset),
};

//   ___                 ___
//  | _ ) __ _ ___ ___  |   \ __ _ _ _  __ ___
//  | _ \/ _` (_-</ -_) | |) / _` | ' \/ _/ -_)
//  |___/\__,_/__/\___| |___/\__,_|_||_\__\___|

void base_space_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: register_code(KC_SPC); break;
    case SINGLE_HOLD: layer_on(NUMBERS); break;
    case DOUBLE_TAP: layer_on(NUMBERS); break;
    case DOUBLE_HOLD: register_code(KC_SPC); break;

    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void base_space_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD: layer_off(NUMBERS); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: unregister_code(KC_SPC); break;
  }
  alttap_state.state = 0;
}

void base_ent_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: register_code(KC_ENT); break;
    case SINGLE_HOLD: layer_on(ARROWS); break;
    case DOUBLE_TAP: layer_on(ARROWS); break;
    case DOUBLE_HOLD: register_code(KC_ENT); break;

    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void base_ent_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: unregister_code(KC_ENT); break;
    case SINGLE_HOLD: layer_off(ARROWS); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: unregister_code(KC_ENT); break;
  }
  alttap_state.state = 0;
}

//   ___                     _                 ___
// NUMBERS
//                                      |__/

void numbers_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case DOUBLE_TAP: layer_on(NUMBERS); break;
    case SINGLE_TAP:
    case SINGLE_HOLD:
    case DOUBLE_HOLD: register_code(KC_SPC); break;

    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void numbers_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case DOUBLE_TAP: layer_off(NUMBERS); break;
    case SINGLE_HOLD:
    case SINGLE_TAP:
    case DOUBLE_HOLD: unregister_code(KC_SPC); break;
  }
  alttap_state.state = 0;
}

//   __  __                    ___
// Arrows

void arrows_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case DOUBLE_TAP: layer_on(ARROWS); break;
    case SINGLE_TAP:
    case SINGLE_HOLD:
    case DOUBLE_HOLD: register_code(KC_ENT); break;

    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void arrows_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case DOUBLE_TAP: layer_off(ARROWS); break;
    case SINGLE_HOLD:
    case SINGLE_TAP:
    case DOUBLE_HOLD: unregister_code(KC_ENT); break;
  }
  alttap_state.state = 0;
}

//     _   _  _____    ___  ___ _      ___ _   _ _  _  ___ _____ ___ ___  _  _   _    ___   ___ ___ ___
//    /_\ | ||_   _|  / _ \/ __| |    | __| | | | \| |/ __|_   _|_ _/ _ \| \| | | |  / _ \ / __|_ _/ __|
//   / _ \| |__| |   | (_) \__ \ |__  | _|| |_| | .` | (__  | |  | | (_) | .` | | |_| (_) | (_ || | (__
//  /_/ \_\____|_|    \___/|___/____| |_|  \___/|_|\_|\___| |_| |___\___/|_|\_| |____\___/ \___|___\___|


void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(FN, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: set_oneshot_layer(FN, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(FN); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(FN); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case RESET:
      /* Don't allow reset from oneshot layer state */
      if (record->event.pressed && is_oneshot_layer_active()){
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }
      return true;
    default:
      return true;
  }
  return true;
}


//   _                               _   _          _          _   ___  ___ ___                _              _
//  | |__ _ _  _ ___ _ _ ___ __ _ __| |_(_)_ ____ _| |_ ___ __| | | _ \/ __| _ )  _  _ _ _  __| |___ _ _ __ _| |_____ __ __
//  | / _` | || / -_) '_|___/ _` / _|  _| \ V / _` |  _/ -_) _` | |   / (_ | _ \ | || | ' \/ _` / -_) '_/ _` | / _ \ V  V /
//  |_\__,_|\_, \___|_|     \__,_\__|\__|_|\_/\__,_|\__\___\__,_| |_|_\\___|___/  \_,_|_||_\__,_\___|_| \__, |_\___/\_/\_/
//          |__/                                                                                        |___/


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
    rgblight_enable();
}


void matrix_scan_user(void) {
  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
      case BASE:
          //rgblight_sethsv_noeeprom_azure();
          rgblight_sethsv_noeeprom (132, 102, rgblight_get_val());
        break;
      case ARROWS:
          //rgblight_sethsv_noeeprom_coral();
          rgblight_sethsv_noeeprom (11, 176, rgblight_get_val());
        break;
      case NUMBERS:
          //rgblight_sethsv_noeeprom_magenta();
          rgblight_sethsv_noeeprom (213, 255, rgblight_get_val());
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE
}
