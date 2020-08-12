cmake_minimum_required(VERSION 3.17)
project(timely_lang C)

set(CMAKE_C_STANDARD 99)

add_executable(timely_lang timely.c include/token.h include/parser.h include/lexer.h src/parser.c src/lexer.c include/tree.h include/list.h src/list.c include/basic.h src/basic.c include/log.h src/tree.c include/eval.h include/map.h src/map.c include/envir.h src/envir.c include/stream.h src/stream.c)