cmake_minimum_required(VERSION 3.19)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(player VERSION 0.0.0.0 LANGUAGES C CXX)

file(GLOB_RECURSE _src src/*.h src/*.c src/*.cpp)
add_executable(${PROJECT_NAME} ${_src})

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)