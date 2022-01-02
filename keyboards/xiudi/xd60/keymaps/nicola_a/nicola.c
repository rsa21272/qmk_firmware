#include QMK_KEYBOARD_H
#include "nicola.h"

#ifdef JTU_ENABLE
#include "jtu.h"
#define send_string(x) send_jtu_string(x)
#define tap_code(x) tap_jtu(x)
#define tap_code16(x) tap_jtu16(x)
#endif

#define TIMEOUT_THRESHOLD (150)
#define OVERLAP_THRESHOLD (20)

bool is_nicola = false;

static uint16_t one_past_keycode = 0;
static uint16_t two_past_keycode = 0;
static uint16_t one_past_keytime = 0;
static uint16_t two_past_keytime = 0;

static const char *nicola_keymaps[] = {
  "u",                     //  0. KC_A
  "he",                    //  1. KC_B
  "su",                    //  2. KC_C
  "te",                    //  3. KC_D
  "ta",                    //  4. KC_E
  "ke",                    //  5. KC_F
  "se",                    //  6. KC_G
  "ha",                    //  7. KC_H
  "ku",                    //  8. KC_I
  "to",                    //  9. KC_J
  "ki",                    // 10. KC_K
  "i",                     // 11. KC_L
  "so",                    // 12. KC_M
  "me",                    // 13. KC_N
  "tu",                    // 14. KC_O
  "E" SS_TAP(X_COMM),      // 15. KC_P
  ".",                     // 16. KC_Q
  "ko",                    // 17. KC_R
  "si",                    // 18. KC_S
  "sa",                    // 19. KC_T
  "ti",                    // 20. KC_U
  "hu",                    // 21. KC_V
  "ka",                    // 22. KC_W
  "hi",                    // 23. KC_X
  "ra",                    // 24. KC_Y
  "E" SS_TAP(X_DOT),       // 25. KC_Z
  SS_TAP(X_COMM),          // 26. KC_LBRC
  "nn",                    // 27. KC_SCLN
  "ne",                    // 28. KC_COMM
  "ho",                    // 29. KC_DOT
  SS_LSFT(SS_TAP(X_SLSH)), // 30. SHIFT + KC_1
  "E" SS_TAP(X_SLSH),      // 31. SHIFT + KC_2
  SS_LSFT(SS_TAP(X_GRV)),  // 32. SHIFT + KC_3
  SS_TAP(X_LBRC),          // 33. SHIFT + kC_4
  SS_TAP(X_RBRC),          // 34. SHIFT + KC_5
  "E" SS_TAP(X_LBRC),      // 35. SHIFT + KC_6
  "E" SS_TAP(X_RBRC),      // 36. SHIFT + KC_7
  SS_LSFT(SS_TAP(X_8)),    // 37. SHIFT + KC_8
  SS_LSFT(SS_TAP(X_9)),    // 38. SHIFT + KC_9
  SS_LSFT(SS_TAP(X_0)),    // 39. SHIFT + KC_0
  "wo",                    // 40. NG_LSFT + KC_A
  "xi",                    // 41. NG_LSFT + KC_B
  "ro",                    // 42. NG_LSFT + KC_C
  "na",                    // 43. NG_LSFT + KC_D
  "ri",                    // 44. NG_LSFT + KC_E
  "xyu",                   // 45. NG_LSFT + KC_F
  "mo",                    // 46. NG_LSFT + KC_G
  "ba",                    // 47. NG_LSFT + KC_H
  "gu",                    // 48. NG_LSFT + KC_I
  "do",                    // 49. NG_LSFT + KC_J
  "gi",                    // 50. NG_LSFT + KC_K
  "po",                    // 51. NG_LSFT + KC_L
  "zo",                    // 52. NG_LSFT + KC_M
  "pu",                    // 53. NG_LSFT + KC_N
  "du",                    // 54. NG_LSFT + KC_O
  "pi",                    // 55. NG_LSFT + KC_P
  "xa",                    // 56. NG_LSFT + KC_Q
  "xya",                   // 57. NG_LSFT + KC_R
  "a",                     // 58. NG_LSFT + KC_S
  "re",                    // 59. NG_LSFT + KC_T
  "di",                    // 60. NG_LSFT + KC_U
  "ya",                    // 61. NG_LSFT + KC_V
  "e",                     // 62. NG_LSFT + KC_W
  SS_TAP(X_MINS),          // 63. NG_LSFT + KC_X
  "pa",                    // 64. NG_LSFT + KC_Y
  "xu",                    // 65. NG_LSFT + KC_Z
  "",                      // 66. NG_LSFT + KC_SCLN
  "pe",                    // 67. NG_LSFT + KC_COMM
  "bo",                    // 68. NG_LSFT + KC_DOT
  "",                      // 69. NG_LSFT + KC_SLSH
  "vu",                    // 70. NG_RSFT + KC_A
  "be",                    // 71. NG_RSFT + KC_B
  "zu",                    // 72. NG_RSFT + KC_C
  "de",                    // 73. NG_RSFT + KC_D
  "da",                    // 74. NG_RSFT + KC_E
  "ge",                    // 75. NG_RSFT + KC_F
  "ze",                    // 76. NG_RSFT + KC_G
  "mi",                    // 77. NG_RSFT + KC_H
  "ru",                    // 78. NG_RSFT + KC_I
  "o",                     // 79. NG_RSFT + KC_J
  "no",                    // 80. NG_RSFT + KC_K
  "xyo",                   // 81. NG_RSFT + KC_L
  "yu",                    // 82. NG_RSFT + KC_M
  "nu",                    // 83. NG_RSFT + KC_N
  "ma",                    // 84. NG_RSFT + KC_O
  "xe",                    // 85. NG_RSFT + KC_P
  "",                      // 86. NG_RSFT + KC_Q
  "go",                    // 87. NG_RSFT + KC_R
  "zi",                    // 88. NG_RSFT + KC_S
  "za",                    // 89. NG_RSFT + KC_T
  "ni",                    // 90. NG_RSFT + KC_U
  "bu",                    // 91. NG_RSFT + KC_V
  "ga",                    // 92. NG_RSFT + KC_W
  "bi",                    // 93. NG_RSFT + KC_X
  "yo",                    // 94. NG_RSFT + KC_Y
  "",                      // 95. NG_RSFT + KC_Z
  "xtu",                   // 96. NG_RSFT + KC_SCLN
  "mu",                    // 97. NG_RSFT + KC_COMM
  "wa",                    // 98. NG_RSFT + KC_DOT
  "xo",                    // 99. NG_RSFT + KC_SLSH
};

static int find_nicola(uint16_t thumb, uint16_t keycode) {
  switch (thumb) {
    default:
      switch (keycode) {
        case KC_A ... KC_Z: return keycode - KC_A;
        case KC_LBRC: return 26;
        case KC_SCLN: return 27;
        case KC_COMM: return 28;
        case KC_DOT: return 29;
      }
      break;
    case NG_LSFT:
      switch (keycode) {
        case KC_A ... KC_Z: return keycode - KC_A + 40;
        case KC_1 ... KC_0: return keycode - KC_1 + 30;
        case KC_SCLN: return 66;
        case KC_COMM: return 67;
        case KC_DOT: return 68;
        case KC_SLSH: return 69;
      }
      break;
    case NG_RSFT:
      switch (keycode) {
        case KC_A ... KC_Z: return keycode - KC_A + 70;
        case KC_1 ... KC_0: return keycode - KC_1 + 30;
        case KC_SCLN: return 96;
        case KC_COMM: return 97;
        case KC_DOT: return 98;
        case KC_SLSH: return 99;
      }
      break;
  }
  return -1;
}

static void send_nicola_key(uint16_t thumb, uint16_t keycode) {
  switch (keycode) {
    case NG_LSFT: send_left_spacebar(); return;
    case NG_RSFT: send_right_spacebar(); return;
  }
  int i = find_nicola(thumb, keycode);
  if (i < 0) {
    tap_code(keycode);
  } else {
    const char *str = nicola_keymaps[i];
    if (*str != 'E') {
      send_string(str);
    } else {
      send_zen_eisu();
      send_string(str + 1);
      send_zen_kana();
    }
  }
}

static bool is_thumb_key(uint16_t keycode) {
  return keycode == NG_LSFT || keycode == NG_RSFT;
}

static void nicola_clear(void) {
  one_past_keycode = two_past_keycode = 0;
  one_past_keytime = two_past_keytime = 0;
}

static void wipe_nicola_keys(void) {
  if (two_past_keycode) {
    if (is_thumb_key(two_past_keycode))
      send_nicola_key(two_past_keycode, one_past_keycode);
    else
      send_nicola_key(one_past_keycode, two_past_keycode);
  } else if (one_past_keycode) {
    send_nicola_key(KC_NO, one_past_keycode);
  }
  nicola_clear();
}

void nicola_on(void) {
  nicola_clear();
  is_nicola = true;
#ifdef BACKLIGHT_ENABLE
  backlight_enable();
#endif
}

void nicola_off(void) {
  wipe_nicola_keys();
  is_nicola = false;
#ifdef BACKLIGHT_ENABLE
  backlight_disable();
#endif
}

void matrix_scan_nicola(void) {
  uint16_t now = timer_read();
  if ((one_past_keycode && !is_thumb_key(one_past_keycode) && now - one_past_keytime > TIMEOUT_THRESHOLD) ||
      (two_past_keycode && !is_thumb_key(two_past_keycode) && now - two_past_keytime > TIMEOUT_THRESHOLD)) {
    wipe_nicola_keys();
  }
};

static bool is_nicola_key(uint16_t keycode) {
  switch (keycode) {
    case KC_A ... KC_Z:
    case KC_1 ... KC_0:
    case KC_LBRC:
    case KC_SCLN:
    case KC_COMM:
    case KC_DOT:
    case KC_SLSH:
    case KC_QUOT:
    case NG_LSFT:
    case NG_RSFT:
    return true;
  }
  return false;
}

bool process_nicola(uint16_t keycode, keyrecord_t *record) {
  static bool previous_mode = false;
  static uint8_t mods = 0;
  if (IS_MOD(keycode)) {
    if (record->event.pressed) {
      mods |= MOD_BIT(keycode);
    } else {
      mods &= ~MOD_BIT(keycode);
    }
  }
  bool nicola_enabled = is_nicola && mods == 0 && is_nicola_key(keycode);
  if (previous_mode != nicola_enabled) {
    previous_mode = nicola_enabled;
    wipe_nicola_keys();
    layer_clear();
    clear_keyboard_but_mods();
  }
  if (!nicola_enabled) {
    return true;
  }
  if (keycode == KC_QUOT) {
    if (record->event.pressed) {
      register_code(KC_BSPC);
    } else {
      unregister_code(KC_BSPC);
    }
    return false;
  }
  if (record->event.pressed) {
    if (one_past_keycode && is_thumb_key(keycode) == is_thumb_key(one_past_keycode)) {
      wipe_nicola_keys();
    } else if (two_past_keycode) {
      uint16_t t1 = one_past_keytime - two_past_keytime;
      uint16_t t2 = record->event.time - one_past_keytime;
      if (t1 < t2) {
        wipe_nicola_keys();
      } else {
        send_nicola_key(KC_NO, two_past_keycode);
      }
    }
    two_past_keycode = one_past_keycode;
    two_past_keytime = one_past_keytime;
    one_past_keycode = keycode;
    one_past_keytime = record->event.time;
  } else {
    if (keycode == two_past_keycode) {
      uint16_t t1 = one_past_keytime - two_past_keytime;
      uint16_t t2 = record->event.time - one_past_keytime;
      if (t1 >= t2 && t2 < OVERLAP_THRESHOLD) {
        send_nicola_key(KC_NO, two_past_keycode);
        two_past_keycode = 0;
        two_past_keytime = 0;
      }
    }
    if (keycode == one_past_keycode || keycode == two_past_keycode) {
      wipe_nicola_keys();
    }
  }
  return false;
}