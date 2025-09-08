
cmake_minimum_required(VERSION 3.21)
project(Carol C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
	${CMAKE_SOURCE_DIR}/src/include/
	${CMAKE_SOURCE_DIR}/src/utils/
)
# TODO: Getting all the source files with '*.c' is not a good practice.
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	${CMAKE_SOURCE_DIR}/src/utils/*.c
	${CMAKE_SOURCE_DIR}/src/*.c
)

add_executable(carol ${SRC_FILES})
target_compile_options(carol PRIVATE -std=c99 -Wall -Werror)

