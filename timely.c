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
    signal(SIGSEGV, handler);
    signal(SIGABRT, handler);
    signal(SIGFPE, handler);
    try(buf) {
        Lexer *lexer = new_lexer(argv[1]);
        Parser *parser = new_parser(lexer);
//        GET_EVAL(parse(parser))->eval(NULL, parser->root);
        Map* map = new_map(2);
        for (int i = 0; i < 10; ++i) {
            map_put(map, i, i);
        }
    } catch(4) {
        print("遇到错误,程序结束:%d", errno);
    }
    return 0;
}
