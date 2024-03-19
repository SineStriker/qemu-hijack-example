project(fakesdl LANGUAGES C CXX)

file(GLOB_RECURSE _src *.h *.c *.cpp)
add_library(${PROJECT_NAME} SHARED ${_src})

target_link_libraries(${PROJECT_NAME} PRIVATE qemu-guest-entry)
target_include_directories(${PROJECT_NAME} PUBLIC .)