#include QMK_KEYBOARD_H
#include "jtu.h"

bool is_jtu = false;

static uint16_t jtu_keymaps[][3] = {
  {KC_2, KC_LBRC, KC_NO},          //  0. KC_2
  {KC_6, KC_EQL, KC_NO},           //  1. KC_6
  {KC_7, S(KC_6), KC_NO},          //  2. KC_7
  {KC_8, S(KC_QUOT), KC_NO},       //  3. KC_8
  {KC_9, S(KC_8), KC_NO},          //  4. KC_9
  {KC_0, S(KC_9), KC_NO},          //  5. KC_0
  {KC_MINS, S(KC_INT1), KC_NO},    //  6. KC_MINS
  {S(KC_MINS), S(KC_SCLN), KC_NO}, //  7. KC_EQL
  {KC_INT3, S(KC_INT3), KC_NO},    //  8. KC_BSLS
  {KC_SCLN, KC_QUOT, KC_NO},       //  9. KC_SCLN
  {S(KC_7), S(KC_2), KC_NO},       // 10. KC_QUOT
  {S(KC_LBRC), S(KC_EQL), KC_NO},  // 11. KC_GRV
  {KC_RBRC, S(KC_RBRC), KC_NO},    // 12. KC_LBRC
  {KC_NUHS, S(KC_NUHS), KC_NO},    // 13. KC_RBRC
};
static uint8_t mods = 0;

static int find_jtu(uint16_t keycode) {
  switch (keycode) {
    case KC_2: return 0;
    case KC_6: return 1;
    case KC_7: return 2;
    case KC_8: return 3;
    case KC_9: return 4;
    case KC_0: return 5;
    case KC_MINS: return 6;
    case KC_EQL: return 7;
    case KC_BSLS: return 8;
    case KC_SCLN: return 9;
    case KC_QUOT: return 10;
    case KC_GRV: return 11;
    case KC_LBRC: return 12;
    case KC_RBRC: return 13;
  }
  return -1;
}

bool register_jtu(uint16_t keycode) {
  if (keycode == KC_LSFT || keycode == KC_RSFT) {
    mods |= MOD_BIT(keycode);
  }
  if (!is_jtu)
    return true;
  int i = find_jtu(keycode);
  if (i >= 0) {
    jtu_keymaps[i][2] = mods ? jtu_keymaps[i][1] : jtu_keymaps[i][0];
    if (jtu_keymaps[i][2] & (QK_LSFT | QK_RSFT)) {
      add_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
    } else {
      del_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
    }
    send_keyboard_report();
    register_code(jtu_keymaps[i][2]);
    return false;
  }
  set_mods(mods | (get_mods() & ~(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))));
  send_keyboard_report();
  return true;
}

bool unregister_jtu(uint16_t keycode) {
  if (keycode == KC_LSFT || keycode == KC_RSFT) {
    mods &= ~MOD_BIT(keycode);
  }
  if (!is_jtu)
    return true;
  int i = find_jtu(keycode);
  if (i >= 0) {
    unregister_code(jtu_keymaps[i][2]);
  }
  set_mods(mods | (get_mods() & ~(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))));
  send_keyboard_report();
  return i < 0;
}

void tap_jtu(uint16_t keycode) {
  if (!is_jtu) {
    tap_code(keycode);
    return;
  }
  int i = find_jtu(keycode);
  if (i >= 0) {
    register_jtu(keycode);
    unregister_jtu(keycode);
  } else {
    tap_code(keycode);
  }
}

void tap_jtu16(uint16_t keycode) {
  if (!is_jtu) {
    tap_code16(keycode);
    return;
  }
  int i = find_jtu(keycode);
  if (i >= 0) {
    uint8_t mods = 0;
    if (keycode & QK_LCTL)
      mods |= MOD_BIT(KC_LCTL);
    if (keycode & QK_LSFT)
      mods |= MOD_BIT(KC_LSFT);
    if (keycode & QK_LALT)
      mods |= MOD_BIT(KC_LALT);
    if (keycode & QK_LGUI)
      mods |= MOD_BIT(KC_LGUI);
    register_mods(mods);
    tap_jtu(keycode);
    unregister_mods(mods);
  } else {
    tap_code16(keycode);
  }
}

void send_jtu_string(const char *str) {
  while (1) {
    char ascii_code = *str;
    if (!ascii_code)
      break;
    if (ascii_code == SS_QMK_PREFIX) {
      ascii_code = *(++str);
      if (ascii_code == SS_TAP_CODE) {
        uint8_t keycode = *(++str);
        tap_jtu(keycode);
      } else if (ascii_code == SS_DOWN_CODE) {
        uint8_t keycode = *(++str);
        if (register_jtu(keycode))
          register_code(keycode);
      } else if (ascii_code == SS_UP_CODE) {
        uint8_t keycode = *(++str);
        if (unregister_jtu(keycode))
          unregister_code(keycode);
      }
    } else {
      send_char(ascii_code);
    }
    ++str;
  }
}

bool process_jtu(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    return register_jtu(keycode);
  } else {
    return unregister_jtu(keycode);
  }
  return true;
}
