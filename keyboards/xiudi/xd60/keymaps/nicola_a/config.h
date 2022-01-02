#pragma once
#include "config_common.h"

#define LAYOUT_60_ansi_split_space( \
      K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,  \
      K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,  \
      K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,          K2D,  \
      K30,          K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,          K3D,  \
      K40,   K41,   K42,                 K46,   K45,                        K4A,   K4B,   K4C,   K4D   \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D },  \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D },  \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   KC_NO, K2D },  \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   KC_NO, K3D },  \
    { K40,   K41,   K42,   KC_NO, KC_NO, K45,   K46,   KC_NO, KC_NO, KC_NO, K4A,   K4B,   K4C,   K4D }   \
}

#define LAYOUT_60_ansi_split_space_rshift( \
      K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,         \
      K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,         \
      K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,          K2D,         \
      K30,          K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,          K3D,   K3C,  \
      K40,   K41,   K42,                 K46,   K45,                        K4A,   K4B,   K4C,   K4D          \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D },  \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D },  \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   KC_NO, K2D },  \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D },  \
    { K40,   K41,   K42,   KC_NO, KC_NO, K45,   K46,   KC_NO, KC_NO, KC_NO, K4A,   K4B,   K4C,   K4D }   \
}

#define LAYOUT_60_ansi_split_space_bs( \
      K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,  K49,  \
      K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,        \
      K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,          K2D,        \
      K30,          K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,          K3D,        \
      K40,   K41,   K42,                 K46,   K45,                        K4A,   K4B,   K4C,   K4D         \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D },  \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D },  \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   KC_NO, K2D },  \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   KC_NO, K3D },  \
    { K40,   K41,   K42,   KC_NO, KC_NO, K45,   K46,   KC_NO, KC_NO, K49,   K4A,   K4B,   K4C,   K4D }   \
}

#define LAYOUT_60_ansi_split_space_bs_rshift( \
      K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,  K49,  \
      K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,        \
      K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,          K2D,        \
      K30,          K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,          K3D,  K3C,  \
      K40,   K41,   K42,                 K46,   K45,                        K4A,   K4B,   K4C,   K4D         \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D },  \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D },  \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   KC_NO, K2D },  \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D },  \
    { K40,   K41,   K42,   KC_NO, KC_NO, K45,   K46,   KC_NO, KC_NO, K49,   K4A,   K4B,   K4C,   K4D }   \
}

#define PERMISSIVE_HOLD 1
#define JTU_ENABLE
#define NICOLA_ENABLE
