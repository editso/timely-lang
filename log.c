//
// Created by zy on 2020/8/21.
//
#include "include/log.h"
#include "include/tstring.h"
#include <stdlib.h>

void log_log(unsigned int l, FILE *file, const char* message, va_list list){
    if (is_level(l)){
        vfprintf(file, message, list);
        fprintf(file,"\n");
    }
}

void log_error(const char* message, ...){
    va_list list;
    va_start(list,message);
    CharBuff* buff = new_buff(1024);
    append_str(buff, TAG_ERROR);
    append_str(buff, message);
    log_log(LOG_LEVEL_ERROR, stderr,to_string(buff), list);
    va_end(list);
    recycle_buff(buff);
    exit(1);
}


void log_warning(const char* message, ...){
    va_list list;
    va_start(list,message);
    CharBuff* buff = new_buff(1024);
    append_str(buff, TAG_WARNING);
    append_str(buff, message);
    log_log(LOG_LEVEL_WARNING, stdout, to_string(buff), list);
    va_end(list);
    recycle_buff(buff);
}

void log_info(const char* message, ...){
    va_list list;
    va_start(list,message);
    CharBuff* buff = new_buff(1024);
    append_str(buff, TAG_INFO);
    append_str(buff, message);
    log_log(LOG_LEVEL_INFO, stdout, to_string(buff), list);
    va_end(list);
    recycle_buff(buff);
}

void log_debug(const char *message, ...){
    va_list list;
    va_start(list,message);
    CharBuff* buff = new_buff(1024);
    append_str(buff, TAG_DEBUG);
    append_str(buff, message);
    log_log(LOG_LEVEL_DEBUG, stdout, to_string(buff), list);
    va_end(list);
    recycle_buff(buff);
}

void log_code(char *file, int row, int col, const char *message, ...) {
    va_list args;
    va_start(args,message);
    CharBuff *buff = new_buff(100);
    append_str(buff, file);
    append_str(buff, ":");
    append_str(buff, itochr(row));
    append_chr(buff, ':');
    append_str(buff, itochr(col));
    append_chr(buff, ':');
    append_str(buff, TAG_ERROR);
    append_str(buff, message);
    log_log(LOG_LEVEL_ERROR, stderr, to_string(buff), args);
    va_end(args);
    recycle_buff(buff);
    exit(1);
}
