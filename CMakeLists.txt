cmake_minimum_required(VERSION 4.1.6)
project("C++ Data Structures" LANGUAGES CXX)

include_directories( include )

add_executable(main
	src/main.cpp
)

target_compile_features(main PRIVATE cxx_std_23)
target_compile_options(main PRIVATE -g -O0 -Wall -Wextra -fsanitize=address,undefined)
target_link_options(main PRIVATE -fsanitize=address,undefined)
