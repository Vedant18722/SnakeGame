cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(snake_game 
    src/main.cpp 
    src/SnakeGameManager.cpp 
    src/snake.c
)

target_include_directories(snake_game PRIVATE include)

if(UNIX AND NOT APPLE)
    find_package(Curses REQUIRED)
    target_link_libraries(snake_game ${CURSES_LIBRARIES})
endif()