cmake_minimum_required(VERSION 4.3)
project(marian_baza_danych C)

set(CMAKE_C_STANDARD 11)

add_executable(marian_baza_danych main.c)

#target_compile_options(marian_baza_danych PRIVATE
#        -g
#        -O0
#        -fsanitize=address,undefined
#)
#
#target_link_options(marian_baza_danych PRIVATE
#        -fsanitize=address,undefined
#)