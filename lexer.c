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

int read_chr(struct lexer *lexer) {
    if (lexer->file == NULL) return END;
    if (lexer->last_chr == EMPTY) {
        bzero(c_buf_, sizeof(c_buf_));
        lexer->col_pos++;
        if (fread(c_buf_, sizeof(c_buf_), 1, lexer->file) <= 0) {
            fclose(lexer->file); // 关流
            lexer->also = t_false;
            lexer->file = NULL;
            return END;
        }
        return *c_buf_;
    } else {
        int chr = lexer->last_chr;
        lexer->last_chr = EMPTY;
        return chr;
    }
}

int is_letter(int chr) {
    return chr >= 'a' && chr <= 'z' ||
           chr >= 'A' && chr <= 'Z';
}

int is_digit(int chr) {
    return chr >= '0' && chr <= '9';
}

int is_symbol(int chr) {
    return chr == '_' || chr == '$';
}

int is_new_line(int chr) {
    return chr == '\r' || chr == '\n';
}

void unread_chr(Lexer *lexer, int pos) {
    lexer->last_chr = pos;
}

KindMeta find_kind(char *kind) {
    for (int i = 0; i < kind_count; ++i) {
        if (strcmp(kind_table[i].name, kind) == 0) {
            return kind_table[i];
        }
    }
    return EMPTY_KIND;
}

Token *new_token(struct lexer *lexer, int kind, char *text) {
    Token *token = malloc(sizeof(Token));
    token->col_pos = lexer->col_pos - 1 - strlen(text);
    token->row_pos = lexer->row_pos;
    token->kind = kind;
    token->text = text;
    return token;
}

Token *new_end_token() {
    Token *token = malloc(sizeof(Token));
    token->kind = END;
    return token;
}

char *read_letter(Lexer *lexer, StringBuff* buff) {
    int chr;
    while ((chr = read_chr(lexer)) != END) {
        // a_9 | a$9
        if (is_letter(chr) || is_symbol(chr) || is_digit(chr) || chr < 0) {
            append_chr(buff, (char) chr);
        } else {
            unread_chr(lexer, chr);
            break;
        }
    }
    return to_string(buff);;
}

char *read_digit(Lexer *lexer, StringBuff* buff) {
    int chr;
    t_bool dot = t_false;
    while ((chr = read_chr(lexer)) != END) {
        if (is_digit(chr)) {
            append_chr(buff, (char) chr);
        } else if (chr == '.' && !dot) {
            dot = t_true;
            int pre_chr = chr;
            chr = read_chr(lexer);
            if (is_digit(chr)) {
                append_chr(buff, (char) pre_chr);
                append_chr(buff, (char) chr);
                dot = t_true;
            } else {
                unread_chr(lexer, chr);
                break;
            }
        } else {
            unread_chr(lexer, chr);
            break;
        }
    }
    return to_string(buff);
}

char *read_string(Lexer *lexer,StringBuff* buff) {
    int chr;
    int flag = 0;
    while ((chr = read_chr(lexer)) != END) {
        if (chr == '\'' || chr == '"') {
            append_chr(buff, (char) chr);
            if (flag && chr == buff_get(buff, 0)) {
                break;
            }
            flag = 1;
        } else {
            append_chr(buff, (char) chr);
        }
    }
    if (chr == END) {
        lexer_error("String is not closed normally",
                    to_string(buff),
                    lexer->row_pos,
                    lexer->col_pos);
    }
    return to_string(buff);;
}

/**
 * 多行注释
 */
char *read_multi_note(Lexer *lexer,StringBuff* buff) {
    int chr;
    int op;
    while ((chr = read_chr(lexer))) {
        if (chr == '*') {
            op = read_chr(lexer);
            // 可能下一个还是 * 那么记录下一个星
            if (op == '*') {
                append_chr(buff, (char) chr);
                unread_chr(lexer, op);
                continue;
            } else if (op == '/') {
                break;
            }
        }
        if (is_new_line(chr)) {
            lexer->row_pos++;
        }
        if (chr == END) {
            lexer_error("note is not closed normally",
                        to_string(buff),
                        lexer->row_pos,
                        lexer->col_pos);
        }
        append_chr(buff, (char) chr);
    }
    return to_string(buff);
}

/**
 * 单行
 */
char *read_single_note(Lexer *lexer, StringBuff* buff) {
    int chr;
    while ((chr = read_chr(lexer))) {
        if (is_new_line(chr) || chr == END) {
            lexer->row_pos++;
            break;
        }
        append_chr(buff, (char) chr);
    }
    return to_string(buff);
}

/**
 * 运算符
 */
Token *read_operator(Lexer* lexer, StringBuff* buff){
    int chr = read_chr(lexer);
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
        case '=': {
            append_chr(buff, (char) chr);
            append_chr(buff, (char) op);
            char *s = to_string(buff);
            KindMeta kind = find_kind(s);
            return new_token(lexer, kind.kind, s);
        }
        case '/':
        case '*': {
            if (op == '/') {
                // single
                read_single_note(lexer, buff);
            } else {
                // multi
                read_multi_note(lexer,  buff);
            }
            break;
        }
        default: {
            unread_chr(lexer, op);
            append_chr(buff, (char )chr);
            return new_token(lexer, chr, to_string(buff));
        }
    }
    append_chr(buff, (char)chr);
    return new_token(lexer, EMPTY,to_string(buff));
}

Token* select_token(Lexer* lexer, int chr, StringBuff* buff){
    switch (chr) {
        case ' ':
            break;
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
        case ';':
            unread_chr(lexer, chr);
            return read_operator(lexer, buff);
        case '\'':
        case '"':
            /**
             *  处理字符串
             *
             */
            unread_chr(lexer, chr);
            return new_token(lexer, CONST_STRING, read_string(lexer, buff));
        default: {
            if (is_digit(chr)) {
                unread_chr(lexer, chr);
                return new_token(lexer, NUMBER, read_digit(lexer, buff));
            } else if (is_letter(chr) || is_symbol(chr) || chr < 0) {
                unread_chr(lexer, chr);
                Kind kind;
                char *c = read_letter(lexer, buff);
                if ((kind = find_kind(c).kind) == EMPTY) {
                    kind = ID;
                }
                return new_token(lexer, kind, c);
            } else if (is_new_line(chr)) {
                append_chr(buff, (char) chr);
                return new_token(lexer, NEWLINE, to_string(buff));
            }
        }
    }
    append_chr(buff, (char)chr);
    return new_token(lexer, EMPTY, to_string(buff));
}

void read_all(Lexer *lexer) {
    int chr;
    StringBuff *buff = new_sbuff(2);
    Token* token;
    while ((chr = read_chr(lexer)) != END) {
        if (is_new_line(chr)) {
            lexer->col_pos = 1;
            lexer->row_pos++;
        }
        clear_buff(buff);
        if ((token = select_token(lexer, chr, buff))->kind == EMPTY)continue;
        list_add(lexer->tokens, token);
    }
    free(buff->body);
    free(buff);
}

/**
 * 填充 list
 * @param lexer  --
 * @param index  --
 * @return 成功 true  否则 false
 */
t_bool fill_list(Lexer *lexer, int index) {
    if (index >= lexer->tokens->size) {
        if (lexer->also) {
            read_all(lexer);
        } else {
            return t_false;
        }
    }
    return t_true;
}

Lexer *new_lexer(char *file) {
    struct lexer *lexer = malloc(sizeof(struct lexer));
    if ((lexer->file = fopen(file, "r")) == NULL) {
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


Token *lexer_read(Lexer *lexer) {
    Token *token;
    if ((token = lexer_peek(lexer, 0))->kind != END) {
        return list_remove(lexer->tokens, 0);
    }
    return token;
}

Token *lexer_peek(Lexer *lexer, int index) {
    if (fill_list(lexer, index)) {
        Token *token = list_get(lexer->tokens, index);
        if (token == NULL)return new_end_token();
        return token;
    }
    return new_end_token();
}
