//
// Created by zy on 8/13/20.
//
#include "include/tstring.h"
#include "include/basic.h"
#include "include/tmath.h"

void buff_zero(char* buff, unsigned int size){
    memset(buff, '\0', size);
}

CharBuff* new_buff(unsigned int size){
    CharBuff* buff = malloc(sizeof(CharBuff));
    size =  MALLOC_SIZE(char, +size);
    buff->body = malloc(MALLOC_SIZE(char, +size));
    buff->len = 0;
    buff->init_size = size;
    buff->buff_size = size;
    buff_zero(buff->body, size);
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
int re_sbuff(CharBuff* buff, unsigned int new_size){
    if (new_size <= buff->buff_size){
        new_size = buff->buff_size * 2;
    }
    new_size = MALLOC_SIZE(char, +new_size);
    buff->buff_size = new_size;
    char* old_buff = buff->body;
    char* new_buff = malloc(new_size);
    buff_zero(new_buff, new_size);
    if (new_buff == NULL)return t_false;
    buff->body = memcpy(new_buff, buff->body, buff->len);
    free(old_buff);
    return t_true;
}


int sbuff_write(CharBuff* buff, char c){
    if (buff->len >= buff->buff_size){
        if (re_sbuff(buff, buff->buff_size * 2) == 0)return t_false;
    }
    buff->body[buff->len++] = c;
    return t_true;
}

int append_chr(CharBuff* buff, char c){
    return sbuff_write(buff, c);
}

int append_str(CharBuff* buff, char *c){
    unsigned long len = str_len_(c);
    for (int i = 0; i < len; ++i) {
        if (sbuff_write(buff, c[i])  == 0)return t_false;
    }
    return t_true;
}

char* to_string(CharBuff* buff){
    char* s = malloc(MALLOC_SIZE(char,  +buff->len-1));
    buff_zero(s, buff->len);
    return strcpy(s, buff->body);
}

void print_buff(CharBuff* buff){
    printf("%s\n",  buff->body);
}

void clear_buff(CharBuff* buff){
    free(buff->body);
    buff->body = require_not_null(malloc(sizeof(char) * buff->init_size), "clear buff error!");
    buff->buff_size = buff->init_size;
    buff->len = 0;
    buff_zero(buff->body, buff->init_size);
}

char buff_get(CharBuff* buff, int index){
    if (buff->len > index)
        return buff->body[index];
    return '\0';
}

void recycle_buff(CharBuff* buff){
    if (buff != NULL){
        free(buff->body);
        free(buff);
    }
}


char *itochr(int i) {
    int num = abs(i);
    if (num == 0) return "0";
    CharBuff *buff = new_buff(10);
    int n;
    while (num > 0) {
        n = num % 10;
        append_chr(buff, (char) (n + '0'));
        num /= 10;
    }
    if (i < 0) {
        append_chr(buff, '-');
    }
    char *value = to_string(buff);
    free(buff->body);
    free(buff);
    return reverse(value);
}

char *reverse(char *s) {
    unsigned long len = strlen(s);
    char chr;
    for (unsigned int i = len - 1, j = 0; j < i; --i, j++) {
        chr = s[j];
        s[j] = s[i];
        s[i] = chr;
    }
    return s;
}