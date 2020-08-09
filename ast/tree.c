//
// Created by zy on 8/9/20.
//
#include "tree.h"

VarTerm* new_var_term(Token* name, void* expr){
    VarTerm* var = malloc(sizeof(VarTerm));
    var->name = name;
    var->value = expr;
    return var;
}

ConstraintTerm* new_constraintTerm(Token* name){
    ConstraintTerm* constraint = malloc(sizeof(ConstraintTerm));
    constraint->name = name;
    return constraint;
}

BinaryExpr* new_binary_expr(void* left,Token* op, void* right){
    BinaryExpr* binary = malloc(sizeof(BinaryExpr));
    binary->left = left;
    binary->op = op;
    binary->right = right;
    return binary;
}

BlockStmt* new_block_stmt(struct list* stmts){
    BlockStmt* block = malloc(sizeof(BlockStmt));
    block->stmts = stmts;
    return block;
}

WhileStmt* new_while_stmt(Token* name, void* expr, BlockStmt* block){
    WhileStmt* t_while = malloc(sizeof(WhileStmt));
    t_while ->name = name;
    t_while->expr =expr;
    t_while->block=block;
    return t_while;
}
