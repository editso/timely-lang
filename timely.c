#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parser.h"



int main(int argc, char **argv) {
    int fd = open(argv[1],O_RDONLY);
    printf("%s", argv[1]);
    if (fd == -1){
        perror("timely");
        exit(0);
    }
    parse(argv[1]);
    return 0;
}
