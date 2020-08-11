//
// Created by zy on 8/8/20.
//

#ifndef TIMELY_LANG_LOG_H
#define TIMELY_LANG_LOG_H
#include "stdio.h"
#include "stdarg.h"
#include "token.h"

void lexer_error(char *m, char *s, unsigned int row, unsigned int col);


void parser_error(char *m,char *s, Token* token);



#endif //TIMELY_LANG_LOG_H
