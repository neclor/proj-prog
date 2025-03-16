cmake_minimum_required(VERSION 3.10)
project(Project_2)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)


include_directories(
  ${GTK2_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/lib
)


file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE LIB_FILES "${PROJECT_SOURCE_DIR}/lib/*.a")
file(GLOB_RECURSE SHARED_LIB_FILES "${PROJECT_SOURCE_DIR}/lib/*.so")


add_executable(${PROJECT_NAME} ${SRC_FILES})


target_link_libraries(${PROJECT_NAME}
  ${GTK2_LIBRARIES}
  ${LIB_FILES}
  ${SHARED_LIB_FILES}
)


target_compile_options(${PROJECT_NAME} PRIVATE --std=c99 --pedantic -Wall -W -Wmissing-prototypes)
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK2_CFLAGS_OTHER})
