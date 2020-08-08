//
// Created by zy on 8/7/20.
//

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "lexer.h"
#include "list.h"

char buf[1];

int read_char(struct lexer* lexer){
    bzero(buf,sizeof(buf));
    if (read(lexer->fd, buf,sizeof(buf)) <= 0){
        close(lexer->fd); // 关闭流
        return END;
    }
    lexer->cur_pos++;
    return buf[0];
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

char* read_letter(struct lexer* lexer){
    return "";
}

long read_digit(struct lexer* lexer){
    return -1;
}

Token* new_token(struct lexer* lexer, int kind, char *text){
    Token* token = malloc(sizeof(Token));
    token->col_pos = lexer->cur_pos;
    token->row_pos = lexer->cur_line;
    token->kind = kind;
    token->text = text;
    return token;
}

Lexer* new_lexer(char *file){
    struct lexer *lexer = malloc(sizeof(struct lexer));
    lexer->tokens = malloc(sizeof(struct list));
    if ((lexer->fd = open(file, O_RDONLY)) <= 0){
        perror("timely");
        exit(0);
    }
    return lexer;
}

void read_line(struct lexer* lexer){
    int chr;
    Token* token;
    while ((chr = read_char(lexer)) != END){
        if (is_new_line(chr)){
            lexer->cur_pos = 0;
            lexer->cur_line++;
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
                break;
            default:{
                if (is_digit(chr)){
                    token  = new_token(lexer, NUMBER, (char *) read_digit(lexer));
                } else if (is_letter(chr)){
                    token = new_token(lexer, ID, read_letter(lexer));
                }
                if (token != NULL){
                    list_add(lexer->tokens, token);
                }
            }
        }
    }
}