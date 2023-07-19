cmake_minimum_required(VERSION 3.5.1)

project(debug)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_library(mylib SHARED src/mylib.c)

target_compile_options(mylib PUBLIC -fPIC -g)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)


#add_executable(add add.c)
#target_link_libraries(add loop)
#target_compile_options(add PUBLIC -g)


add_executable(main src/main.c)
target_link_libraries(main dl pthread)
target_compile_options(main PUBLIC -g)

add_executable(main_n_g src/main.c)
target_link_libraries(main_n_g dl pthread)

