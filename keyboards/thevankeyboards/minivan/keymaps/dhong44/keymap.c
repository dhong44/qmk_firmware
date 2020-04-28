#include <stdbool.h>
#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define BASE 0
#define NUMBERS 1
#define ARROWS 2
#define FN 3
#define SPECIAL 4

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
  GUI = 0,
};

int cur_dance (qk_tap_dance_state_t *state);
void gui_finished (qk_tap_dance_state_t *state, void *user_data);
void gui_reset (qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        XXXXXXX,   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      XXXXXXX,
XXXXXXX,   LCTL_T(KC_A),      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      RGUI_T(KC_SCLN),   XXXXXXX,
XXXXXXX,   LSFT_T(KC_Z),      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    RSFT_T(KC_SLSH),   XXXXXXX,
        XXXXXXX,   TD(GUI),   LALT_T(KC_BSPC), LT(NUMBERS, KC_SPC),     LT(ARROWS, KC_ENT),  RCTL_T(KC_ESC), LT(FN, KC_TAB),      XXXXXXX),


    [NUMBERS] = LAYOUT(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        XXXXXXX,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      XXXXXXX,
XXXXXXX,   LCTL_T(KC_ZKHK),   _______,   _______,   _______,   _______,   KC_MINS,LSFT(KC_MINS),KC_EQL,    KC_PPLS,   RGUI_T(KC_QUOT),   XXXXXXX,
        XXXXXXX,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   XXXXXXX,
        XXXXXXX,   _______,   _______,   _______,              KC_ENT,    _______,   _______,   _______),

    [ARROWS] = LAYOUT(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        XXXXXXX,   KC_HOME,   KC_UP,     KC_END,    KC_PGUP,   _______,   _______,   _______,   _______,   KC_LBRC,   KC_RBRC,   XXXXXXX,
XXXXXXX,   LCTL_T(KC_LEFT),   KC_DOWN,   KC_RIGHT,  KC_PGDN,   _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  RGUI_T(KC_BSLS),   XXXXXXX,
        XXXXXXX,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,     XXXXXXX,
        XXXXXXX,   _______,   _______,   KC_SPC,               _______,   _______,   _______,   _______),

    [FN] = LAYOUT(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        XXXXXXX,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,   XXXXXXX,
        XXXXXXX,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_F11,    _______,   _______,   KC_F12,    _______,   RGB_VAD,   RGB_VAI,   XXXXXXX,
        XXXXXXX,   KC_MPRV,   KC_MPLY,   KC_MNXT,   KC_CLCK,   _______,   _______,   _______,   _______,   KC_BRID,   KC_BRIU,   XXXXXXX,
        XXXXXXX,   _______,   _______,   _______,              _______,   _______,   _______,   _______),

    [SPECIAL] = LAYOUT(
    //  1          2          3          4          5          6          7          8          9          10         11         12         13         14         15
        XXXXXXX,   KC_TAB,    KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    XXXXXXX,
        XXXXXXX,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_F11,    _______,   _______,   KC_F12,    _______,   RGB_VAD,   RGB_VAI,   XXXXXXX,
XXXXXXX,   LSFT_T(KC_MPRV),   KC_MPLY,   KC_MNXT,   KC_CLCK,   _______,   _______,   _______,   _______,   KC_BRID,   KC_BRIU,   XXXXXXX,
        XXXXXXX,   _______,   _______,   _______,              _______,   _______,   _______,   _______)
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
  [GUI]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL,gui_finished, gui_reset),
};

//     _   _  _____    ___  ___ _      ___ _   _ _  _  ___ _____ ___ ___  _  _   _    ___   ___ ___ ___
//    /_\ | ||_   _|  / _ \/ __| |    | __| | | | \| |/ __|_   _|_ _/ _ \| \| | | |  / _ \ / __|_ _/ __|
//   / _ \| |__| |   | (_) \__ \ |__  | _|| |_| | .` | (__  | |  | | (_) | .` | | |_| (_) | (_ || | (__
//  /_/ \_\____|_|    \___/|___/____| |_|  \___/|_|\_|\___| |_| |___\___/|_|\_| |____\___/ \___|___\___|


void gui_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: register_code(KC_LGUI); break;
    case SINGLE_HOLD: register_code(KC_LGUI); break;
    case DOUBLE_TAP: set_oneshot_layer(SPECIAL, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(SPECIAL); break;
    case TRIPLE_TAP: set_oneshot_layer(SPECIAL, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case TRIPLE_HOLD: register_code(KC_LCTL); layer_on(SPECIAL); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void gui_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: unregister_code(KC_LGUI); break;
    case SINGLE_HOLD: unregister_code(KC_LGUI); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD:  layer_off(SPECIAL); unregister_code(KC_LALT); break;
    case TRIPLE_TAP: break;
    case TRIPLE_HOLD: layer_off(SPECIAL); unregister_code(KC_LCTL); break;
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
