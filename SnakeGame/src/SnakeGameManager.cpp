#include "snake.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    #define CLEAR_SCREEN "clear"
#endif

class SnakeGameManager {
private:
    Snake snake;
    Point food;
    int grid_width = 20;
    int grid_height = 20;
    int score = 0;
    bool game_over = false;

    void clear_screen() {
        system(CLEAR_SCREEN);
    }

    void render() {
        clear_screen();
        std::cout << "=== SNAKE GAME (C/C++ Hybrid) ===\n";
        std::cout << "Score: " << score << " | Length: " << snake.length << "\n";
        std::cout << "WASD to move | R=Restart\n";
        std::cout << std::string(grid_width + 2, '=') << "\n";

        for (int y = 0; y < grid_height; y++) {
            std::cout << "|";
            for (int x = 0; x < grid_width; x++) {
                bool is_head = (snake.body[0].x == x && snake.body[0].y == y);
                bool is_body = false;
                
                for (int i = 1; i < snake.length; i++) {
                    if (snake.body[i].x == x && snake.body[i].y == y) {
                        is_body = true;
                        break;
                    }
                }
                
                bool is_food = (food.x == x && food.y == y);
                
                if (is_head) std::cout << "@";
                else if (is_body) std::cout << "O";
                else if (is_food) std::cout << "*";
                else std::cout << ".";
            }
            std::cout << "|\n";
        }
        std::cout << std::string(grid_width + 2, '=') << "\n";
        
        if (game_over) {
            std::cout << "GAME OVER! Final Score: " << score << "\n";
            std::cout << "Press R to restart...\n";
        }
    }

#ifdef _WIN32
    char get_input() {
        if (_kbhit()) {
            return _getch();
        }
        return 0;
    }
#else
    char get_input() {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        setbuf(stdin, NULL);
        
        char c = 0;
        if (read(STDIN_FILENO, &c, 1) > 0) {
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt);
            return c;
        }
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt);
        return 0;
    }
#endif

public:
    SnakeGameManager() {
        srand(time(NULL));
        init_game();
    }

    void init_game() {
        ::init_game(&snake, &food, grid_width, grid_height);
        score = 0;
        game_over = false;
    }

    void run() {
        while (true) {
            char key = get_input();
            
            if (key) {
                if (game_over && (key == 'r' || key == 'R')) {
                    init_game();
                } else if (!game_over) {
                    int new_dir = -1;
                    switch (key) {
                        case 'w': case 'W': new_dir = DIR_UP; break;
                        case 'a': case 'A': new_dir = DIR_LEFT; break;
                        case 's': case 'S': new_dir = DIR_DOWN; break;
                        case 'd': case 'D': new_dir = DIR_RIGHT; break;
                    }
                    if (new_dir != -1) {
                        ::change_direction(&snake, new_dir);
                    }
                }
            }

            if (!game_over) {
                ::move_snake(&snake);
                
                if (::check_food_collision(&snake, &food)) {
                    ::grow_snake(&snake);
                    score += 10;
                    ::generate_food(&food, &snake, grid_width, grid_height);
                }
                
                game_over = ::check_collision(&snake, grid_width, grid_height);
            }
            
            render();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }
};