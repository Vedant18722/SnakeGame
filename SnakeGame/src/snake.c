#include "snake.h"
#include <stdlib.h>
#include <time.h>

void init_game(Snake* snake, Point* food, int grid_width, int grid_height) {
    int center_x = grid_width / 2;
    int center_y = grid_height / 2;
    
    snake->body[0] = (Point){center_x, center_y};
    snake->body[1] = (Point){center_x - 1, center_y};
    snake->body[2] = (Point){center_x - 2, center_y};
    snake->length = 3;
    snake->direction = DIR_RIGHT;
    
    generate_food(food, snake, grid_width, grid_height);
}

void move_snake(Snake* snake) {
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
    
    Point head = snake->body[0];
    switch (snake->direction) {
        case DIR_UP:    head.y--; break;
        case DIR_RIGHT: head.x++; break;
        case DIR_DOWN:  head.y++; break;
        case DIR_LEFT:  head.x--; break;
    }
    snake->body[0] = head;
}

void change_direction(Snake* snake, int new_direction) {
    int opposite = (snake->direction + 2) % 4;
    if (new_direction != opposite) {
        snake->direction = new_direction;
    }
}

int check_collision(const Snake* snake, int grid_width, int grid_height) {
    Point head = snake->body[0];
    
    if (head.x < 0 || head.x >= grid_width || head.y < 0 || head.y >= grid_height) {
        return 1;
    }
    
    for (int i = 1; i < snake->length; i++) {
        if (head.x == snake->body[i].x && head.y == snake->body[i].y) {
            return 1;
        }
    }
    
    return 0;
}

int check_food_collision(const Snake* snake, const Point* food) {
    Point head = snake->body[0];
    return (head.x == food->x && head.y == food->y);
}

void generate_food(Point* food, const Snake* snake, int grid_width, int grid_height) {
    int valid = 0;
    while (!valid) {
        food->x = rand() % grid_width;
        food->y = rand() % grid_height;
        
        valid = 1;
        for (int i = 0; i < snake->length; i++) {
            if (food->x == snake->body[i].x && food->y == snake->body[i].y) {
                valid = 0;
                break;
            }
        }
    }
}

void grow_snake(Snake* snake) {
    snake->length++;
}