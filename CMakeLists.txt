cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ringbuffer src/ringbuffer.cpp)
add_library(multibuffer src/multibuffer.cpp)

target_include_directories(ringbuffer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_include_directories(multibuffer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)


project(bufftest VERSION 0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(bufftest
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ringbuffer
        multibuffer
        -lpthread
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        _DEBUG
        RINGBUFF_AUTO_FIRST_ROTATE
)
