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
  ALT_OSL1 = 0,
  MOD_BASE = 1,
  MOD_SL = 2,
  MOD_ML = 3,
  ALT_MINI = 4
};

enum {
    TO_MINI = SAFE_RANGE,
    TO_60
};

int cur_dance (qk_tap_dance_state_t *state);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);
void mini_alt_finished (qk_tap_dance_state_t *state, void *user_data);
void mini_alt_reset (qk_tap_dance_state_t *state, void *user_data);
void base_finished (qk_tap_dance_state_t *state, void *user_data);
void base_reset (qk_tap_dance_state_t *state, void *user_data);
void sl_finished (qk_tap_dance_state_t *state, void *user_data);
void sl_reset (qk_tap_dance_state_t *state, void *user_data);
void ml_finished (qk_tap_dance_state_t *state, void *user_data);
void ml_reset (qk_tap_dance_state_t *state, void *user_data);


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
#define LAYOUT_60_ansi_iso_split( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k1e, k2d, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,      \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b,      k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,  k0b,  k0c,   k0d, k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,   k1d,   k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,   k2d,   KC_NO }, \
    { k30,  KC_NO,   k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   KC_NO }, \
    { k40,  k41,   KC_NO, k43,  k44,   KC_NO, k46,  KC_NO, k48,   KC_NO, k4a,  k4b,  KC_NO, k4d,   k4e   }  \
}

#define LAYOUT_minivan( k2d, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,      \
    k40, k41,      k43, k44,            k48,      k4a, k4b,      k4d \
) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO,KC_NO,KC_NO }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,KC_NO,   KC_NO   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,k2d,   KC_NO }, \
    { k30,  KC_NO,   k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   KC_NO }, \
    { k40,  k41,   KC_NO, k43,  k44,   KC_NO, KC_NO, KC_NO, k48,   KC_NO, k4a,  k4b,  KC_NO, k4d,   KC_NO   } \
}

// Layers for full 60 layout

#define QWERTY 0     // Base Layer
#define SL 1         // Secondary Layer
#define ML 2         // Mouse Layer
#define ML2 3        // Mouse Layer
#define FN 4         // Function Layer

// Layers for minivan

#define BASE 5
#define NUMBERS 6
#define ARROWS 7
#define FNMINI 8

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
   [QWERTY] = LAYOUT_60_ansi_iso_split(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        KC_GESC,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_GRV,    KC_DEL,
        KC_TAB ,   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,
        KC_BSPC,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_BSLS,   TO_MINI,
        KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,
        KC_LCTL,   KC_LGUI,   TD(ALT_OSL1), KC_SPC, TD(MOD_BASE), KC_ENT, MO(FN),    KC_RALT,   KC_MENU,   KC_RCTL),

  /* Keymap Secondary: Secondary Layer
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
   [SL] = LAYOUT_60_ansi_iso_split(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   KC_HOME,   KC_UP,     KC_END,    KC_PGUP,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,    KC_LEFT,  KC_DOWN,   KC_RIGHT,  KC_PGDN,   _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   TD(MOD_SL),   _______,   _______,   _______,   _______,   _______),

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
   [ML] = LAYOUT_60_ansi_iso_split(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   KC_BTN1,   KC_MS_U,   KC_BTN2,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   KC_MS_L,   KC_MS_D,   KC_MS_R,   _______,   _______,   KC_MS_L,   KC_MS_D,   KC_MS_U,   KC_MS_R,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   KC_BTN1,   TD(MOD_ML),   KC_BTN2,   _______,   _______,   _______,   _______),

  /* Keymap FN: Mouse Scrolling Layer
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
   [ML2] = LAYOUT_60_ansi_iso_split(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   KC_WH_U,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        KC_DELT,   KC_WH_L,   KC_WH_D,   KC_WH_R,   _______,   _______,   KC_WH_L,   KC_WH_D,   KC_WH_U,   KC_WH_R,   _______,   _______,   _______,   KC_NO,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   KC_NO,     _______,   _______,   _______),


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
   [FN] = LAYOUT_60_ansi_iso_split(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        _______,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    _______,   _______,
        _______,   KC_MUTE,   KC_VOLD,   KC_VOLU,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   RGB_VAD,   RGB_VAI,
        _______,   KC_MPRV,   KC_MPLY,   KC_MNXT,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_NO,
        _______,   KC_BRID,   KC_BRIU,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   KC_NO,     _______,   _______,   _______,   _______,   _______),


   [BASE] = LAYOUT_minivan(   TO_60,
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        KC_TAB ,   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,
        KC_BSPC,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,
        KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,
        KC_LCTL,   KC_LGUI,   TD(ALT_MINI), LT(NUMBERS, KC_SPC),     LT(ARROWS, KC_ENT),    MO(FNMINI),  TO(NUMBERS),   TO(ARROWS)),

   [NUMBERS] = LAYOUT_minivan(_______,
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        KC_MINS,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_EQL,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,              KC_ENT,    _______,   TO(BASE),   _______),

   [ARROWS] = LAYOUT_minivan(_______,
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        KC_ESC,    KC_HOME,   KC_UP,     KC_END,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_RBRC,
        KC_DELT,   KC_LEFT,   KC_DOWN,   KC_RIGHT,  _______,   _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______,   KC_GRAVE,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_BSLS,   _______,
        _______,   _______,   _______,   KC_SPC,               _______,   _______,   _______,   TO(BASE)),

   [FNMINI] = LAYOUT_minivan(KC_NO,
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
  [ALT_OSL1]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset),
  [MOD_BASE]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,base_finished, base_reset),
  [MOD_SL]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL,sl_finished, sl_reset),
  [MOD_ML]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ml_finished, ml_reset),
  [ALT_MINI]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,mini_alt_finished, mini_alt_reset)
};


//   ___                 ___
//  | _ ) __ _ ___ ___  |   \ __ _ _ _  __ ___
//  | _ \/ _` (_-</ -_) | |) / _` | ' \/ _/ -_)
//  |___/\__,_/__/\___| |___/\__,_|_||_\__\___|

void base_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: layer_on(SL); break;
    case SINGLE_HOLD: layer_on(ML2); break;
    case DOUBLE_TAP: layer_on(ML); break;
    case DOUBLE_HOLD: break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void base_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_off(ML2); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
  }
  alttap_state.state = 0;
}

//   ___                     _                 ___
//  / __| ___ __ ___ _ _  __| |__ _ _ _ _  _  |   \ __ _ _ _  __ ___
//  \__ \/ -_) _/ _ \ ' \/ _` / _` | '_| || | | |) / _` | ' \/ _/ -_)
//  |___/\___\__\___/_||_\__,_\__,_|_|  \_, | |___/\__,_|_||_\__\___|
//                                      |__/

void sl_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: layer_off(SL); break;
    case SINGLE_HOLD: layer_on(ML2); break;
    case DOUBLE_TAP: layer_off(SL); layer_on(ML); break;
    case DOUBLE_HOLD: break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void sl_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_off(ML2); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
  }
  alttap_state.state = 0;
}

//   __  __                    ___
//  |  \/  |___ _  _ ___ ___  |   \ __ _ _ _  __ ___
//  | |\/| / _ \ || (_-</ -_) | |) / _` | ' \/ _/ -_)
//  |_|  |_\___/\_,_/__/\___| |___/\__,_|_||_\__\___|

void ml_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: layer_off(ML); layer_on(SL); break;
    case SINGLE_HOLD: layer_on(ML2); break;
    case DOUBLE_TAP: layer_off(ML); break;
    case DOUBLE_HOLD: break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void ml_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_off(ML2); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
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

void mini_alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(FNMINI, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: set_oneshot_layer(FNMINI, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(FN); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void mini_alt_reset (qk_tap_dance_state_t *state, void *user_data) {
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

// For custom functions

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TO_MINI:
      if (!record->event.pressed) {
          set_single_persistent_default_layer(BASE);
      }
      return false; // Skip all further processing of this key
    case TO_60:
      if (!record->event.pressed) {
          set_single_persistent_default_layer(QWERTY);
      }
      return false; // Let QMK send the enter press/release events
    default:
      return true; // Process all other keycodes normally
  }
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
      case QWERTY:
      case BASE:
          //rgblight_sethsv_noeeprom_azure();
          rgblight_sethsv_noeeprom (132, 102, rgblight_get_val());
        break;
      case SL:
      case ARROWS:
          //rgblight_sethsv_noeeprom_coral();
          rgblight_sethsv_noeeprom (11, 176, rgblight_get_val());
        break;
      case ML:
      case NUMBERS:
          //rgblight_sethsv_noeeprom_magenta();
          rgblight_sethsv_noeeprom (213, 255, rgblight_get_val());
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE
}
