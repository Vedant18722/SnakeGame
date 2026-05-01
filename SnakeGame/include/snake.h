#ifndef SNAKE_H
#define SNAKE_H

#define DIR_UP    0
#define DIR_RIGHT 1
#define DIR_DOWN  2
#define DIR_LEFT  3

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point body[400];
    int length;
    int direction;
} Snake;

void init_game(Snake* snake, Point* food, int grid_width, int grid_height);
void move_snake(Snake* snake);
void change_direction(Snake* snake, int new_direction);
int check_collision(const Snake* snake, int grid_width, int grid_height);
int check_food_collision(const Snake* snake, const Point* food);
void generate_food(Point* food, const Snake* snake, int grid_width, int grid_height);
void grow_snake(Snake* snake);

#endif