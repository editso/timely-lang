//
// Created by zy on 8/7/20.
//
#include "include/lexer.h"
#include "include/list.h"
#include "include/basic.h"
#include "include/tstring.h"
#include "include/ttypes.h"

uint read_chr(struct lexer *lexer) {
    if (lexer->file == NULL) return END;
    uint chr;
    if (lexer->last_chr != EMPTY) {
        chr = lexer->last_chr;
        lexer->last_chr = EMPTY;
        return chr;
    }
    if ((chr = fgetc(lexer->file)) == EOF) {
        fclose(lexer->file); // 关流
        lexer->file = NULL;
        return END;
    }
    lexer->col_pos++;
    return chr;
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

Token *new_token(Lexer *lexer, int kind, char *s) {
    Token *token = new(Token);
    token->col_pos = lexer->col_pos - 1 - strlen(s);
    token->row_pos = lexer->row_pos;
    token->kind = kind;
    token->text = s;
    return token;
}

Token *new_end_token() {
    Token *token = malloc(sizeof(Token));
    token->kind = END;
    return token;
}

char *read_letter(Lexer *lexer, CharBuff* buff) {
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

char *read_digit(Lexer *lexer, CharBuff* buff) {
    uint chr;
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

char *read_string(Lexer *lexer, CharBuff* buff) {
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
char *read_multi_note(Lexer *lexer, CharBuff* buff) {
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
            lexer->col_pos = 1;
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
char *read_single_note(Lexer *lexer, CharBuff* buff) {
    uint chr;
    while ((chr = read_chr(lexer))) {
        if (is_new_line(chr) || chr == END) {
            lexer->row_pos++;
            lexer->col_pos = 1;
            break;
        }
        if (chr > 127)continue;
        append_chr(buff, (char) chr);
    }
    return to_string(buff);
}

/**
 * 运算符
 */
Token *read_operator(Lexer* lexer, CharBuff* buff){
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
    return new_token(lexer, EMPTY, to_string(buff));
}

Token* generate_token(Lexer* lexer, int chr, CharBuff* buff){
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
    CharBuff *buff = new_buff(10);
    int chr;
    Token* token;
    while ((chr = read_chr(lexer)) != END) {
        if (is_new_line(chr)) {
            lexer->col_pos = 1;
            lexer->row_pos++;
        }
        clear_buff(buff);
        if ((token = generate_token(lexer, chr, buff))->kind == EMPTY)continue;
        list_add(lexer->tokens, token);
    }
    recycle_buff(buff);
}

/**
 * 填充 list
 * @param lexer  --
 * @param index  --
 * @return 成功 true  否则 false
 */
t_bool fill_list(Lexer *lexer, int index) {
    if (index >= lexer->tokens->size) {
        if (lexer->file == NULL)return t_false;
        read_all(lexer);
    }
    return t_true;
}

Lexer *new_lexer(char *file) {
    Lexer *lexer = new(Lexer);
    if ((lexer->file = fopen(file, "rb+")) == NULL) {
        perror("timely");
        exit(0);
    }
    lexer->source = file;
    lexer->tokens = new_list();
    lexer->last_chr = EMPTY;
    lexer->row_pos = 1;
    lexer->col_pos = 1;
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
