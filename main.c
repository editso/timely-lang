#include "include/parser.h"
#include <setjmp.h>
#include <signal.h>
#include <errno.h>

jmp_buf buf;

void handler(int sig) {
    errno = 0;
    errno = 4;
    throw(buf, sig);
}

int main(int argc, char **argv) {
    level = LOG_LEVEL_DEBUG;
    signal(SIGSEGV, handler);
    signal(SIGABRT, handler);
    signal(SIGFPE, handler);
    try(buf) {
        Lexer *lexer = new_lexer(argv[1]);
        Parser *parser = new_parser(lexer);
        tree_node(parse(parser))->eval(NULL, parser->tree);
    } catch(4) {
        log_error("遇到错误!!");
    }
    return 0;
}
