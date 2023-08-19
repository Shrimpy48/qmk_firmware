RGB_MATRIX_EFFECT(musical)
// RGB_MATRIX_EFFECT(my_cool_effect)
RGB_MATRIX_EFFECT(snek)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "transactions.h"

#include "snek.h"

static uint8_t lerp(uint8_t start, uint8_t end, uint8_t num, uint8_t div) {
    uint16_t dist = end - start;
    return start + (uint8_t)((dist * (uint16_t)num) / (uint16_t)div);
}

static uint8_t led_key_groups[14][5] = {
    {24, 25, 26, NO_LED, NO_LED}, {2, 3, 21, 22, 23}, {18, 19, 20, NO_LED, NO_LED}, {1, 15, 16, 17, NO_LED}, {10, 11, 12, NO_LED, NO_LED}, {0, 7, 8, 9, NO_LED},
    {4, 5, 6, 13, 14},
    {31, 32, 33, 40, 41},
    {27, 34, 35, 36, NO_LED}, {37, 38, 39, NO_LED, NO_LED}, {28, 42, 43, 44, NO_LED}, {45, 46, 47, NO_LED, NO_LED}, {29, 30, 48, 49, 50}, {51, 52, 53, NO_LED, NO_LED},
};

static bool musical(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);
    for (uint8_t g = 0; g < 14; g++) {
        // Work out the tick for this group
        uint16_t tick = max_tick;
        for (uint8_t idx = 0; idx < 5; idx++) {
            uint8_t i = led_key_groups[g][idx];
            if (i == NO_LED) {
                continue;
            }
            // Reverse search to find most recent key hit
            for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
                if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                    tick = g_last_hit_tracker.tick[j];
                    break;
                }
            }
        }
        // Set the LEDs for this group
        uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
        HSV hsv = rgb_matrix_config.hsv;
        hsv.h = 19 * g;
        hsv.v = scale8(255 - offset, hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        for (uint8_t idx = 0; idx < 5; idx++) {
            uint8_t i = led_key_groups[g][idx];
            if ((i < led_min) || (i >= led_max) || (i == NO_LED)) {
                continue;
            }
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

// e.g: A simple effect, self-contained within a single method
// static bool my_cool_effect(effect_params_t* params) {
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);
//     for (uint8_t i = led_min; i < led_max; i++) {
//         HSV hsv = rgb_matrix_config.hsv;
//         if (led_max > led_min + 1) {
//             hsv.h = lerp(0, 85, i - led_min, led_max - 1 - led_min);
//         } else {
//             hsv.h = 170;
//         }
//         RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//     }
//     return rgb_matrix_check_finished_leds(led_max);
// }

// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
uint16_t last_tick_time;
uint16_t last_sync_time;
static keypos_t snake_to_matrix(coord_t snake_pos) {
    keypos_t out;
    if (snake_pos.col < 6) {
        out.row = snake_pos.row;
        out.col = snake_pos.col;
    } else {
        out.row = snake_pos.row + 4;
        out.col = 11 - snake_pos.col;
    }
    return out;
}
static void snek_complex_init(effect_params_t* params) {
  if (is_keyboard_master()) {
      init_game();
      last_tick_time = g_rgb_timer;
      last_sync_time = 0;
  }
}
static bool snek_complex_run(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  // TODO: move tick to a housekeeping thing
  uint16_t time = g_rgb_timer;
  if (is_keyboard_master()) {
      if ((time - last_tick_time) > 65535 / qadd8(rgb_matrix_config.speed, 64)) {
          tick();
          last_tick_time = time;
      }
    if (last_sync_time != last_tick_time) {
        snake_state_t m2s = snake_state;
        if(transaction_rpc_send(USER_SYNC_SNEK, sizeof(m2s), &m2s)) {
            last_sync_time = last_tick_time;
        }
      }
  }
  uint8_t end = snake_len() - 1;
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    HSV hsv = rgb_matrix_config.hsv;
    keypos_t cell_pos;
    bool found = false;
    uint8_t snake_seg = 0;
    for (uint8_t idx = snake_state.snake_tail; idx != snake_state.snake_head; idx = incmod(idx, SNAKE_MAX_LEN)) {
        cell_pos = snake_to_matrix(snake_state.snake_cells[idx]);
        if (g_led_config.matrix_co[cell_pos.row][cell_pos.col] == i) {
            hsv.h = lerp(43, 64, end-snake_seg, end);
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            found = true;
            break;
        }
        snake_seg++;
    }
    if (!found) {
        cell_pos = snake_to_matrix(snake_state.snake_cells[snake_state.snake_head]);
        if (g_led_config.matrix_co[cell_pos.row][cell_pos.col] == i) {
            hsv.h = 85;
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            cell_pos = snake_to_matrix(snake_state.food_pos);
            if (g_led_config.matrix_co[cell_pos.row][cell_pos.col] == i) {
                hsv.h = 0;
                RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            } else {
                hsv.v = 0;
                RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
  }
  return rgb_matrix_check_finished_leds(led_max);
}
static bool snek(effect_params_t* params) {
  if (params->init) snek_complex_init(params);
  return snek_complex_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
