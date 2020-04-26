cmake_minimum_required(VERSION 2.8)
project(hess C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_C_FLAGS "-std=c89 -Os -fPIC -Wno-unused-result -static -D LOG")

add_executable(hess_1st_order hess_1st_order.c)
