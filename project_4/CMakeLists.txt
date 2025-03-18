cmake_minimum_required(VERSION 3.16)


project(game)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)


include_directories(${PROJECT_SOURCE_DIR}/src)


file(GLOB_RECURSE SOURCES src/*.c)


add_executable(${PROJECT_NAME} ${SOURCES})


target_compile_options(${PROJECT_NAME} PRIVATE --std=c99 --pedantic -Wall -W -Wextra -Wmissing-prototypes)


# Add GTK2
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
include_directories(${GTK2_INCLUDE_DIRS})
link_directories(${GTK2_LIBRARY_DIRS})
add_definitions(${GTK2_CFLAGS_OTHER})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK2_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK2_LIBRARIES})
