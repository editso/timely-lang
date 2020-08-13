//
// Created by zy on 8/7/20.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/lexer.h"
#include "include/list.h"
#include "include/basic.h"

char c_buf_[1];
int read_chr(struct lexer* lexer){
    if (lexer->last_chr == EMPTY){
        bzero(c_buf_, sizeof(c_buf_));
        lexer->col_pos++;
        if (fread(c_buf_, sizeof(c_buf_), 1,lexer->file) <= 0){
            fclose(lexer->file); // 关流
            lexer->also = t_false;
            return END;
        }
        return *c_buf_;
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

void unread_chr(Lexer* lexer, int pos){
    lexer->last_chr = pos;
}

char* read_letter(Lexer *lexer){
    int chr;
    List * buff = new_list();
    while ((chr = read_chr(lexer)) != END){
        // a_9 | a$9
        if (is_letter(chr) || is_symbol(chr) || is_digit(chr)){
            list_add(buff, GET_CHAR(chr));
        }else{
            unread_chr(lexer, chr);
            break;
        }
    }
    char *s = list_to_string(buff);
    free(buff);
    return s;
}

char* read_digit(Lexer *lexer){
    int chr;
    List *buff = new_list();
    t_bool dot = t_false;
    while ((chr = read_chr(lexer)) != END){
        if (is_digit(chr)){
            list_add(buff, GET_CHAR(chr));
        } else if (chr == '.' && !dot){
            dot = t_true;
            int pre_chr = chr;
            chr = read_chr(lexer);
            if (is_digit(chr)){
                list_add(buff, GET_CHAR(pre_chr));
                list_add(buff, GET_CHAR(chr));
                dot = t_true;
            }else{
                unread_chr(lexer, chr);
                break;
            }
        }else{
            unread_chr(lexer, chr);
            break;
        }
    }
    char *s = list_to_string(buff);
    free(buff);
    return s;
}

char* read_string(Lexer *lexer){
    int chr;
    List *buff = new_list();
    int flag = 0;
    while ((chr = read_chr(lexer)) != END){
        if (chr == '\'' || chr == '"'){
            list_add(buff, GET_CHAR(chr));
            if (flag && !strcmp((char *)&chr, buff->head->data)){
                break;
            }
            flag = 1;
        }else{
            list_add(buff, GET_CHAR(chr));
        }
    }
    if (chr == END){
        lexer_error("String is not closed normally",
                    list_to_string(buff),
                    lexer->row_pos,
                    lexer->col_pos);
    }
    char *s = list_to_string(buff);
    free(buff);
    return s;
}

KindMeta find_kind(char *kind){
    for (int i = 0; i < kind_count; ++i) {
        if (strcmp(kind_table[i].name, kind) == 0){
            return kind_table[i];
        }
    }
    return EMPTY_KIND;
}

Token* new_token(struct lexer* lexer, int kind, char *text){
    Token* token = malloc(sizeof(Token));
    token->col_pos = lexer->col_pos - 1 - strlen(text);
    token->row_pos = lexer->row_pos;
    token->kind = kind;
    token->text = text;
    return token;
}


Token* new_end_token(){
    Token* token = malloc(sizeof(Token));
    token->kind = END;
    return token;
}

void read_all(Lexer *lexer){
    int chr;

    while ((chr = read_chr(lexer)) != END){
        if (is_new_line(chr)){
            lexer->col_pos = 1;
            lexer->row_pos++;
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
            case ':':
            case ';':{
                int op = read_chr(lexer);
                /**
                 * ++  -- ....
                 */
                switch (op) {
                    case '.':
                    case '+':
                    case '-':
                    case '&':
                    case '|':
                    case '>':
                    case '=':{
                        char *array = malloc(sizeof(char) + 1);
                        array[0] = (char)chr;
                        array[1] = (char)op;
                        KindMeta kind = find_kind(array);
                        list_add(lexer->tokens, new_token(lexer, kind.kind, array));
                        break;
                    }
                    default:{
                        unread_chr(lexer, op);
                        char *c = malloc(sizeof(char));
                        *c = (char)chr;
                        list_add(lexer->tokens, new_token(lexer, chr, c));
                        break;
                    }
                }
                break;
            }
            case '\'':
            case '"':
                /**
                 *  处理字符串
                 *
                 */
                unread_chr(lexer, chr);
                list_add(lexer->tokens, new_token(lexer, STRING, read_string(lexer)));
                break;
            default:{
                if (is_digit(chr)){
                    unread_chr(lexer, chr);
                    list_add(lexer->tokens, new_token(lexer,NUMBER, read_digit(lexer)));
                } else if (is_letter(chr) || is_symbol(chr)){
                    unread_chr(lexer, chr);
                    Kind kind;
                    char *c = read_letter(lexer);
                    if ((kind = find_kind(c).kind) == EMPTY){
                        kind = ID;
                    }
                    list_add(lexer->tokens, new_token(lexer, kind, c));
                }else if (is_new_line(chr)){
                    char* s = malloc(sizeof(char));
                    *s = (char)chr;
                    list_add(lexer->tokens, new_token(lexer, NEWLINE, s));
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
            read_all(lexer);
        } else{
            return t_false;
        }
    }
    return t_true;
}

Lexer* new_lexer(char *file){
    struct lexer *lexer = malloc(sizeof(struct lexer));
    if ((lexer->file = fopen(file, "r")) == NULL){
        perror("timely");
        exit(0);
    }
    lexer->source = file;
    lexer->tokens = malloc(sizeof(List));
    lexer->last_chr = EMPTY;
    lexer->row_pos = 1;
    lexer->col_pos = 1;
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
