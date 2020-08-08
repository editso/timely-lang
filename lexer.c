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
    if (lexer->last_chr == EMPTY){
        bzero(buf,sizeof(buf));
        if (read(lexer->fd, buf, sizeof(buf)) <= 0){
            close(lexer->fd); // 关流
            lexer->also = t_false;
            return END;
        }
        lexer->cur_pos++;
        return buf[0];
    }else{
        int chr = lexer->last_chr;
        lexer->last_chr = EMPTY;
        return chr;
    }
}

int is_letter(int chr){
    return  chr >= 'a' && chr <= 'z' ||
            chr >= 'A' && chr <= 'Z';
}

int is_digit(int chr){
    return chr >= '0' && chr <= '9';
}

int is_symbol(int chr){
    return chr == '_' || chr == '$';
}

int is_new_line(int chr){
    return chr == '\r' || chr ==  '\n';
}

void set_last_chr(Lexer* lexer, int pos){
    lexer->last_chr = pos;
}

char* read_letter(struct lexer* lexer){
    int chr;
    struct list* buff = new_list();
    while ((chr = read_char(lexer)) != END){
        // a_9 | a$9
        if (is_letter(chr) || is_symbol(chr) || is_digit(chr)){
            list_add(buff, (void *)chr);
        }else{
            set_last_chr(lexer, chr);
            break;
        }
    }
    char *s = to_string(buff);
    free(buff);
    return s;
}

Symbol find_symbol(char *symbol){
    for (int i = 0; i < symbol_count; ++i) {
        if (strcmp(symbol_table[i].symbol, symbol) == 0){
            return symbol_table[i];
        }
    }
    return EMPTY_SYMBOL;
}

Token* new_token(struct lexer* lexer, int kind, char *text){
    Token* token = malloc(sizeof(Token));
    token->col_pos = lexer->cur_pos - 1 - strlen(text);
    token->row_pos = lexer->cur_line;
    token->kind = kind;
    token->text = text;
    return token;
}

char* read_digit(struct lexer* lexer){
    int chr;
    struct list *buff = new_list();
    t_bool dot = t_false;
    while ((chr = read_char(lexer)) != END){
        if (is_digit(chr)){
            list_add(buff, (void *)chr);
        } else if (chr == '.' && !dot){
            dot = t_true;
            int pre_chr = chr;
            chr = read_char(lexer);
            if (is_digit(chr)){
                list_add(buff, (void *)pre_chr);
                list_add(buff, (void *)chr);
                dot = t_true;
            }else{
                char *ch = malloc(sizeof(char));
                *ch = (char)chr;
                set_last_chr(lexer, chr);
                break;
            }
        }else{
            set_last_chr(lexer, chr);
            break;
        }
    }
    char *s = to_string(buff);
    free(buff);
    return s;
}


Token* new_end_token(){
    Token* token = malloc(sizeof(Token));
    token->kind = END;
    return token;
}

void read_line(Lexer *lexer){
    int chr;
    while ((chr = read_char(lexer)) != END){
        if (is_new_line(chr)){
            lexer->cur_pos = 0;
            lexer->cur_line++;
            break;
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
            case '.':
            case ';':{
                int op = read_char(lexer);
                switch (op) {
                    case '+':
                    case '-':
                    case '&':
                    case '|':
                    case '=':{
                        char *array = malloc(sizeof(char) + 1);
                        array[0] = (char)chr;
                        array[1] = (char)op;
                        Symbol symbol = find_symbol(array);
                        list_add(lexer->tokens, new_token(lexer, symbol.kind, array));
                        break;
                    }
                    default:{
                        set_last_chr(lexer, op);
                        char *c = malloc(sizeof(char));
                        *c = (char)chr;
                        list_add(lexer->tokens, new_token(lexer, chr, c));
                        break;
                    }
                }
                break;
            }
            default:{
                if (is_digit(chr)){
                    set_last_chr(lexer, chr);
                    list_add(lexer->tokens, new_token(lexer,NUMBER,read_digit(lexer)));
                } else if (is_letter(chr) || is_symbol(chr)){
                    set_last_chr(lexer, chr);
                    list_add(lexer->tokens, new_token(lexer, ID, read_letter(lexer)));
                }
            }
        }
    }
}


/**
 * 填充 list
 * @param lexer  --
 * @param index  --
 * @return 成功 true  否则 false
 */
t_bool fill_list(Lexer* lexer, int index){
    if (index >= lexer->tokens->size){
        if (lexer->also){
            int size = lexer->tokens->size;
            do {
                read_line(lexer);
            }while (lexer->also || index >= lexer->tokens->size);
        } else{
            return t_false;
        }
    }
    return t_true;
}

Lexer* new_lexer(char *file){
    struct lexer *lexer = malloc(sizeof(struct lexer));
    lexer->tokens = malloc(sizeof(struct list));
    if ((lexer->fd = open(file, O_RDONLY)) <= 0){
        perror("timely");
        exit(0);
    }
    lexer->last_chr = EMPTY;
    lexer->cur_pos = 1;
    lexer->cur_line = 1;
    lexer->also = t_true;
    return lexer;
}

Token* lexer_read(Lexer *lexer){
    Token* token;
    if ((token = lexer_peek(lexer, 0))->kind != END){
        return list_remove(lexer->tokens, 0);
    }
    return token;
}

Token* lexer_peek(Lexer* lexer, int index){
    if (fill_list(lexer, index)){
        Token *token = list_get(lexer->tokens, index);
        if (token == NULL)return new_end_token();
        return token;
    }
    return new_end_token();
}
