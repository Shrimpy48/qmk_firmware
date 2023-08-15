#include "snek.h"

uint8_t decmod(uint8_t x, uint8_t n) {
    if (x == 0) {
        return n - 1;
    }
    return x - 1;
}

uint8_t incmod(uint8_t x, uint8_t n) {
    if (x == n - 1) {
        return 0;
    }
    return x + 1;
}

uint8_t snake_len() {
    if (snake_state.snake_head > snake_state.snake_tail) {
        return 1 + snake_state.snake_head - snake_state.snake_tail;
    } else {
        return SNAKE_MAX_LEN + 1 - (snake_state.snake_tail - snake_state.snake_head);
    }
}

dir_t tail_dir() {
    coord_t head = snake_state.snake_cells[snake_state.snake_head];
    coord_t neck = snake_state.snake_cells[decmod(snake_state.snake_head, SNAKE_MAX_LEN)];
    if (neck.col < head.col) {
        return left;
    } else if (neck.col > head.col) {
        return right;
    } else if (neck.row < head.row) {
        return up;
    } else {
        return down;
    }
}

bool hit_food() {
    coord_t head_pos = snake_state.snake_cells[snake_state.snake_head];
    return head_pos.row == snake_state.food_pos.row && head_pos.col == snake_state.food_pos.col;
}

bool hit_snake() {
    coord_t head_pos = snake_state.snake_cells[snake_state.snake_head];
    coord_t cell_pos;
    for (uint8_t i = snake_state.snake_tail; i != snake_state.snake_head; i = incmod(i, SNAKE_MAX_LEN)) {
        cell_pos = snake_state.snake_cells[i];
        if (cell_pos.row == head_pos.row && cell_pos.col == head_pos.col) {
            return true;
        }
    }
    return false;
}

void advance_head() {
    coord_t new_head = snake_state.snake_cells[snake_state.snake_head];
    switch (snake_state.snake_dir) {
        case up:
            new_head.row = decmod(new_head.row, SNAKE_ROWS);
            break;
        case down:
            new_head.row = incmod(new_head.row, SNAKE_ROWS);
            break;
        case left:
            new_head.col = decmod(new_head.col, SNAKE_COLS);
            break;
        case right:
            new_head.col = incmod(new_head.col, SNAKE_COLS);
            break;
    }
    snake_state.snake_head = incmod(snake_state.snake_head, SNAKE_MAX_LEN);
    snake_state.snake_cells[snake_state.snake_head] = new_head;
}

void advance_tail() {
    snake_state.snake_tail = incmod(snake_state.snake_tail, SNAKE_MAX_LEN);
}

void place_snake() {
    snake_state.snake_tail = 0;
    snake_state.snake_head = 0;
    uint8_t row = rand() % SNAKE_ROWS;
    uint8_t col = rand() % SNAKE_COLS;
    snake_state.snake_cells[snake_state.snake_tail].row = row;
    snake_state.snake_cells[snake_state.snake_tail].col = col;
    snake_state.snake_dir = rand() % 4;
    advance_head();
}

void place_food() {
    while (true) {
        uint8_t row = rand() % SNAKE_ROWS;
        uint8_t col = rand() % SNAKE_COLS;
        bool in_snake = false;
        coord_t cell_pos;
        for (uint8_t i = snake_state.snake_tail; i != snake_state.snake_head; i = incmod(i, SNAKE_MAX_LEN)) {
            cell_pos = snake_state.snake_cells[i];
            if (row == cell_pos.row && col == cell_pos.col) {
                in_snake = true;
                break;
            }
        }
        cell_pos = snake_state.snake_cells[snake_state.snake_head];
        if (row == cell_pos.row && col == cell_pos.col) {
            in_snake = true;
        }
        if (in_snake) {
            continue;
        }
        snake_state.food_pos.row = row;
        snake_state.food_pos.col = col;
        break;
    }
}

void init_game() {
    place_snake();
    place_food();
}

bool tick() {
    advance_head();
    // At this point, head can == tail.
    // The tail cannot be food, so it will immediately advance.
    if (hit_food()) {
        place_food();
    } else {
        advance_tail();
    }
    if (hit_snake()) {
        init_game();
    } else if (snake_len() >= SNAKE_MAX_LEN) {
        init_game();
        return true;
    }
    return false;
}
