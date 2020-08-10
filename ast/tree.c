//
// Created by zy on 8/9/20.
//
#include "eval.h"
#include "../basic.h"


void* binary_eval(Environment* env, BinaryExpr* expr){
    GET_EVAL(expr->left)->eval(env, expr->left);
    GET_EVAL(expr->right)->eval(env,expr->right);
    return NULL;
}

void* while_eval(Environment* env, WhileStmt* stmt){
    return NULL;
}
void* var_eval(Environment* env, VarTerm* term){
    return NULL;
}
void* constraint_eval(Environment* env, ConstantTerm* term){
    return NULL;
}
void* block_eval(Environment* env, BlockStmt* stmt){
    return NULL;
}

void* start_eval(Environment* env, StartTerm * stmt){
    return NULL;
}
void* end_eval(Environment* env, EndTerm * stmt){
    return NULL;
}

void* call_eval(Environment* env, CallTerm* term){
    return NULL;
}

Eval* new_eval(void* (*eval_call)(Environment* env, void* node)){
    Eval* eval = malloc(sizeof(Eval));
    eval->eval = eval_call;
    return eval;
}


Tree* new_tree(struct list* list){
    Tree* tree = malloc(sizeof(Tree));
    tree->stmts = list;
    return tree;
}

VarTerm* new_var_term(Token* name, void* expr){
    VarTerm* var = malloc(sizeof(VarTerm));
    var->eval = new_eval(GET_FUN(var_eval));
    var->name = name;
    var->value = expr;
    return var;
}

ConstantTerm* new_constant_term(Token* name){
    ConstantTerm* constraint = malloc(sizeof(ConstantTerm));
    constraint->name = name;
    constraint->eval = new_eval(GET_FUN(constraint_eval));
    return constraint;
}

BinaryExpr* new_binary_expr(void* left,Token* op, void* right){
    BinaryExpr* binary = malloc(sizeof(BinaryExpr));
    binary->left = left;
    binary->op = op;
    binary->right = right;
    binary->eval = new_eval(GET_FUN(binary_eval));
    return binary;
}

BlockStmt* new_block_stmt(struct list* stmts){
    BlockStmt* block = malloc(sizeof(BlockStmt));
    block->stmts = stmts;
    block->eval = new_eval(GET_FUN(block_eval));
    return block;
}

WhileStmt* new_while_stmt(Token* name, void* expr, BlockStmt* block){
    WhileStmt* t_while = malloc(sizeof(WhileStmt));
    t_while ->name = name;
    t_while->expr =expr;
    t_while->block=block;
    t_while->eval=new_eval(GET_FUN(while_eval));
    return t_while;
}

StartTerm* new_start_term(Token* op, void* expr){
    StartTerm* term = malloc(sizeof(StartTerm));
    term->eval = new_eval(GET_FUN(start_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

EndTerm* new_end_term(Token* op, void* expr){
    EndTerm* term = malloc(sizeof(EndTerm));
    term->eval= new_eval(GET_FUN(end_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

CallTerm* new_call_term(void* expr, struct list* args){
    CallTerm *term = malloc(sizeof(CallTerm));
    term->expr = expr;
    term->eval = new_eval(GET_FUN(call_eval));
    term->args = args;
    return term;
}