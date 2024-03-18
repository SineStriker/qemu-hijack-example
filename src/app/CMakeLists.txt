project(player LANGUAGES C CXX)

file(GLOB_RECURSE _src *.h *.c *.cpp)
add_executable(${PROJECT_NAME} ${_src})

target_link_libraries(${PROJECT_NAME} PRIVATE fakesdl)