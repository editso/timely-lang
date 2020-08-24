//
// Created by zy on 8/9/20.
//
#include "include/eval.h"
#include "include/basic.h"

Tree *new_tree(List *list) {
    Tree *tree = new(Tree);
    tree->stmts = list;
    tree->eval = *new_eval(eval_callback(tree_eval));
    return tree;
}

VarTerm *new_var_term(Token *name, void *expr, Type* type, Modifier* modifier) {
    VarTerm *var = new(VarTerm);
    var->eval = *new_eval(eval_callback(var_eval));
    var->name = name;
    var->value = expr;
    var->modifier = modifier;
    var->type = type;
    return var;
}

ConstantTerm *new_constant_term(Token *name) {
    ConstantTerm *constraint = new(ConstantTerm);
    constraint->name = name;
    constraint->eval = *new_eval(eval_callback(constant_eval));
    return constraint;
}

BinaryExpr *new_binary_expr(void *left, Token *op, void *right) {
    BinaryExpr *binary = new(BinaryExpr);
    binary->left = left;
    binary->op = op;
    binary->right = right;
    binary->eval = *new_eval(eval_callback(binary_eval));
    return binary;
}

BlockStmt *new_block_stmt(List *stmts) {
    BlockStmt *block = new(BlockStmt);
    block->stmts = stmts;
    block->eval = *new_eval(eval_callback(block_eval));
    return block;
}

WhileStmt *new_while_stmt(void *expr, void *block) {
    WhileStmt *t_while = new(WhileStmt);
    t_while->expr = expr;
    t_while->block = block;
    t_while->eval = *new_eval(eval_callback(while_eval));
    return t_while;
}

StartTerm *new_start_term(Token *op, void *expr) {
    StartTerm *term = new(StartTerm);
    term->eval = *new_eval(eval_callback(start_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

EndTerm *new_end_term(Token *op, void *expr) {
    EndTerm *term = new(EndTerm);
    term->eval = *new_eval(eval_callback(end_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

CallTerm *new_call_term(void *expr, List *args) {
    CallTerm *term = new(CallTerm);
    term->expr = expr;
    term->eval = *new_eval(eval_callback(call_eval));
    term->args = args;
    return term;
}

EmptyStmt *new_empty(Token *op) {
    EmptyStmt *empty = new(EmptyStmt);
    empty->token = op;
    empty->eval = *new_eval(eval_callback(empty_eval));
    return empty;
}

FunStmt *new_fun_stmt(Token *name, List *args, void *block, Modifier* modifier) {
    FunStmt *fun = new(FunStmt);
    fun->eval = *new_eval(eval_callback(fun_eval));
    fun->name = name;
    fun->args = args;
    fun->block = block;
    fun->modifier = modifier;
    return fun;
}

TryStmt *new_try_stmt(void *block, List *stmts, void *finally) {
    TryStmt *stmt = new(TryStmt);
    stmt->eval = *new_eval(eval_callback(try_eval));
    stmt->block = block;
    stmt->stmts = stmts;
    stmt->stmt = finally;
    return stmt;
}

CatchStmt *new_catch_stmt(void *expr, void *block) {
    CatchStmt *stmt = new(CatchStmt);
    stmt->eval = *new_eval(eval_callback(catch_eval));
    stmt->expr = expr;
    stmt->block = block;
    return stmt;
}

ClassStmt *new_class_stmt(Token *name, List *extends, BlockStmt *block, Modifier* modifier) {
    ClassStmt *stmt = new(ClassStmt);
    stmt->eval = *new_eval(eval_callback(class_eval));
    stmt->name = name;
    stmt->extends = extends;
    stmt->block = block;
    stmt->modifier = modifier;
    return stmt;
}

Modifier* new_modifier(List* modifiers){
    Modifier* modifier = new(Modifier);
    modifier->eval = *new_eval(eval_callback(modifier_eval));
    modifier->modifiers = modifiers;
    return modifier;
}

Stmt* new_stmt(List* stmt){
    Stmt* stmts = new(Stmt);
    stmts->stmt = stmt;
    stmts->eval = *new_eval(eval_callback(call_eval));
    return stmts;
}

Type* new_type(Token* name){
    Type* type = new(Type);
    type->eval = *new_eval(eval_callback(type_eval));
    type->name = name;
    return type;
}

ArraySubscript*  new_array_subscript(void* name, void* expr){
    ArraySubscript* arraySubscript  = new(ArraySubscript);
    arraySubscript->eval = *new_eval(eval_callback(subscript_eval));
    arraySubscript->name = name;
    arraySubscript->expr = expr;
    return arraySubscript;
}

Expr* new_expr(void* expr){
    Expr* expr_ = new(Expr);
    expr_->expr = expr;
    return expr_;
}


SelectMember* new_select_member( void* object, void* expr){
    SelectMember* member = new(SelectMember);
    member->expr = expr;
    member->object = object;
    return member;
}

IFStmt* new_if_stmt(void* expr, void* block, void*  elsexpr){
    IFStmt* stmt = new(IFStmt);
    stmt->eval = *new_eval(eval_callback(if_eval));
    stmt->expr = expr;
    stmt->block = block;
    stmt->elsexpr = elsexpr;
    return stmt;
}

ElseStmt* new_else_stmt(void *block){
    ElseStmt* stmt = new(ElseStmt);
    stmt->eval = *new_eval(eval_callback(else_eval));
    stmt->block = block;
    return stmt;
}

SwitchStmt* new_switch_stmt(void* expr, List* cases, void* defexpr){
    SwitchStmt* stmt = new(SwitchStmt);
    stmt->eval = *new_eval(eval_callback(switch_eval));
    stmt->expr = expr;
    stmt->cases = cases;
    stmt->defexpr = defexpr;
    return stmt;
}

CaseStmt* new_case_stmt(void* expr, void* block){
    CaseStmt* stmt = new(CaseStmt);
    stmt->eval =  *new_expr(eval_callback(case_eval));
    stmt->block = block;
    stmt->expr = expr;
    return stmt;
}