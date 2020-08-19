//
// Created by zy on 8/8/20.
//
#include "include/basic.h"
#include "include/log.h"
#include "string.h"


KindMeta get_kind_meta(Kind kind) {
    StringBuff *buff = new_sbuff(2);
    if (kind != NEWLINE && kind >= 0 && kind <= 127) {
        KindMeta *meta = malloc(sizeof(KindMeta));
        append_chr(buff, (char) kind);
        meta->kind = kind;
        meta->name = to_string(buff);
        free(buff->body);
        free(buff);
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

void log_code(char *file, int row, int col, char *message, ...) {
    va_list args;
    va_start(args,message);
    StringBuff *buff = new_sbuff(100);
    append_str(buff, file);
    append_str(buff, ":");
    append_str(buff, itochr(row));
    append_chr(buff, ':');
    append_str(buff, itochr(col));
    append_chr(buff, ':');
    append_str(buff,TAG_ERROR);
    append_str(buff, message);
    log_log(LOG_LEVEL_ERROR, stderr, to_string(buff), args);
    va_end(args);
    recycle_buff(buff);
    exit(1);
}


char *get_token_pos(Token *token) {
    StringBuff *buff = new_sbuff(4);
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

void lexer_error(char *m, char *s, unsigned int row, unsigned int col) {
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


void print(char *s, ...) {
    va_list args;
    va_start(args, s);
    vprintf(s,args);
    printf("\n");
    va_end(args);
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

void log_log(unsigned int l, FILE *file, char* message, va_list list){
    if (is_level(l)){
        vfprintf(file, message, list);
        fprintf(file,"\n");
    }
}


void log_error(char* message, ...){
    va_list list;
    va_start(list,message);
    StringBuff* buff = new_sbuff(1024);
    append_str(buff, TAG_ERROR);
    append_str(buff, message);
    log_log(LOG_LEVEL_ERROR, stderr,to_string(buff), list);
    va_end(list);
    recycle_buff(buff);
    exit(1);
}


void log_warning(char* message, ...){
    va_list list;
    va_start(list,message);
    StringBuff* buff = new_sbuff(1024);
    append_str(buff, TAG_WARNING);
    append_str(buff, message);
    log_log(LOG_LEVEL_WARNING, stdout, to_string(buff), list);
    va_end(list);
    recycle_buff(buff);
}

void log_info(char* message, ...){
    va_list list;
    va_start(list,message);
    StringBuff* buff = new_sbuff(1024);
    append_str(buff, TAG_INFO);
    append_str(buff, message);
    log_log(LOG_LEVEL_INFO, stdout, to_string(buff), list);
    va_end(list);
    recycle_buff(buff);
}

void log_debug(char *message, ...){
    va_list list;
    va_start(list,message);
    StringBuff* buff = new_sbuff(1024);
    append_str(buff, TAG_DEBUG);
    append_str(buff, message);
    log_log(LOG_LEVEL_DEBUG, stdout, to_string(buff), list);
    va_end(list);
    recycle_buff(buff);
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

char *itochr(int i) {
    int num = abs(i);
    if (num == 0) return "0";
    StringBuff *buff = new_sbuff(10);
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
