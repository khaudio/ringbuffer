cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_library(ringbuffer src/ringbuffer.cpp)
# add_library(multibuffer src/multibuffer.cpp)

# target_include_directories(ringbuffer
#     INTERFACE
#         ${CMAKE_CURRENT_SOURCE_DIR}/inc
#     PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}/inc
#     PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}/inc
# )

# target_include_directories(multibuffer
#     INTERFACE
#         ${CMAKE_CURRENT_SOURCE_DIR}/inc
#     PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}/inc
#     PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}/inc
# )


project(bufftest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CXX_EXTENSIONS on)
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}
    src/ringbuffer.cpp
    src/multibuffer.cpp
    src/main.cpp
)

target_include_directories(bufftest
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        _DEBUG
        RINGBUFF_AUTO_FIRST_ROTATE
)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -pedantic -Werror -Wextra -Wall -Wshadow-compatible-local")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif(CMAKE_COMPILER_IS_GNUCXX)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Debug>:${CMAKE_CXX_FLAGS}>
        $<$<CONFIG:Release>:-O2>
        $<$<CONFIG:RelWithDebInfo>:-O2 -g>
)
