#include "snek.h"

uint8_t snake_len() {
    if (snake_head >= snake_tail) {
        return 1 + snake_head - snake_tail;
    } else {
        return SNAKE_MAX_LEN - (snake_tail - snake_head - 1);
    }
}

bool hit_food() {
    coord_t head_pos = snake_cells[snake_head];
    return head_pos.row == food_pos.row && head_pos.col == food_pos.col;
}

bool hit_snake() {
    coord_t head_pos = snake_cells[snake_head];
    coord_t cell_pos;
    for (uint8_t i = snake_tail; i != snake_head; i = (i + 1) % SNAKE_MAX_LEN) {
        cell_pos = snake_cells[i];
        if (cell_pos.row == head_pos.row && cell_pos.col == head_pos.col) {
            return true;
        }
    }
    return false;
}

void advance_head() {
    coord_t new_head = snake_cells[snake_head];
    switch (snake_dir) {
        case up:
            new_head.row = (new_head.row - 1) % SNAKE_ROWS;
            break;
        case down:
            new_head.row = (new_head.row + 1) % SNAKE_ROWS;
            break;
        case left:
            new_head.col = (new_head.col - 1) % SNAKE_COLS;
            break;
        case right:
            new_head.col = (new_head.col + 1) % SNAKE_COLS;
            break;
    }
    snake_head = (snake_head + 1) % SNAKE_MAX_LEN;
    snake_cells[snake_head] = new_head;
}

void advance_tail() {
    snake_tail = (snake_tail + 1) % SNAKE_MAX_LEN;
}

void place_snake() {
    snake_tail = 0;
    snake_head = 0;
    uint8_t row = rand() % SNAKE_ROWS;
    uint8_t col = rand() % SNAKE_COLS;
    snake_cells[snake_tail].row = row;
    snake_cells[snake_tail].col = col;
    snake_dir = rand() % 4;
    advance_head();
}

void place_food() {
    while (true) {
        uint8_t row = rand() % SNAKE_ROWS;
        uint8_t col = rand() % SNAKE_COLS;
        bool in_snake = false;
        coord_t cell_pos;
        for (uint8_t i = snake_tail; i != snake_head; i = (i + 1) % SNAKE_MAX_LEN) {
            cell_pos = snake_cells[i];
            if (row == cell_pos.row && col == cell_pos.col) {
                in_snake = true;
                break;
            }
        }
        cell_pos = snake_cells[snake_head];
        if (row == cell_pos.row && col == cell_pos.col) {
            in_snake = true;
        }
        if (in_snake) {
            continue;
        }
        food_pos.row = row;
        food_pos.col = col;
        break;
    }
}

void init_game() {
    place_snake();
    place_food();
}

bool tick() {
    advance_head();
    if (hit_snake()) {
        init_game();
    } else if (snake_len() == SNAKE_MAX_LEN) {
        init_game();
        return true;
    } else if (hit_food()) {
        place_food();
    } else {
        advance_tail();
    }
    return false;
}
