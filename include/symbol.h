//
// Created by zy on 2020/9/1.
//

#ifndef TIMELY_LANG_SYMBOL_H
#define TIMELY_LANG_SYMBOL_H

#include "token.h"

#include "tree.h"

typedef struct symbol_ {
    struct symbol_ *super;
} Symbol;


typedef struct variable_symbol_{
    Symbol symbol;
}VariableSymbol;

typedef struct operate_symbol_{
    Symbol symbol;
    Token op;
}OperateSymbol;



#endif //TIMELY_LANG_SYMBOL_H
