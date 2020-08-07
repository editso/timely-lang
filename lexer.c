//
// Created by zy on 8/7/20.
//

#include <string.h>
#include <stdio.h>
#include "lexer.h"

char *source;
unsigned long len;
unsigned int cur_index;
unsigned int cur_pos;
unsigned int cur_line = 1;

int read_char(){
    if (cur_index >= len)
        return END;
    cur_pos++;
    return source[cur_index++];
}

int is_letter(int chr){
    return  chr >= 'a' && chr <= 'z' ||
            chr >= 'A' && chr <= 'Z';
}

int is_digit(int chr){
    return chr >= '0' && chr <= '9';
}

int is_new_line(int chr){
    return chr == '\r' || chr <=  '\n';
}

void lexer(char *s){
    source = s;
    len = strlen(s);
    int chr;
    while ((chr = read_char()) != END){
        if (is_new_line(chr)){
            cur_pos = 0;
            cur_line++;
        }
        switch (chr) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '&':
            case '|':
            case '!':
            case '(':
            case ')':
            case '{':
            case '}':
            case '%':
            case '[':
            case ']':
            case '>':
            case '<':
            case '=':
            case ',':
            case ';':
                printf("key world\n");
                break;
            default:
                if (is_digit(chr)){
                    printf("digit\n");
                } else if (is_letter(chr)){
                    printf("letter\n");
                }
        }
    }
}
