//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_TREE_H
#define TIMELY_LANG_TREE_H

#include "token.h"
#include "list.h"
#include "envir.h"

typedef struct {
    void *(*eval)(Environment *env, void *node);
} Eval;

#define GET_EVAL(eval) ((Eval*)eval)

#define GET_FUN(fun) ((void *(*)(Environment *, void *))fun)


typedef struct modifier_{
    Eval eval;
    List* modifiers;
}Modifier;


typedef struct {
    Eval eval;
    List *stmts;
} Tree;

typedef struct stmt_{
    Eval eval;
    List* stmt;
}Stmt;

typedef struct {
    Eval eval;
    void *left;
    Token *op;
    void *right;
} BinaryExpr;


typedef struct {
    Eval eval;
    Token *op;
    void *expr;
} StartTerm;

typedef struct {
    Eval eval;
    Token *op;
    void *expr;
} EndTerm;

typedef struct type_{
    Eval eval;
    Token* name;
}Type;

typedef struct {
    Eval eval;
    Token *name;
    void *value;
    Type* type;
    Modifier* modifier;
} VarTerm;


typedef struct {
    Eval eval;
    Token *name;
} ConstantTerm;


/**
 * 函数调用
 */
typedef struct {
    Eval eval;
    void *expr;
    List *args;
} CallTerm;


typedef struct {
    Eval eval;
    List *stmts;
} BlockStmt;

typedef struct {
    Eval eval;
    Token *token;
} EmptyStmt;

typedef struct {
    Eval eval;
    void *expr;
    void *block;
} WhileStmt;

typedef struct if_{
    Eval* eval;
    // if(expr)
    void* expr;
    //  {}
    void* block;
    // else if(){}
    List* elseif;
    // else{}
    void* elsexpr;
}IFStmt;


typedef struct {
    Eval eval;
    Token *name;
    List *args;
    void *block;
    Modifier* modifier;
} FunStmt;



typedef struct {
    Eval eval;
    void *expr;
    void *block;
} CatchStmt;


typedef struct {
    Eval eval;

    /**
     * try{
     *
     * }
     */
    void *block;
    /**
     * try{
     *
     * }catch e{
     *
     * }catch e{
     *
     * }
     */
    List *stmts;
    /**
     * try{
     *
     * }catch e{
     *
     * }finally{
     *
     * }
     */
    void *stmt;
} TryStmt;


typedef struct {
    Eval eval;
    Token *name;
    List *extends;
    void *block;
    Modifier* modifier;
} ClassStmt;

typedef struct{
    Eval eval;
    void* name;
    void* expr;
}ArraySubscript;

typedef struct{
    Eval eval;
    void* object;
    void* expr;
}SelectMember;

typedef struct expr_{
    Eval eval;
    void* expr;
}Expr;

typedef struct switch_{
    Eval eval;
    void* expr;
    List* cases;
    void* defexpr;
}SwitchStmt;

typedef struct case_{
    Expr eval;
    void* expr;
    void* block;
}CaseStmt;

Tree *new_tree(List *list);

VarTerm *new_var_term(Token *name, void *expr, Type* type, Modifier* modifier);

ConstantTerm *new_constant_term(Token *name);

BinaryExpr *new_binary_expr(void *left, Token *op, void *right);

BlockStmt *new_block_stmt(List *stmts);

WhileStmt *new_while_stmt(void *expr, void *block);


StartTerm *new_start_term(Token *op, void *expr);

EndTerm *new_end_term(Token *op, void *expr);

EmptyStmt *new_empty(Token *op);

FunStmt *new_fun_stmt(Token *name, List *args, void *block, Modifier* modifier);

CallTerm *new_call_term(void *expr, List *args);

TryStmt *new_try_stmt(void *block, List *stmts, void *finally);

CatchStmt *new_catch_stmt(void *expr, void *block);

ClassStmt *new_class_stmt(Token *name, List *parent, void *block, Modifier* modifier);

Modifier* new_modifier(List* modifiers);
Type* new_type(Token* name);

Stmt* new_stmt(List* stmt);


ArraySubscript*  new_array_subscript(void* name, void* expr);

SelectMember* new_select_member( void* object, void* expr);

Expr* new_expr(void* expr);

IFStmt* new_if_stmt(void* expr, void* block, List* elseif, void*  elsexpr);

SwitchStmt* new_switch_stmt(void* expr, List* cases, void* defexpr);
CaseStmt* new_case_stmt(void* expr, void* block);
#endif //TIMELY_LANG_TREE_H
