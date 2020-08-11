#include "parser.h"
#include "setjmp.h"
#include "signal.h"
#include "errno.h"
#include "map.h"

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
//        struct parser* parser = new_parser(lexer);
//        parse(parser);
//        runner(parser);

        Map* map = new_map(10);
        map_put(map, "data","hello");
        map_put(map, 1,"2");
        map_put(map, 2,"1");
        map_put(map, lexer,"lexer");
        print("size: %d",map->size);
        print("data: %s",map_get(map, "data"));
        print("1: %s",map_get(map, 1));
        print("2: %s",map_get(map, 2));
        print("lexer: %s",map_get(map, lexer));

    }catch(4){
        print("遇到错误,程序结束:%d", errno);
    }
    return 0;
}
