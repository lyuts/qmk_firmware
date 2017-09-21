#include QMK_KEYBOARD_H
#include "ergodox_infinity.h"
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "action_tapping.h"
#include "version.h"
#include "mousekey.h"
#include "eeconfig.h"
#include "eeprom.h"

//#ifdef SUBPROJECT_infinity
//#include "visualizer/lcd_backlight.h"
//#endif

#define _BASE 0 // Default layer
#define _L1 1 // Symbols
#define _L2 2 // Media/Mouse
#define _L3 3 // Numpad

// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

enum DualRoleKeyId {
    ESC_TILD = 0,
    TEENSY_KEY
};

//enum function_id {
//    SHIFT_ESC,
//};


enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Esc/Tild|   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab/L2 |   Q  |   W  |   E  |   R  |   T  |  [   |           |  +   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |  =   |------+------+------+------+------+--------|
 * | L1     |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |  '/L1  |
 * |--------+------+------+------+------+------|  ]   |           |  _   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |  -   |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |  L3  |      | LGui | LAlt |                                       | RAlt | RGui | Menu |  App | Ctrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Ins  |Teensy|       |Teensy|      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       | PgUp |      |      |
 *                                 | Bcksp| Del  |------|       |------|Enter |Spc/L2|
 *                                 |      |      | End  |       | PgDn |      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[_BASE] = KEYMAP(  // layer 0 : default
        // left hand
        F(ESC_TILD),      KC_1,     KC_2,   KC_3,      KC_4,     KC_5,   KC_NO,
        LT(_L2, KC_TAB),  KC_Q,     KC_W,   KC_E,      KC_R,     KC_T,   KC_LBRC,
        MO(_L1),          KC_A,     KC_S,   KC_D,      KC_F,     KC_G,
        KC_LSFT,          KC_Z,     KC_X,   KC_C,      KC_V,     KC_B,   KC_RBRC,
        KC_LCTRL,         MO(_L3),  KC_NO,  KC_LGUI,   KC_LALT,

                                                      KC_INS, F(TEENSY_KEY),
                                                              KC_HOME,
                                              KC_BSPC,KC_DELT,KC_END,

        // right hand
             KC_NO,       KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
             KC_EQL,      KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,          LT(_L1, KC_QUOT),
             KC_MINS,     KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,
                                  KC_RALT, KC_RGUI,KC_MENU,KC_APP,           KC_RCTL,

             F(TEENSY_KEY),        KC_NO,
             KC_PGUP,
             KC_PGDN,KC_ENT, LT(_L2, KC_SPC)
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |    `    |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      | Home | PgUp |  Up  | PgDn | End  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------|      | Left | Down | Rght |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |    . |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------| Ins  |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[_L1] = KEYMAP(
       // left hand
       KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,
       KC_TRNS,  KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_TRNS,
       KC_TRNS,  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV,
       KC_TRNS,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

                                                         KC_TRNS,  KC_TRNS,
                                                                   KC_TRNS,
                                               KC_TRNS,  KC_TRNS,  KC_TRNS,

       // right hand
       KC_F12,  KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_HOME, KC_PGUP,KC_UP,   KC_PGDN, KC_END,  KC_TRNS,
                KC_TRNS, KC_LEFT,KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_INS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Version|      |PrScr |ScrlLk|Pause |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |WhlUp |MsRght| MsUp |MsLeft|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|WhlPrs|      | MsDn | MsRg |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |WhlDn |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[_L2] = KEYMAP(
       VRSN,    KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          EPRM, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,       KC_TRNS,     KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_MS_WH_UP,   KC_MS_BTN1,  KC_MS_U, KC_MS_BTN2,  KC_TRNS, KC_TRNS,
                 KC_MS_BTN3,    KC_MS_L,     KC_MS_D, KC_MS_R,     KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_MS_WH_DOWN, KC_TRNS,     KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                          KC_TRNS,     KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Media and mouse keys?
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      | Num  |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |   7  |   8  |   9  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |   4  |   5  |   6  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |   1  |   2  |   3  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |   0  |   .  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[_L3] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,       KC_NLCK,     KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,       KC_KP_7,     KC_KP_8, KC_KP_9,     KC_TRNS, KC_TRNS,
                 KC_TRNS,       KC_KP_4,     KC_KP_5, KC_KP_6,     KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,       KC_KP_1,     KC_KP_2, KC_KP_3,     KC_TRNS, KC_TRNS,
                                KC_TRNS,     KC_KP_0, KC_KP_DOT,   KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(_L1),                // FN1 - Momentary Layer 1 (Symbols)
    [ESC_TILD]  = ACTION_FUNCTION(ESC_TILD),
    [TEENSY_KEY] = ACTION_FUNCTION(TEENSY_KEY), 
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
      case ESC_TILD:
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
      case TEENSY_KEY:
          clear_keyboard();
          print("\n\nJump to bootloader... ");
          wait_ms(250);
          bootloader_jump(); // should not return
          print("not supported.\n");
          break;

  }
}
