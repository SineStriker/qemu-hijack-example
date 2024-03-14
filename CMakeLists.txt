cmake_minimum_required(VERSION 3.19)

project(player VERSION 0.0.0.0 LANGUAGES C CXX)

file(GLOB_RECURSE _src *.h *.cpp)
add_executable(${PROJECT_NAME} ${_src})

find_package(FFmpeg CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
ffmpeg_link_libraries(${PROJECT_NAME} PRIVATE avcodec avformat swresample)