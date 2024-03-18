project(fakesdl LANGUAGES C CXX)

file(GLOB_RECURSE _src *.h *.c *.cpp)
add_library(${PROJECT_NAME} SHARED ${_src})

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 dl)

target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)

target_include_directories(${PROJECT_NAME} PUBLIC .)