#pragma once

enum nicola_keycodes {
  NG_LSFT = SAFE_RANGE, // left thumb key
  NG_RSFT               // right thumb key
};
#undef SAFE_RANGE
#define SAFE_RANGE (NG_RSFT + 1)

extern bool is_nicola;

void nicola_on(void);
void nicola_off(void);
void send_eisu(void);
void send_shift_eisu(void);
void send_kana(void);
void send_shift_kana(void);
void send_left_spacebar(void);
void send_right_spacebar(void);
void send_zen_eisu(void);
void send_zen_kana(void);
void matrix_scan_nicola(void);
bool process_nicola(uint16_t keycode, keyrecord_t *record);