#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define MAC 0
#define WIN 1
#define NUM 2
#define ARR 3
#define WAR 4
#define FNS 5

// Tap struct
typedef struct {
  bool is_press_action;
  int state;
} tap;


// Tap Dance enum
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

enum custom_keycodes {
  TO_MAC = SAFE_RANGE,
  TO_WIN
};

//Tap dance enums
enum {
  ALT = 0,
  GUI = 1,
};

int cur_dance (qk_tap_dance_state_t *state);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);
void gui_finished (qk_tap_dance_state_t *state, void *user_data);
void gui_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [MAC] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,KC_O,RALT_T(KC_P), TO_WIN,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_BSPC),LCTL_T(KC_A),KC_S,  KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, RCTL_T(KC_SCLN), KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
KC_LSFT,  LSFT_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, RSFT_T(KC_SLSH), KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            TD(ALT), LGUI_T(KC_BSPC),LT(NUM,KC_SPC),  LT(ARR, KC_ENT),  RGUI_T(KC_TAB),  LT(FNS, KC_ESC) \
                                      //`--------------------------'  `--------------------------'

  ),

  [WIN] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,KC_O,RALT_T(KC_P), TO_MAC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_BSPC),LCTL_T(KC_A),KC_S,  KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, RCTL_T(KC_SCLN), KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
KC_LSFT,  LSFT_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, RSFT_T(KC_SLSH), KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            TD(GUI), LALT_T(KC_BSPC),LT(NUM,KC_SPC),  LT(WAR, KC_ENT),  RGUI_T(KC_TAB),  LT(FNS, KC_ESC) \
                                      //`--------------------------'  `--------------------------'

  ),

  [NUM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ZKHK,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,  RALT_T(KC_0), _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
_______,LCTL_T(KC_ZKHK),_______,_______,_______,   _______,                 KC_MINS,LSFT(KC_MINS),KC_EQL,LSFT(KC_EQL),RCTL_T(KC_QUOT),   _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,     KC_ENT, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [ARR] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ZKHK, KC_HOME,   KC_UP,  KC_END, KC_PGUP, _______,                      _______, _______, _______, KC_LBRC,RALT_T(KC_RBRC),KC_RBRC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_DELT),LCTL_T(KC_LEFT),KC_DOWN,KC_RIGHT,KC_PGDN,_______,                KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT,RCTL_T(KC_BSLS),KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, LGUI_T(KC_DEL),  KC_SPC,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [WAR] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ZKHK, KC_HOME,   KC_UP,  KC_END, KC_PGUP, _______,                      _______, _______, _______, KC_LBRC,RALT_T(KC_RBRC),KC_RBRC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_DELT),LCTL_T(KC_LEFT),KC_DOWN,KC_RIGHT,KC_PGDN,_______,                KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT,RCTL_T(KC_BSLS),KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, LALT_T(KC_DEL),  KC_SPC,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [FNS] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_MUTE, KC_VOLD, KC_VOLU,  KC_F11, _______,                      _______,  KC_F12, _______, XXXXXXX, XXXXXXX, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_CLCK, _______,                      _______, _______, _______, KC_BRID, KC_BRIU, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  )
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
  [GUI]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL,gui_finished, gui_reset),
};

//     _   _  _____    ___  ___ _      ___ _   _ _  _  ___ _____ ___ ___  _  _   _    ___   ___ ___ ___
//    /_\ | ||_   _|  / _ \/ __| |    | __| | | | \| |/ __|_   _|_ _/ _ \| \| | | |  / _ \ / __|_ _/ __|
//   / _ \| |__| |   | (_) \__ \ |__  | _|| |_| | .` | (__  | |  | | (_) | .` | | |_| (_) | (_ || | (__
//  /_/ \_\____|_|    \___/|___/____| |_|  \___/|_|\_|\___| |_| |___\___/|_|\_| |____\___/ \___|___\___|


void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(FNS, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: register_code(KC_LALT); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(FNS); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: unregister_code(KC_LALT); break;
    case DOUBLE_HOLD: layer_off(FNS); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;
}

void gui_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(FNS, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LGUI); break;
    case DOUBLE_TAP: register_code(KC_LGUI); break;
    case DOUBLE_HOLD: register_code(KC_LGUI); layer_on(FNS); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void gui_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LGUI); break;
    case DOUBLE_TAP: unregister_code(KC_LGUI); break;
    case DOUBLE_HOLD: layer_off(FNS); unregister_code(KC_LGUI); break;
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

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
// void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
//   if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
//     layer_on(layer3);
//   } else {
//     layer_off(layer3);
//   }
// }

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if (record->event.pressed) {
// #ifdef SSD1306OLED
//     set_keylog(keycode, record);
// #endif
    // set_timelog();
  // }

                          thatthat that what what what what that the probably probablywhenwhat whatwhatwhatwhatwhatwhatthe then  teh then how  the ducks
  // switch (keycode) {
  //   case QWERTY:
  //     if (record->event.pressed) {
  //       persistent_default_layer_set(1UL<<_QWERTY);
  //     }
  //     return false;
  //   case LOWER:
  //     if (record->event.pressed) {
  //       layer_on(_LOWER);
  //       update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
  //     } else {
  //       layer_off(_LOWER);
  //       update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
  //     }
  //     return false;
  //   case RAISE:
  //     if (record->event.pressed) {
  //       layer_on(_RAISE);
  //       update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
  //     } else {
  //       layer_off(_RAISE);
  //       update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
  //     }
  //     return false;
  //   case ADJUST:
  //       if (record->event.pressed) {
  //         layer_on(_ADJUST);
  //       } else {
  //         layer_off(_ADJUST);
  //       }
  //       return false;
  //   case RGB_MOD:
  //     #ifdef RGBLIGHT_ENABLE
  //       if (record->event.pressed) {
  //         rgblight_mode(RGB_current_mode);
  //         rgblight_step();
  //         RGB_current_mode = rgblight_config.mode;
  //       }
  //     #endif
  //     return false;
  //   case RGBRST:
  //     #ifdef RGBLIGHT_ENABLE
  //       if (record->event.pressed) {
  //         eeconfig_update_rgblight_default();
  //         rgblight_enable();
  //         RGB_current_mode = rgblight_config.mode;
  //       }
  //     #endif
  //     break;
//   }
//   return true;
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
  }

  switch(keycode) {
    case TO_MAC:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(MAC);
      }
      return false;
    case TO_WIN:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(WIN);
      }
      return false;
    default:
      return true;
  }
}