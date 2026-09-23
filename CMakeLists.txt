cmake_minimum_required(VERSION 3.21)
project(c_utils VERSION 1.0.0 LANGUAGES C)

set(TEST_UTILITIES_NAME c_utils-examples)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# --- VALIDATIONS AND WARNINGS

if (MSVC)
    set(COMPILER_WARNING_FLAGS /W4 /WX)
else()
    set(COMPILER_WARNING_FLAGS -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion)
endif()

option(ENABLE_SANITIZERS "Enable address sanitizers and undefined-behavior sanitizers" OFF)

if(ENABLE_SANITIZERS AND NOT MSVC)
    add_compile_options(-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address -fsanitize=undefined)
endif()

# --- DEFINITION OF THE LIBRARY ---

add_library(${PROJECT_NAME} STATIC
        src/linked_list.c
        src/array_list.c
        src/queue.c
        src/hash_map.c
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Build the examples to use
enable_testing()
add_subdirectory(examples)