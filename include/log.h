//
// Created by zy on 8/8/20.
//

#ifndef TIMELY_LANG_LOG_H
#define TIMELY_LANG_LOG_H

#include "stdio.h"
#include "stdarg.h"
#include "token.h"

#define FONT_COLOR_RED      "\033[31m"
#define COLOR_NONE          "\033[0m"
#define FONT_COLOR_BLACK    "\033[30m"
#define FONT_COLOR_YELLOW   "\033[33m"
#define FONT_COLOR_GREEN    "\033[32m"
#define COLOR_YR            "\033[46;31m"

#define TAG_ERROR       FONT_COLOR_RED"ERROR"COLOR_NONE ": "
#define TAG_INFO        FONT_COLOR_GREEN"INFO"COLOR_NONE ": "
#define TAG_WARNING     FONT_COLOR_YELLOW"WARNING"COLOR_NONE ": "
#define TAG_DEBUG       COLOR_YR"DEBUG"COLOR_NONE ": "

#define LOG_LEVEL_INFO  1u
#define LOG_LEVEL_WARNING  LOG_LEVEL_INFO | 2u
#define LOG_LEVEL_ERROR  LOG_LEVEL_WARNING | 4u
#define LOG_LEVEL_DEBUG LOG_LEVEL_ERROR | 8u
#define LOG_DISABLE 0u

#define level log_level_
#define is_level(l) (level & l) == l


/**
 *  debug
 *  error
 *  warning
 *  info
 */
extern unsigned int log_level_;

void log_log(unsigned int l, FILE *file, char *message, va_list list);

void log_error(char *message, ...);

void log_warning(char *message, ...);

void log_info(char *message, ...);

void log_debug(char *message, ...);

void log_code(char *file, int row, int col, char *message, ...);

void lexer_error(char *m, char *s, unsigned int row, unsigned int col);


#endif //TIMELY_LANG_LOG_H
