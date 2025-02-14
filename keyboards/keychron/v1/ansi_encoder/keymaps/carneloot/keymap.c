#include QMK_KEYBOARD_H
#include "blinker.h"

// clang-format off

enum layers{
    BASE,
    FN_1,
    GAMES,
    FN_3
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// Accented letters

#define UC_ATIL UC(0x00E3)
#define UC_OTIL UC(0x00F5)
#define UC_ACUT UC(0x00E1)
#define UC_ECUT UC(0x00E9)
#define UC_ICUT UC(0x00ED)
#define UC_OCUT UC(0x00F3)
#define UC_CDIL UC(0x00E7)
#define UC_AGRA UC(0x00E0)

const uint16_t PROGMEM cdil_combo[] = {KC_QUOT, KC_C, COMBO_END};
const uint16_t PROGMEM atil_combo[] = {KC_SCLN, KC_A, COMBO_END};
const uint16_t PROGMEM otil_combo[] = {KC_GRV, KC_O, COMBO_END};
const uint16_t PROGMEM acut_combo[] = {KC_QUOT, KC_A, COMBO_END};
const uint16_t PROGMEM ecut_combo[] = {KC_QUOT, KC_E, COMBO_END};
const uint16_t PROGMEM icut_combo[] = {KC_QUOT, KC_I, COMBO_END};
const uint16_t PROGMEM ocut_combo[] = {KC_QUOT, KC_O, COMBO_END};
const uint16_t PROGMEM agra_combo[] = {KC_LBRC, KC_A, COMBO_END};

combo_t key_combos[] = {
    COMBO(cdil_combo, UC_CDIL),
    COMBO(atil_combo, UC_ATIL),
    COMBO(otil_combo, UC_OTIL),
    COMBO(acut_combo, UC_ACUT),
    COMBO(ecut_combo, UC_ECUT),
    COMBO(icut_combo, UC_ICUT),
    COMBO(ocut_combo, UC_OCUT),
    COMBO(agra_combo, UC_AGRA),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ansi_82(
        KC_ESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_MUTE,
        KC_GRV,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_DEL,
        KC_TAB,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_HOME,
        KC_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_END,
        KC_LSFT, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL, KC_LCMD,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(FN_1), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [FN_1] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  KC_CALC,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_PSCR,            RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  UC_NEXT,  _______,  _______,    _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            KC_PGUP,
        KC_CAPS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  QK_BOOT,  _______,  _______,  _______,  _______,              _______,            KC_PGDN,
        _______,            _______,  _______,  CM_TOGG,  _______,  _______,  NK_TOGG,  KX_CATG,  _______,  _______,  _______,              _______,  _______,
        _______,  GU_TOGG,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),

    [GAMES] = LAYOUT_ansi_82(
        KC_ESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_MUTE,
        KC_GRV,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_DEL,
        KC_TAB,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_HOME,
        KC_CAPS, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_END,
        KC_LSFT, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL, KC_LCMD,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(FN_3), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [FN_3] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  KC_CALC,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_PSCR,            RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            KC_PGUP,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  QK_BOOT,  _______,  _______,  _______,  _______,              _______,            KC_PGDN,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  KX_CATG,  _______,  _______,  _______,              _______,  _______,
        _______,  GU_TOGG,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
};
#endif // ENCODER_MAP_ENABLE

// Turn on Caps Lock LED
#if defined(RGB_MATRIX_ENABLE)

#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#else
    #define MAX_BRIGHTNESS 0xFF
#endif

uint8_t caps_lock_leds[] = {
    0, 15, 30, 45, 59, 72, 73, 74, 76, 77, 78,
    70, 57, 43, 28, 13, 29, 44, 58, 5, 6, 7, 8
};

size_t caps_lock_leds_size = sizeof caps_lock_leds / sizeof caps_lock_leds[0];

#ifdef KEY_CANCELLATION_ENABLE

#define SOCD_BLINK_PERIOD 200
#define SOCD_BLINK_KEY 66 // M
#define SOCD_BLINK_R 0x00
#define SOCD_BLINK_G 0x74
#define SOCD_BLINK_B 0xff

blinker_t socd_blinker = CREATE_BLINKER(
    SOCD_BLINK_PERIOD,
    SOCD_BLINK_KEY,
    SOCD_BLINK_R,
    SOCD_BLINK_G,
    SOCD_BLINK_B
);

const key_cancellation_t PROGMEM key_cancellation_list[] = {
    [0] = {KC_D, KC_A, KX_KEEP_PRESSED},
    [1] = {KC_A, KC_D, KX_KEEP_PRESSED}
};

#endif

#if defined(COMBO_ENABLE)

#define COMBO_BLINK_PERIOD 200
#define COMBO_BLINK_KEY 62 // C
#define COMBO_BLINK_R 0x06
#define COMBO_BLINK_G 0xA7
#define COMBO_BLINK_B 0x04

blinker_t combo_blinker = CREATE_BLINKER(
    COMBO_BLINK_PERIOD,
    COMBO_BLINK_KEY,
    COMBO_BLINK_R,
    COMBO_BLINK_G,
    COMBO_BLINK_B
);

#endif

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        uint8_t b = MAX_BRIGHTNESS;
        for (int i = 0; i < caps_lock_leds_size; i++) {
            rgb_matrix_set_color(caps_lock_leds[i], b, b, b);
        }
    }

    // Win key disabled = set light to on
    if (keymap_config.no_gui) {
        // #eb005a
        rgb_matrix_set_color(73, 0xEB, 0x00, 0x5A);
    }

#ifdef KEY_CANCELLATION_ENABLE
    blink_led(&socd_blinker);
#endif


#if defined(COMBO_ENABLE)
    blink_led(&combo_blinker);
#endif

    return true;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef KEY_CANCELLATION_ENABLE
    if (!record->event.pressed && keycode == QK_KEY_CANCELLATION_TOGGLE) {
        socd_blinker.max_blinks = key_cancellation_is_enabled() ? 2 : 1;
        start_blinker(&socd_blinker);
    }
#endif

#if defined(COMBO_ENABLE)
    if (!record->event.pressed) {
        if (keycode == QK_COMBO_TOGGLE) {
            combo_blinker.max_blinks = is_combo_enabled() ? 2 : 1;
            start_blinker(&combo_blinker);
        } else if (keycode == UC_NEXT) {
            combo_blinker.max_blinks = get_unicode_input_mode() == UNICODE_MODE_LINUX ? 1 : 2;
            start_blinker(&combo_blinker);
        }
    }
#endif

    return true;
}

