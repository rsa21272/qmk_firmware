#include QMK_KEYBOARD_H

#ifdef JTU_ENABLE
#include "jtu.h"
#endif

#ifdef NICOLA_ENABLE
#include "nicola.h"
#endif

#ifndef JTU_ENABLE
#define NC_JIS KC_NO
#define KC_ANSI KC_NO
#endif

#ifndef NICOLA_ENABLE
#define NG_LSFT NC_MHEN
#define NG_RSFT NC_HENK
#endif

// keymap layers
#define _BL 0
#define _F1 1
#define _F2 2

// custom keycodes
enum custom_keycodes {
  NC_RGUI = SAFE_RANGE,
  NC_LGUI,
  NC_JIS,
  NC_ANSI,
  NC_APP = LT(_F1, KC_APP) // _F1 layer when held, KC_APP when tappd
};

// keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_60_ansi_split_space_bs_rshift(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(_F1),
    MO(_F2), KC_LALT, NC_LGUI,                   NG_LSFT, NG_RSFT,                            NC_RGUI, KC_RALT, NC_APP,  KC_RCTL),
  [_F1] = LAYOUT_60_ansi_split_space_bs_rshift(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
    KC_CAPS, NC_ANSI, NC_JIS,  _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   _______, _______,
    _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, _______, _______, _______, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_DOWN,          _______, _______,
    _______, _______, KC_LGUI,                   _______, _______,                            KC_RGUI, _______, _______, _______),
  [_F2] = LAYOUT_60_ansi_split_space_bs_rshift(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
    KC_CAPS, NC_ANSI, NC_JIS,  _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_PSCR, _______, KC_PAUS, _______,
    _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS,  KC_DEL,           _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, KC_LGUI,                   _______, _______,                            KC_RGUI, _______, _______, _______),
};

void send_eisu(void) {
  tap_code16(KC_F17);
  tap_code16(KC_LANG2);
#ifdef NICOLA_ENABLE
  nicola_off();
#endif
}

void send_shift_eisu(void) {
  tap_code16(S(KC_F17));
  tap_code16(S(KC_LANG2));
#ifdef NICOLA_ENABLE
  nicola_off();
#endif
}

void send_kana(void) {
  tap_code16(KC_F19);
  tap_code16(KC_LANG1);
#ifdef NICOLA_ENABLE
  nicola_on();
#endif
}

void send_shift_kana(void) {
  tap_code16(S(KC_F19));
  tap_code16(S(KC_LANG1));
#ifdef NICOLA_ENABLE
  nicola_on();
#endif
}

void send_left_spacebar(void) {
  tap_code16(KC_SPC);
}

void send_right_spacebar(void) {
  tap_code16(KC_SPC);
}

void send_zen_eisu(void) {
  tap_code16(KC_F17);
  tap_code16(KC_LANG2);
}

void send_zen_kana(void) {
  tap_code16(KC_F19);
  tap_code16(KC_LANG1);
}

void keyboard_post_init_user(void) {
#ifdef JTU_ENABLE
  is_jtu = true;
#endif
#ifdef NICOLA_ENABLE
  is_nicola = false;
#endif
#ifdef BACKLIGHT_ENABLE
  backlight_level(30);
  backlight_disable();
#endif
#ifdef CONSOLE_ENABLE
  debug_enable = true;
#endif
}

void matrix_scan_user(void) {
#ifdef NICOLA_ENABLE
  matrix_scan_nicola();
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t gui = KC_NO;
  switch (gui) {
    default:
      if (keycode == NC_RGUI || keycode == NC_LGUI) {
        if (record->event.pressed)
          gui = keycode;
        return false;
      }
      break;
    case NC_RGUI:
      switch (keycode) {
        case NC_RGUI:
          if (!record->event.pressed) {
            send_kana();
            gui = 0;
          }
          return false;
        case NC_LGUI:
          if (record->event.pressed) {
            send_shift_eisu();
            gui = 0;
          }
          return false;
        default:
          if (!IS_MOD(keycode) && record->event.pressed) {
            register_code(KC_RGUI);
            gui = KC_RGUI;
          }
      }
      break;
    case NC_LGUI:
      switch (keycode) {
        case NC_LGUI:
          if (!record->event.pressed) {
            send_eisu();
            gui = 0;
          }
          return false;
        case NC_RGUI:
          if (record->event.pressed) {
            send_shift_kana();
            gui = 0;
          }
          return false;
        default:
          if (!IS_MOD(keycode) && record->event.pressed) {
            register_code(KC_LGUI);
            gui = KC_LGUI;
          }
      }
      break;
    case KC_RGUI:
      if (keycode == NC_RGUI || keycode == NC_LGUI) {
        if (keycode == NC_RGUI && !record->event.pressed) {
          unregister_code(KC_RGUI);
          gui = 0;
        }
        return false;
      }
      break;
    case KC_LGUI:
      if (keycode == NC_RGUI || keycode == NC_LGUI) {
        if (keycode == NC_LGUI && !record->event.pressed) {
          unregister_code(KC_LGUI);
          gui = 0;
        }
        return false;
      }
      break;
  }
#ifdef JTU_ENABLE
  switch (keycode) {
    case NC_ANSI: is_jtu = false; return false;
    case NC_JIS: is_jtu = true; return false;
  }
#endif
#ifdef NICOLA_ENABLE
  if (!process_nicola(keycode, record)) {
    return false;
  }
  switch (keycode) {
    case NG_LSFT:
    case NG_RSFT:
      if (record->event.pressed) {
        register_code(KC_SPC);
      } else {
        unregister_code(KC_SPC);
      }
      return false;
  }
#endif
#ifdef JTU_ENABLE
  if (!process_jtu(keycode, record)) {
    return false;
  }
#endif
  return true;
}