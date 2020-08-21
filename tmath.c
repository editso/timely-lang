//
// Created by zy on 2020/8/21.
//
#include "include/basic.h"
#include "include/tstring.h"
#include "include/list.h"
#include "include/tmath.h"
#include <string.h>

int max(int a, int b){
    return a>=b?a:b;
}

int min(int a, int b){
    return a<=b?a:b;
}

char *big_add(char *a, char *b) {
    unsigned long alen = strlen(a);
    unsigned long blen = strlen(b);
    List *al = new_list();
    List *bl = new_list();
    unsigned int max = alen >= blen ? alen : blen;
    char *ma = alen >= blen ? a : b;
    unsigned int min = blen <= alen ? blen : alen;
    char *mb = blen <= alen ? b : a;
    for (int i = 0; i < max; ++i) {
        list_add(al, GET_CHAR(ma[i]));
    }
    for (int i = 0; i < min; ++i) {
        list_add(bl, GET_CHAR(mb[i]));
    }
    int ia,ib,x;
    for (int i = (int) al->size - 1, j = (int) bl->size - 1; j >= 0; --i, --j) {
        ia = (int) *(char *) list_get(al, i) - '0';
        ib = (int) *(char *) list_get(bl, j) - '0';
        x = i;
        while (ia + ib > 9) {
            *(char *) list_get(al, x) = (char) (((ia + ib) % 10) + '0');
            if (--x < 0)break;
            ib = (ia + ib) / 10;
            ia = (int) *(char *) list_get(al, x) - '0';
        }
        // 进位
        if (x < 0) {
            list_insert(al, 0, GET_CHAR((ia + ib) / 10 + '0'));
        } else {
            *(char *) list_get(al, x) = (char) (ia + ib + '0');
        }
    }
    CharBuff* buff = new_buff(al->size);
    for (int i = 0; i < al->size; ++i) {
        append_str(buff,list_get(al, i));
    }
    char* num = to_string(buff);
    recycle_buff(buff);
    return num;
}

