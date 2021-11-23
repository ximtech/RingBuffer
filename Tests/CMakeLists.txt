cmake_minimum_required(VERSION 3.20)
project(Tests C)

set(CMAKE_C_STANDARD 99)

set(ROOT_DIR "..")
include_directories(${ROOT_DIR})

add_executable(
        Tests main.c
        munit/munit.h
        munit/munit.c
        munit/example.c

        ${ROOT_DIR}/RingBuffer.h
        ${ROOT_DIR}/RingBuffer.c
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME})