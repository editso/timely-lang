//
// Created by zy on 8/8/20.
//

#ifndef TIMELY_LANG_BASIC_H
#define TIMELY_LANG_BASIC_H
#include <stdio.h>
#include <stdarg.h>
#include "list.h"
#include "token.h"
#include "log.h"
#include "string.h"

#define GET_CHAR(chr) memset(malloc(sizeof(char)), chr, 1)
#define t_bool int
#define t_true  1
#define t_false 0


void print(char *, ...);


void out_token(Token* token);




long to_number(struct list *list);


#endif //TIMELY_LANG_BASIC_H
