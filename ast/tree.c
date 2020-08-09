//
// Created by zy on 8/9/20.
//
#include "eval.h"


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
void* constraint_eval(Environment* env, ConstraintTerm* term){
    return NULL;
}
void* block_eval(Environment* env, BlockStmt* stmt){
    return NULL;
}


Eval* new_eval(void* (*eval_call)(Environment* env, void* node)){
    Eval* eval = malloc(sizeof(Eval));
    eval->eval = eval_call;
    return eval;
}


VarTerm* new_var_term(Token* name, void* expr){
    VarTerm* var = malloc(sizeof(VarTerm));
    var->name = name;
    var->value = expr;
    var->eval = new_eval(GET_FUN(var_eval));
    return var;
}

ConstraintTerm* new_constraintTerm(Token* name){
    ConstraintTerm* constraint = malloc(sizeof(ConstraintTerm));
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
