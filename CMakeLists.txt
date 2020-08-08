cmake_minimum_required(VERSION 3.17)
project(timely_lang C)

set(CMAKE_C_STANDARD 99)

add_executable(timely_lang timely.c token.h parser.h lexer.h parser.c lexer.c ast/tree.h list.h list.c basic.h basic.c log.h log.c)