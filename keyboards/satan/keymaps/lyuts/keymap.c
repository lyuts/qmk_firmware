#include "satan.h"

#define TAPPING_TERM 200

// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum Layer {
    _BL = 0, // base layer
    _L1, // 
    _L2
};

enum TapDance {
    O_BRCK = 1,
};

enum DualRoleKeyId {
    ESC_TILD = 0,
    TAB_FN2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |TabFN|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |fn1    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space            |fn2 |fn1 |fn2 |Ctrl |
   * `-----------------------------------------------------------'


   * ,-----------------------------------------------------------------------.
   * |Esc~|   1|   2|   3|   4|   5|   6|   7|   8|   9|   0|   -|   =|Bcksp |
   * |-----------------------------------------------------------------------|
   * |Tab   |   Q|   W|   E|   R|   T|   Y|   U|   I|   O|   P|   [|   ]|  \ |
   * |-----------------------------------------------------------------------|
   * |fn1    |   A|   S|   D|   F|   G|   H|   J|   K|   L|   ;|   '| Return |
   * |-----------------------------------------------------------------------|
   * |Shift    |   Z|   X|   C|   V|   B|   N|   M|   ,|   .|   /|Shift      |
   * |-----------------------------------------------------------------------|
   * |Ctrl |Gui  |Alt  |           Space            |fn2  |fn1  |fn2  |Ctrl  |
   * `-----------------------------------------------------------------------'
   */
[_BL] = LAYOUT_60_ansi(
  F(ESC_TILD), KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
  F(TAB_FN2),  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,   KC_P,    TD(O_BRCK), KC_RBRC, KC_BSLS, \
  MO(_L1),     KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,  \
  KC_LSFT,     KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M,     KC_COMM, KC_DOT, KC_SLSH,                   KC_RSFT, \
  KC_LCTL,     KC_LGUI, KC_LALT,                           KC_SPC,                             MO(_L2), MO(_L1),    MO(_L2), KC_RCTL),






/* Keymap _L1: Function Layer
   * ,-----------------------------------------------------------------------.
   * |    |  F1|  F2|  F3|  F4|  F5|  F6|  F7|  F8|  F9|  F0|    |    |      |
   * |-----------------------------------------------------------------------|
   * |      |    |    |    |    |    |Home|PgUp|  Up|PgDn| End|Sclk|Paus|    |
   * |-----------------------------------------------------------------------|
   * |       |    |    |    |    |    |    | Lft| Dwn|Rght|    |    |        |
   * |-----------------------------------------------------------------------|
   * |         |    | App|    |    |    |    |    |    |    |    |           |
   * |-----------------------------------------------------------------------|
   * |     |     |     |                            |     |     |     |      |
   * `-----------------------------------------------------------------------'
   * ,-----------------------------------------------------------.
   * | ~ | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  DEL  |
   * |-----------------------------------------------------------|
   * |     |   |  |  |  |  |Hom|PgU|Up |PgD|End |Sclk|Paus|      |
   * |-----------------------------------------------------------|
   * |      |    |    |   |  |  |  |Lf|Dwn|Rgh|    |    |  Ins   |
   * |-----------------------------------------------------------|
   * |        |   |App|  |  |   |   |   |    |   |    |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_L1] = LAYOUT_60_ansi(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP,  KC_UP,   KC_PGDN, KC_END,  KC_SLCK, KC_PAUS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT,  KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,          KC_INS, \
  KC_TRNS, KC_TRNS, KC_APP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),








  /* Keymap _L2: Function Layer
   * ,-----------------------------------------------------------------------.
   * |    |    |    |    |    |    |    |    |    |    |    |    |    | RESET|
   * |-----------------------------------------------------------------------|
   * |      |    |    |    |    |    |WhlU|Btn1| MUp|Btn2|    |    |    |    |
   * |-----------------------------------------------------------------------|
   * |       |    |    |    |    |    |WhlP|MLft|MDwn|MRgt|    |    |        |
   * |-----------------------------------------------------------------------|
   * |         |    |    |    |    |    |WhlD|    |    |    |    |           |
   * |-----------------------------------------------------------------------|
   * |     |     |     |                            |     |     |     |      |
   * `-----------------------------------------------------------------------'
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |  RESET|
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |WhU|Lcl|M_U|Rcl|   |   |   |     |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   |WhP|M_L|M_D|M_R|   |   |        |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |WhD|   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'   
   */
[_L2] = LAYOUT_60_ansi(
        /*
  #ifdef RGBLIGHT_ENABLE
  KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC,  BL_INC,  BL_TOGG, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, \
  KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS,                   KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  #else
 */ 
  KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN3, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,          KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_D, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
//  #endif
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [ESC_TILD]  = ACTION_FUNCTION(SHIFT_ESC),
  [TAB_FN2]  = ACTION_LAYER_TAP_KEY(_L2, KC_TAB),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for Esc, twice for Caps Lock
    [O_BRCK]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, LSFT(KC_LBRC)),
        // Other declarations would go here, separated by commas, if you have them
};
