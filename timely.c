#include "parser.h"

int main(int argc, char **argv) {
    Lexer* lexer = new_lexer(argv[1]);
    struct parser* parser = new_parser(lexer);
    parse(parser);
    return 0;
}
