//
// Created by zy on 8/13/20.
//
#include "../include/basic.h"


void buff_zero(char* buff, unsigned int size){
    memset(buff, '\0', size);
}


StringBuff* new_sbuff(int size){
    StringBuff* buff = malloc(sizeof(StringBuff));
    size =  MALLOC_SIZE(char, +size);
    buff->body = malloc(MALLOC_SIZE(char, +size));
    buff_zero(buff->body, size);
    buff->len = 0;
    buff->buff_size = size;
    return buff;
}


unsigned long str_len_(const char* s){
    if (s == NULL)return 0;
    unsigned int i = 0;
    while (s[i++] != '\0');
    return i - 1;
}

/**
 * 扩展buff大小
 * @param buff buff容器指针
 * @param new_size 新的buff大小
 * @return 成功 1 否则 -1
 */
int re_sbuff(StringBuff* buff, unsigned int new_size){
    if (new_size <= buff->buff_size){
        new_size = buff->buff_size * 2;
    }
    new_size = MALLOC_SIZE(char, +new_size);
    buff->buff_size = new_size;
    char* old_buff = buff->body;
    char* new_buff = malloc(sizeof(char) * new_size);
    buff_zero(new_buff, new_size);
    if (new_buff == NULL)return t_false;
    buff->body = memcpy(new_buff, buff->body, buff->len);
    free(old_buff);
    return t_true;
}


int sbuff_write(StringBuff* buff, char c){
    if (buff->len >= buff->buff_size){
        if (re_sbuff(buff, buff->buff_size * 2) == 0)return t_false;
    }
    buff->body[buff->len++] = c;
    return t_true;
}

int append_chr(StringBuff* buff, char c){
    return sbuff_write(buff, c);
}

int append_str(StringBuff* buff, char *c){
    unsigned long len = str_len_(c);
    for (int i = 0; i < len; ++i) {
        if (sbuff_write(buff, c[i])  == 0)return t_false;
    }
    return t_true;
}

char* to_string(StringBuff* buff){
    char* s = malloc(MALLOC_SIZE(char,  +buff->len));
    buff_zero(s, buff->len);
    return strcpy(s, buff->body);
}

void print_buff(StringBuff* buff){
    printf("%s\n",  buff->body);
}

void clear_buff(StringBuff* buff){
    buff_zero(buff->body, buff->buff_size);
}