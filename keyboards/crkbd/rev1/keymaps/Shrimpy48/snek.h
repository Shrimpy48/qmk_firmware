#pragma once

#include QMK_KEYBOARD_H

#define SNAKE_ROWS 3
#define SNAKE_COLS 12
#define SNAKE_MAX_LEN 28

uint8_t decmod(uint8_t x, uint8_t n);

uint8_t incmod(uint8_t x, uint8_t n);

typedef enum {
    up,
    down,
    left,
    right,
} dir_t;

typedef struct {
    uint8_t row : 4;
    uint8_t col : 4;
} coord_t;

typedef struct {
    coord_t snake_cells[SNAKE_MAX_LEN];
    uint8_t snake_head;
    uint8_t snake_tail;
    coord_t food_pos;
    dir_t   snake_dir;
} snake_state_t;

snake_state_t snake_state;

uint8_t snake_len(void);

dir_t tail_dir(void);

bool hit_food(void);

bool hit_snake(void);

void advance_head(void);

void advance_tail(void);

void place_snake(void);

void place_food(void);

void init_game(void);

bool tick(void);

