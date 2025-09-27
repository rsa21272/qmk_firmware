#pragma once

extern bool is_jtu;

bool register_jtu(uint16_t keycode);
bool unregister_jtu(uint16_t keycode);
void tap_jtu(uint16_t keycode);
void tap_jtu16(uint16_t keycode);
void send_jtu_string(const char *str);
bool process_jtu(uint16_t keycode, keyrecord_t *record);
