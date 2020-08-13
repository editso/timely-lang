//
// Created by zy on 8/8/20.
//
#include "../include/basic.h"
#include "../include/log.h"
#include "string.h"


KindMeta get_kind_meta(Kind kind){
    if (kind != NEWLINE && kind >= 0 && kind <= 127){
        KindMeta* meta = malloc(sizeof(KindMeta));
        char* s = malloc(sizeof(s));
        *s = (char)kind;
        meta->kind = kind;
        meta->name = s;
        return *meta;
    }else{
        for (int i = 0; i < kind_count; ++i) {
            if (kind_table[i].kind == kind){
                return kind_table[i];
            }
        }
    }
    return EMPTY_KIND;
}


void print_error(char* label, char* line, char* pos, char* fmt, va_list arg){
    fprintf(stdout,"%s:%s:",line, pos);
    fprintf(stdout, "%s:", label);
    vprintf(fmt,arg);
    fprintf(stdout,"\n");
}


void log_error(char* file, unsigned int line, unsigned int pos, char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    StringBuff* buff = new_sbuff(10);
    append_str(buff,file);
    append_str(buff,":");
    append_str(buff, itochr((int)line));
    print_error("ERROR", to_string(buff), itochr((int)pos), fmt, args);
    va_end(args);
    free(buff->body);
    free(buff);
    exit(1);
}


char* get_token_pos(Token* token){
    return "(pos)";
}


void lexer_error(char *m, char *s, unsigned int row, unsigned int col){
    size_t len = strlen(s);
    char buff[col + 2];
    memset(buff, '\0', col+2);
    memset(buff,'\n',1);
    memset(buff+1,' ', col);
    memset(buff+col, '^',  1);
    char n_buff[col];
    if (col > len){
        memset(n_buff, ' ', col - len + 1);
    }
    fprintf(stderr,"%s:(%d, %d)\n", m,row,col);
    fprintf(stderr,"%s%s%s\n",n_buff,s,buff);
    abort();
}


void parser_error(char *m,char *s, Token* token){
    lexer_error(m, s, token->row_pos, token->col_pos);
}


void print(char *s, ...){
    va_list args;
    va_list args1;
    va_start(args, s);
    va_copy(args1, args);
    char buf[1 + vsnprintf(NULL, 0, s, args)];
    va_end(args);
    vsnprintf(buf, sizeof(buf), s, args1);
    va_end(args1);
    printf("%s\n", buf);
}

void out_token(Token* token){
    char *s = token->text;
    if (token->kind == NEWLINE){
        s = "<New Line>";
    }
    print("<Kind=%s<%d>, (%d,%d)>",
          s,
          token->kind,
          token->row_pos,
          token->col_pos);
}


char *reverse(char* s){
    unsigned long len = strlen(s);
    char chr;
    for (unsigned int i = len - 1, j = 0;  j < i; --i, j++) {
        chr = s[j];
        s[j] = s[i];
        s[i] = chr;
    }
    return s;
}

char* itochr(int i){
    int num = abs(i);
    if (num == 0) return "0";
    StringBuff* buff = new_sbuff(10);
    int n;
    while (num > 0){
        n = num % 10;
        append_chr(buff, (char)(n + '0'));
        num /= 10;
    }
    if (i < 0){
        append_chr(buff, '-');
    }
    char* value = to_string(buff);
    free(buff->body);
    free(buff);
    return reverse(value);
}
