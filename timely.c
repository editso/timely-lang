#include "include/parser.h"
#include <setjmp.h>
#include <signal.h>
#include <errno.h>
#include "string.h"
#include "include/tmath.h"

jmp_buf buf;

void handler(int sig) {
    errno = 0;
    errno = 4;
    throw(buf, sig);
}

int main(int argc, char **argv) {
    signal(SIGSEGV, handler);
    signal(SIGABRT, handler);
    signal(SIGFPE, handler);
    level = LOG_LEVEL_ERROR;
    try(buf) {
        Lexer *lexer = new_lexer(argv[1]);
        Parser *parser = new_parser(lexer);
        GET_EVAL(parse(parser))->eval(NULL, parser->tree);
    } catch(4) {
        log_error("遇到错误!!");
    }
    return 0;
}
