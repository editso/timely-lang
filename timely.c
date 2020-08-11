#include "include/parser.h"
#include "setjmp.h"
#include "signal.h"
#include "errno.h"
#include "include/map.h"

jmp_buf buf;

void handler(int sig){
    errno=0;
    errno = 4;
    throw(buf,sig);
}

int main(int argc, char **argv) {
    signal(SIGSEGV,  handler);
    signal(SIGABRT,  handler);
    signal(SIGFPE,  handler);
    try(buf){
        Lexer* lexer = new_lexer(argv[1]);
        struct parser* parser = new_parser(lexer);
        parse(parser);
        runner(parser, NULL);


    }catch(4){
        print("遇到错误,程序结束:%d", errno);
    }
    return 0;
}
