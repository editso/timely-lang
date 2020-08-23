//
// Created by zy on 8/9/20.
//
#include "include/eval.h"
#include "include/tio.h"
#include "include/basic.h"

void *binary_eval(Environment *env, BinaryExpr *expr) {

    GET_EVAL(expr->left)->eval(env, expr->left);
    GET_EVAL(expr->right)->eval(env, expr->right);

    return NULL;
}

void *while_eval(Environment *env, WhileStmt *stmt) {
    print("while循环: %s", __FUNCTION__);
//    while (GET_EVAL(stmt->expr)->eval(env, stmt->expr)){
//        GET_EVAL(stmt->block)->eval(env, stmt->block);
//    }
    return NULL;
}

void *var_eval(Environment *env, VarTerm *term) {
    print("变量声明: %s", __FUNCTION__);
//    void* value = GET_EVAL(term->value)->eval(env,term);
//    map_put(&env->map, term->name->text, value);
    return NULL;
}

void *constant_eval(Environment *env, ConstantTerm *term) {

    switch (term->name->kind) {
        case NUMBER:
            return "number";
        case CONST_STRING:
            return "hello world";
        case ID:
            return term->name->text;
        default:
            return NULL;
    }
    return NULL;
}

void *block_eval(Environment *env, BlockStmt *stmt) {

    List *comm = stmt->stmts;
    void *node;
    for (int i = 0; i < comm->size; ++i) {
        node = list_get(stmt->stmts, i);
        if (node == NULL)continue;
        GET_EVAL(node)->eval(env, node);
    }
    return NULL;
}

void *start_eval(Environment *env, StartTerm *stmt) {

    return NULL;
}

void *end_eval(Environment *env, EndTerm *stmt) {

    return NULL;
}


void *call_eval(Environment *env, CallTerm *term) {

    ConstantTerm *constant = term->expr;
    List *args = term->args;
    char buff[1024];
    return NULL;
}

void *fun_eval(Environment *env, FunStmt *fun) {

    return NULL;
}

void *tree_eval(Environment *env, Tree *eval) {
//    print("call: %s", __FUNCTION__ );
    List *stmts = eval->stmts;
    void *node;
    for (int i = 0; i < stmts->size; ++i) {
        node = list_get(stmts, i);
        GET_EVAL(node)->eval(env, node);
    }
    return NULL;
}

void *try_eval(Environment *env, TryStmt *stmt) {

    return NULL;
}

void *catch_eval(Environment *env, CatchStmt *stmt) {

    return NULL;
}

void *empty_eval(Environment *env, EmptyStmt *term) {
    return NULL;
}

Eval *new_eval(void *(*eval_call)(Environment *env, void *node)) {
    Eval *eval = new(Eval);
    eval->eval = eval_call;
    return eval;
}

void *class_eval(Environment *env, ClassStmt *stmt) {

    return NULL;
}

Tree *new_tree(List *list) {
    Tree *tree = new(Tree);
    tree->stmts = list;
    tree->eval = *new_eval(GET_FUN(tree_eval));
    return tree;
}

VarTerm *new_var_term(Token *name, void *expr, Type* type, Modifier* modifier) {
    VarTerm *var = new(VarTerm);
    var->eval = *new_eval(GET_FUN(var_eval));
    var->name = name;
    var->value = expr;
    var->modifier = modifier;
    var->type = type;
    return var;
}

ConstantTerm *new_constant_term(Token *name) {
    ConstantTerm *constraint = new(ConstantTerm);
    constraint->name = name;
    constraint->eval = *new_eval(GET_FUN(constant_eval));
    return constraint;
}

BinaryExpr *new_binary_expr(void *left, Token *op, void *right) {
    BinaryExpr *binary = new(BinaryExpr);
    binary->left = left;
    binary->op = op;
    binary->right = right;
    binary->eval = *new_eval(GET_FUN(binary_eval));
    return binary;
}

BlockStmt *new_block_stmt(List *stmts) {
    BlockStmt *block = new(BlockStmt);
    block->stmts = stmts;
    block->eval = *new_eval(GET_FUN(block_eval));
    return block;
}

WhileStmt *new_while_stmt(void *expr, void *block) {
    WhileStmt *t_while = new(WhileStmt);
    t_while->expr = expr;
    t_while->block = block;
    t_while->eval = *new_eval(GET_FUN(while_eval));
    return t_while;
}

StartTerm *new_start_term(Token *op, void *expr) {
    StartTerm *term = new(StartTerm);
    term->eval = *new_eval(GET_FUN(start_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

EndTerm *new_end_term(Token *op, void *expr) {
    EndTerm *term = new(EndTerm);
    term->eval = *new_eval(GET_FUN(end_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

CallTerm *new_call_term(void *expr, List *args) {
    CallTerm *term = new(CallTerm);
    term->expr = expr;
    term->eval = *new_eval(GET_FUN(call_eval));
    term->args = args;
    return term;
}

EmptyStmt *new_empty(Token *op) {
    EmptyStmt *empty = new(EmptyStmt);
    empty->token = op;
    empty->eval = *new_eval(GET_FUN(empty_eval));
    return empty;
}

FunStmt *new_fun_stmt(Token *name, List *args, void *block, Modifier* modifier) {
    FunStmt *fun = new(FunStmt);
    fun->eval = *new_eval(GET_FUN(fun_eval));
    fun->name = name;
    fun->args = args;
    fun->block = block;
    fun->modifier = modifier;
    return fun;
}

TryStmt *new_try_stmt(void *block, List *stmts, void *finally) {
    TryStmt *stmt = new(TryStmt);
    stmt->eval = *new_eval(GET_FUN(try_eval));
    stmt->block = block;
    stmt->stmts = stmts;
    stmt->stmt = finally;
    return stmt;
}

CatchStmt *new_catch_stmt(void *expr, void *block) {
    CatchStmt *stmt = new(CatchStmt);
    stmt->eval = *new_eval(GET_FUN(catch_eval));
    stmt->expr = expr;
    stmt->block = block;
    return stmt;
}

ClassStmt *new_class_stmt(Token *name, List *extends, void *block, Modifier* modifier) {
    ClassStmt *stmt = new(ClassStmt);
    stmt->eval = *new_eval(GET_FUN(class_eval));
    stmt->name = name;
    stmt->extends = extends;
    stmt->block = block;
    stmt->modifier = modifier;
    return stmt;
}

Modifier* new_modifier(List* modifiers){
    Modifier* modifier = new(Modifier);
    modifier->modifiers = modifiers;
    return modifier;
}

Stmt* new_stmt(List* stmt){
    Stmt* stmts = new(Stmt);
    stmts->stmt = stmt;
    return stmts;
}

Type* new_type(Token* name){
    Type* type = new(Type);
    type->name = name;
    return type;
}

ArraySubscript*  new_array_subscript(void* name, void* expr){
    ArraySubscript* arraySubscript  = new(ArraySubscript);
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

IFStmt* new_if_stmt(void* expr, void* block, List* elseif, void*  elsexpr){
    IFStmt* stmt = new(IFStmt);
    stmt->expr = expr;
    stmt->block = block;
    stmt->elsexpr = elsexpr;
    stmt->elseif = elseif;
    return stmt;
}

SwitchStmt* new_switch_stmt(void* expr, List* cases, void* defexpr){
    SwitchStmt* stmt = new(SwitchStmt);
    stmt->expr = expr;
    stmt->cases = cases;
    stmt->defexpr = defexpr;
    return stmt;
}

CaseStmt* new_case_stmt(void* expr, void* block){
    CaseStmt* stmt = new(CaseStmt);
    stmt->block = block;
    stmt->expr = expr;
    return stmt;
}