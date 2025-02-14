#pragma once

typedef struct {
    uint8_t blinks;
    bool light_state;
    bool blinker_running;
    uint16_t timer;
    uint16_t period;
    uint8_t key;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t max_blinks;
} blinker_t;

#define CREATE_BLINKER(PERIOD, KEY, R, G, B) \
  {                                          \
    .blinks = 0,                             \
    .light_state = false,                    \
    .blinker_running = false,                \
    .timer = 0,                              \
    .period = PERIOD,                        \
    .key = KEY,                              \
    .r = R,                                  \
    .g = G,                                  \
    .b = B,                                  \
    .max_blinks = 0                          \
  }


void blink_led(blinker_t *blinker) {
    if (blinker->blinker_running) {
        if (timer_elapsed(blinker->timer) > blinker->period) {
            blinker->light_state = !blinker->light_state; blinker->timer = timer_read();
            if (blinker->light_state) {
                blinker->blinks++;
            } else if (blinker->blinks >= blinker->max_blinks) {
                blinker->blinker_running = false;
            }
        }

        if (blinker->light_state) {
            rgb_matrix_set_color(blinker->key, blinker->r, blinker->g, blinker->b);
        }
    }
}

void start_blinker(blinker_t *blinker, uint8_t max_blinks) {
    blinker->blinks = 0;
    blinker->timer = timer_read() - blinker->period;
    blinker->light_state = false;
    blinker->blinker_running = true;
    blinker->max_blinks = max_blinks;
}
