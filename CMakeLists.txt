cmake_minimum_required(VERSION 3.5)
project(linux_dirty_talk C)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/include)
add_library(kiki_api kiki_api.c)

add_executable(kiki_tester kiki_tester.c)
target_link_libraries(kiki_tester kiki_api)
