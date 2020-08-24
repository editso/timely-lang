//
// Created by zy on 2020/8/21.
//

#ifndef TIMELY_LANG_TSTRING_H
#define TIMELY_LANG_TSTRING_H
#include "string.h"

typedef struct str_buff_ {
    // 初始 buff 大小
    unsigned int init_size;
    unsigned int len;
    unsigned int buff_size;
    char *body;
} CharBuff;

CharBuff *new_buff(unsigned int size);

int append_str(CharBuff *buff, char *c);

int append_chr(CharBuff *buff, char c);

char buff_get(CharBuff *buff, int index);

char *to_string(CharBuff *buff);

void print_buff(CharBuff *buff);

void clear_buff(CharBuff *buff);

/**
 * 回收 malloc
 */
void recycle_buff(CharBuff *buff);

/**
 * 反转字符串
 * @param s被反转的字符串
 * @return 反转后的
 */
char *reverse(char *s);

/**
 * int 类型转 字符类型
 * @return 转换好的
 */
char *itochr(int num);

#endif //TIMELY_LANG_TSTRING_H
