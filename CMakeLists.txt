cmake_minimum_required(VERSION 3.17)
project(timely_lang C)

set(CMAKE_C_STANDARD 99)

add_executable(timely main.c include/token.h include/parser.h include/lexer.h lexer.c include/tree.h include/list.h list.c include/basic.h basic.c include/log.h tree.c include/eval.h include/map.h map.c include/envir.h envir.c include/tio.h tio.c tstring.c include/stack.h stack.c parser.c include/tmath.h tmath.c include/tstring.h log.c)