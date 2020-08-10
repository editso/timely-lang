#include "parser.h"
#include "ast/eval.h"
#include "setjmp.h"
#include "signal.h"
#include "string.h"
#include "errno.h"

jmp_buf buf;

void handler(int sig){
    errno=0;
    errno = 4;
    throw(buf,sig);
}

int main(int argc, char **argv) {
    signal(SIGSEGV,  handler);
    try(buf){
        Lexer* lexer = new_lexer(argv[1]);
        struct parser* parser = new_parser(lexer);
        parse(parser);
        runner(parser);
    }catch(4 || 1==1){
        perror("error");
        printf("断错误,程序结束:%d", errno);
    }
    return 0;
}
