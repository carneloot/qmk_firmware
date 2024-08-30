// Copyright 2024 Harrison Chan (@xelus22)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_key_cancellation.h"
#include <string.h>
#include "keycodes.h"
#include "keycode_config.h"
#include "action_util.h"
#include "keymap_introspection.h"

/**
 * @brief function for querying the enabled state of key cancellation
 *
 * @return true if enabled
 * @return false if disabled
 */
bool key_cancellation_is_enabled(void) {
    return keymap_config.key_cancellation_enable;
}

/**
 * @brief Enables key cancellation and saves state to eeprom
 *
 */
void key_cancellation_enable(void) {
    keymap_config.key_cancellation_enable = true;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Disables key cancellation and saves state to eeprom
 *
 */
void key_cancellation_disable(void) {
    keymap_config.key_cancellation_enable = false;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Toggles key cancellation's status and save state to eeprom
 *
 */
void key_cancellation_toggle(void) {
    keymap_config.key_cancellation_enable = !keymap_config.key_cancellation_enable;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief handler for user to override whether key cancellation should process this keypress
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Allow key cancellation
 * @return false Stop processing and escape from key cancellation
 */
__attribute__((weak)) bool process_key_cancellation_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

#define SET_SIZE 128  // Adjust based on your keyboard matrix size

typedef struct {
    uint16_t keys[SET_SIZE];
    uint8_t count;
} KeySet;

KeySet __pressed_keys = { .keys = {0}, .count = 0 };

// Function to add a key to the set
bool __add_key_to_set(KeySet *set, uint16_t key) {
    for (uint8_t i = 0; i < set->count; i++) {
        if (set->keys[i] == key) {
            return false;  // Key already in the set
        }
    }
    if (set->count < SET_SIZE) {
        set->keys[set->count++] = key;
        return true;  // Key added to the set
    }
    return false;  // Set is full
}

// Function to remove a key from the set
bool __remove_key_from_set(KeySet *set, uint16_t key) {
    for (uint8_t i = 0; i < set->count; i++) {
        if (set->keys[i] == key) {
            set->keys[i] = set->keys[--set->count];  // Replace with the last element
            return true;  // Key removed from the set
        }
    }
    return false;  // Key not found in the set
}

// Function to check if a key is in the set
bool __is_key_in_set(const KeySet *set, uint16_t key) {
    for (uint8_t i = 0; i < set->count; i++) {
        if (set->keys[i] == key) {
            return true;  // Key is in the set
        }
    }
    return false;  // Key not in the set
}

/**
 * @brief Process handler for key_cancellation feature
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Continue processing keycodes, and send to host
 * @return false Stop processing keycodes, and don't send to host
 */
bool process_key_cancellation(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_KEY_CANCELLATION_ON:
                key_cancellation_enable();
                return false;
            case QK_KEY_CANCELLATION_OFF:
                key_cancellation_disable();
                return false;
            case QK_KEY_CANCELLATION_TOGGLE:
                key_cancellation_toggle();
                return false;
            default:
                break;
        }
    }

    if (!keymap_config.key_cancellation_enable) {
        return true;
    }

    // only supports basic keycodes
    if (!IS_BASIC_KEYCODE(keycode)) {
        return true;
    }

    if (!process_key_cancellation_user(keycode, record)) {
        return true;
    }

    // Adding unpress keys to pressed_keys store
    if (record->event.pressed) {
        __add_key_to_set(&__pressed_keys, keycode);
    } else {
        __remove_key_from_set(&__pressed_keys, keycode);
    }

    // loop through all the keyup and keydown events
    for (uint16_t i = 0; i < key_cancellation_count(); i++) {
        key_cancellation_t key_cancellation = key_cancellation_get(i);
        if (keycode == key_cancellation.press) {
            if (record->event.pressed) {
                del_key(key_cancellation.unpress);
            } else if (__is_key_in_set(&__pressed_keys, key_cancellation.unpress) && (key_cancellation.flags & KX_KEEP_PRESSED) != 0) {
                add_key(key_cancellation.unpress);
            }
        }
    }

    return true;
}
