cmake_minimum_required(VERSION 3.17)
project(timely_lang C)

set(CMAKE_C_STANDARD 99)

add_executable(timely_lang timely.c include/token.h include/parser.h include/lexer.h parser.c lexer.c include/tree.h include/list.h list.c include/basic.h basic.c include/log.h tree.c include/eval.h include/map.h map.c include/envir.h envir.c include/stream.h stream.c buff.c include/stack.h stack.c)