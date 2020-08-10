//
// Created by zy on 8/8/20.
//
#include "basic.h"
#include "log.h"
#include "string.h"

KindMeta get_kind_meta(Kind kind){
    if (kind >= 0 && kind <= 127){
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
    print("<Kind=%s, (%d,%d)>",
          token->text,
          token->row_pos,
          token->col_pos);
}

long to_number(struct list *list){
    char *buf = malloc(sizeof(char) * list->size);
    // 11110
    for (int i = 0; i < list->size; ++i) {
        buf[i] = *(char*)list_get(list, i);
    }
    long *n=malloc(sizeof(long));
    memcpy(n, buf, list->size);
    return *n;
}
