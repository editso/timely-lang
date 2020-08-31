//
// Created by zy on 8/8/20.
//

#ifndef TIMELY_LANG_BASIC_H
#define TIMELY_LANG_BASIC_H
#include "log.h"
#include <setjmp.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>

#define new(type) require_not_null(malloc(sizeof(type)), "Failed to allocate space")
#define new_char(chr) memset(new(char), chr, 1)

typedef int bool;
#define true  1
#define false 0


#define STR2(s) #s
#define STR(s) STR2(s)

#ifndef __TIMELY__JMP__
#define __TIMELY__JMP__


#define MALLOC_SIZE(t, size) sizeof(t) size

#define try(buff) if(!setjmp(buff))
#define catch(no) else if(errno == no)
#define throw(buff, v) longjmp(buff,v);
#endif


char *token_pos(Token *token);

unsigned long hash(void *key);

void out_token(Token *token);

void* require_not_null(void* any, char *message);

#endif //TIMELY_LANG_BASIC_H
