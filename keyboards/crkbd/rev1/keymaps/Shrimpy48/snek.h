#pragma once

#include QMK_KEYBOARD_H

#define SNAKE_ROWS MATRIX_ROWS
#define SNAKE_COLS MATRIX_COLS
#define SNAKE_MAX_LEN (SNAKE_ROWS * SNAKE_COLS)

typedef enum {
    up, down, left, right,
} dir_t;

typedef struct {
    int8_t row;
    int8_t col;
} coord_t;

coord_t snake_cells[SNAKE_MAX_LEN];
uint8_t snake_head;
uint8_t snake_tail;
dir_t snake_dir;
coord_t food_pos;

uint8_t snake_len(void);

bool hit_food(void);

bool hit_snake(void);

void advance_head(void);

void advance_tail(void);

void place_snake(void);

void place_food(void);

void init_game(void);

bool tick(void);

