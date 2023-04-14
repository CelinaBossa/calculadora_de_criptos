cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME main)
project(${PROJECT_NAME})

include_directories(include)

add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wconversion -std=gnu11)

add_executable(${PROJECT_NAME} "./src/main.c")