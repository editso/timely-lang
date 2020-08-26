//
// Created by zy on 8/8/20.
//
#include "include/basic.h"
#include "include/log.h"
#include "include/tio.h"
#include "include/tstring.h"
#include "string.h"

KindMeta get_kind_meta(Kind kind) {
    CharBuff *buff = new_buff(2);
    if (kind != NEWLINE && kind >= 0 && kind <= 127) {
        KindMeta *meta = malloc(sizeof(KindMeta));
        append_chr(buff, (char) kind);
        meta->kind = kind;
        meta->name = to_string(buff);
        recycle_buff(buff);
        return *meta;
    } else {
        for (int i = 0; i < kind_count; ++i) {
            if (kind_table[i].kind == kind) {
                return kind_table[i];
            }
        }
    }
    return EMPTY_KIND;
}

unsigned int  log_level_ = LOG_LEVEL_DEBUG;


void print_error(char *label, char *line, char *pos, char *fmt, va_list arg) {
    fprintf(stdout, "%s:%s:", line, pos);
    fprintf(stdout, "%s:", label);
    vprintf(fmt, arg);
    fprintf(stdout, "\n");
}



char *token_pos(Token *token) {
    CharBuff *buff = new_buff(4);
    append_chr(buff, '(');
    append_str(buff, itochr((int) token->row_pos));
    append_chr(buff, ',');
    append_str(buff, itochr((int) token->col_pos));
    append_chr(buff, ')');
    append_chr(buff, '\0');
    char *s = to_string(buff);
    free(buff->body);
    free(buff);
    return s;
}

void lexer_error(const char *m, const char *s, unsigned int row, unsigned int col) {
    size_t len = strlen(s);
    char buff[col + 2];
    memset(buff, '\0', col + 2);
    memset(buff, '\n', 1);
    memset(buff + 1, ' ', col);
    memset(buff + col, '^', 1);
    char n_buff[col];
    if (col > len) {
        memset(n_buff, ' ', col - len + 1);
    }
    fprintf(stderr, "%s:(%d, %d)\n", m, row, col);
    fprintf(stderr, "%s%s%s\n", n_buff, s, buff);
    exit(1);
}


void parser_error(char *m, char *s, Token *token) {
    lexer_error(m, s, token->row_pos, token->col_pos);
}




void out_token(Token *token) {
    char *s = token->text;
    if (token->kind == NEWLINE) {
        s = "<New Line>";
    }
    print("<Kind=%s<%d>, (%d,%d)>",
          s,
          token->kind,
          token->row_pos,
          token->col_pos);
}

void* require_not_null(void* any, char *message){
    if (any == NULL)
        log_error("%s",message);
    return any;
}

