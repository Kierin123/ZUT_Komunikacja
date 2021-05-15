cmake_minimum_required(VERSION 3.15.4)
project(lab1)
 
include_directories(
    app/inc
    deps/inc
)

file(GLOB SOURCES "app/src/*.c"
                  "deps/src/*.c"
                  "app/src/*.cpp"
                  "deps/src/*.cpp"
)

 
add_compile_options(-Wall -Wextra -pedantic)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} "pthread")

add_definitions(-DLOG_USE_COLOR)
