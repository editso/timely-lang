#include "parser.h"
#include "basic.h"
#include "stdlib.h"
#include "errno.h"
#include "err.h"


void* binary_eval(Environment* env, BinaryExpr * node){
    out_token(node->op);
    return NULL;
}

int main(int argc, char **argv) {
    Lexer* lexer = new_lexer(argv[1]);
    struct parser* parser = new_parser(lexer);
    parse(parser);
    return 0;
}
