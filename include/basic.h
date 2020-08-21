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
#include "setjmp.h"
#include "errno.h"

#define GET_CHAR(chr) memset(malloc(sizeof(char)), chr, 1)
#define t_bool int
#define t_true  1
#define t_false 0

#ifndef __TIMELY__JMP__
#define __TIMELY__JMP__

#define STR2(s) #s
#define STR(s) STR2(s)

#define MALLOC_SIZE(t, size) sizeof(t) size

#define try(buff) if(!setjmp(buff))
#define catch(no) else if(errno == no)
#define throw(buff, v) longjmp(buff,v);
#endif


char *token_pos(Token *token);

unsigned long hash(void *key);

void out_token(Token *token);

long to_number(List *list);


#endif //TIMELY_LANG_BASIC_H
