// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define VIMM 1 // vim
#define SYMB 2 // symbols
#define MOUSE 3 // mouse

enum {
    M_RSFT,
    M_00,
    M_000,
    M_DBQUOT,
    M_BKQUOT,
    M_QUOT,
    M_CBR,
    M_PRN,
    M_BRC,
    M_TAG,
    M_MINS,
    TD_ESC_CAPS
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: base layer
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  L1    | 1 !  | 2 @  | 3 #  | 4 $  | 5 %  | Hyper|           | Meh  | 6 ^  | 7 &  | 8 *  | 9 (  | 0 )  |  del   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  ~`  |           |      |   Y  |   U  |   I  |   O  |   P  |  \ |   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Ctl    |   A  |   S  | D/~L3|   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |  "'    |
 * |--------+------+------+------+------+------|  -   |           |  =   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ~L2  |      |      | Alt  |  Gui |                                       |  Gui | Esc  |   [  |   ]  |  FN0 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | App  |PrtSc |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 |Space/| Tab/ |------|       |------|  Back  |Enter |
 *                                 |L1    | L2   | End  |       | PgDn |  Space |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        DF(VIMM),     KC_1,   KC_2,    KC_3,              KC_4,               KC_5,    ALL_T(KC_NO),
        KC_TAB,       KC_Q,   KC_W,    KC_E,              KC_R,               KC_T,    KC_GRV,
        CTL_T(KC_NO), KC_A,   KC_S,    LT(MOUSE, KC_D),   KC_F,               KC_G,
        KC_LSFT,      KC_Z,   KC_X,    KC_C,              KC_V,               KC_B,    KC_MINS,
        MO(VIMM),    KC_NO,  KC_NO,   KC_LALT,           GUI_T(KC_LANG2),
                                                         ALT_T(KC_APP),     KC_PSCREEN,         KC_HOME,
                                                         LT(VIMM, KC_SPC),  LT(SYMB, KC_TAB),  KC_END,
        // right hand
        MEH_T(KC_NO), KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     KC_DELT,
        KC_NO,        KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     KC_BSLS,
                      KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        KC_EQL,       KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                              GUI_T(KC_LANG1),  KC_ESC,  KC_LBRC, KC_RBRC,  KC_FN0,
        KC_NO,    KC_NO,
        KC_PGUP,
        KC_PGDN,  KC_BSPC,  KC_ENT
    ),
/* Keymap 1: Vim Nomal Mode
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |      |      |      |  $   |      |      |           |      |  ^   |      |      |      |  0   |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Word | End  | Redo |NTab  |      |           |      | Copy | Undo | L0   | L0   |Paste |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | L0   |Search| Cut  | PgDn | Home |------|           |------| Left | Down | Up   |Right |Alfred|        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Del  |      |Select| PgUp |      |           |      |      | Menu |      |      | Find |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ~L2  |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|Del   |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Vim Mode
[VIMM] = KEYMAP(
       KC_ESC,  KC_NO,   KC_NO,             KC_NO,     LCTL(KC_E),KC_NO, KC_NO,
       KC_TRNS, KC_TRNS, LALT(KC_RIGHT),    KC_END,    LGUI(LSFT(KC_Z)), LGUI(KC_T), KC_TRNS,
       KC_TRNS, DF(BASE),LGUI(LALT(KC_F)),  LGUI(KC_X),KC_PGDN,          KC_HOME,
       KC_TRNS, KC_TRNS, KC_DELT,   KC_TRNS,LALT(LSFT(KC_RIGHT)),        KC_PGUP,    KC_TRNS,
       MO(VIMM), KC_TRNS, KC_TRNS,   KC_TRNS,KC_TRNS,
                                            KC_TRNS, KC_TRNS,
                                                     KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_NO,    LCTL(KC_A), KC_NO,      KC_NO,    KC_NO,     LCTL(KC_A),  KC_TRNS,
       KC_TRNS,  LGUI(KC_C), LGUI(KC_Z), DF(BASE), DF(BASE),  LGUI(KC_V),  KC_TRNS,
                 KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,  LALT(KC_SPC),KC_TRNS,
       KC_TRNS,  KC_TRNS,    LCTL(KC_F2),KC_TRNS,  KC_TRNS,   LGUI(KC_F),  KC_TRNS,
                             KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_FN2,
       KC_TRNS, OSL(BASE),
       KC_TRNS,
       KC_TRNS, KC_DELT, KC_TRNS
),
/* Keymap 2: 10key Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 |   /    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | ```  |  ''  |  {}  |  </> |  /   |           |  -   |      |   7  |   8  |   9  |      |   -    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | ---  |  ""  |  ()  |  <>  |------|           |------| 000  |   4  |   5  |   6  |      |   +    |
 * |--------+------+------+------+------+------|  *   |           |  +   |------+------+------+------+------+--------|
 * |        |      |      |      |  []  |      |      |           |      | 00   |   1  |   2  |   3  |      |   *    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |  ,   |   .  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------| BS   |  =   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,  KC_F1,    KC_F2,       KC_F3,       KC_F4,    KC_F5,    KC_F11,
       KC_TRNS,  KC_TRNS,  M(M_BKQUOT), M(M_QUOT),   M(M_CBR), KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  M(M_MINS),   M(M_DBQUOT), M(M_PRN), M(M_TAG),
       KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,     M(M_BRC), KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,
                                                               KC_TRNS,  KC_TRNS,
                                                                         KC_TRNS,
                                                     KC_TRNS,  KC_TRNS,  KC_TRNS,
       // right hand
       KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_SLSH,
       KC_TRNS,  KC_TRNS,  KC_7,     KC_8,     KC_9,     KC_TRNS,   KC_MINS,
                 M(M_000), KC_4,     KC_5,     KC_6,     KC_TRNS,   KC_PLUS,
       KC_TRNS,  M(M_00),  KC_1,     KC_2,     KC_3,     KC_TRNS,   KC_ASTR,
                           KC_0,     KC_COMM,  KC_DOT,   KC_TRNS,   KC_TRNS,
       KC_TRNS,  KC_TRNS,
       KC_TRNS,
       KC_TRNS,  KC_BSPC,  KC_EQL
),
/* Keymap 3: mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Power  |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | RESET  |      |      |      |      |      |      |           |      |      |      | MsUp |      |      | Play   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      | ACL0 |      |------|           |------|      |MsLeft|MsDown|MsRght|      | Next   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |MsWhL |           |MsWhR |      |      |      |      |      | Prev   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | Lclk | Rclk | BTN3 | BTN4 | BTN5 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | Mute |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |VolUp |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |VolDn |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Mouse
[MOUSE] = KEYMAP(
       KC_POWER,KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
       RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_ACL1, KC_TRNS, KC_ACL0, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_L,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right handa
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_MPLY,
                 KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_MNXT,
       KC_WH_R,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV,
                          KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5,
       KC_MUTE, KC_TRNS,
       KC_VOLU,
       KC_VOLD, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(BASE),
    [1] = ACTION_LAYER_TAP_TOGGLE(MOUSE),                // FN1 - Momentary Layer 1 (Symbols)
    [2] = ACTION_LAYER_MOMENTARY(BASE)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case M_RSFT:
            if (record->event.pressed) {
              register_code(KC_RSFT);
            } else {
              unregister_code(KC_RSFT);
            }
            break;
        case M_00:
            if (record->event.pressed) {
                return MACRO( I(25), T(P0), T(P0), END );
            }
            break;
        case M_000:
            if (record->event.pressed) {
                return MACRO( I(25), T(P0), T(P0), T(P0), END );
            }
            break;
        case M_DBQUOT:
            if (record->event.pressed) {
                SEND_STRING("\"\"");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            break;
        case M_QUOT:
            if (record->event.pressed) {
                SEND_STRING("''");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            break;
        case M_CBR:
            if (record->event.pressed) {
                SEND_STRING("{}");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            break;
        case M_PRN:
            if (record->event.pressed) {
                SEND_STRING("()");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            break;
        case M_BRC:
            if (record->event.pressed) {
                SEND_STRING("[]");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            break;
        case M_TAG:
            if (record->event.pressed) {
                SEND_STRING("<>");
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            break;
        case M_BKQUOT:
            if (record->event.pressed) {
                SEND_STRING("```");
            }
            break;
        case M_MINS:
            if (record->event.pressed) {
                SEND_STRING("---");
            }
            break;
      }
    return MACRO_NONE;
};

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
        default:
            // none
            break;
    }

};
