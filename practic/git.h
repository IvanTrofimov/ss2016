#ifndef STDIO_H
#define STDIO_H
#include<stdio.h>
#endif
#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif
#ifndef STRING_H
#define STRING_H
#include<string.h>
#endif
#ifndef SYS_TYPES_H
#define SYS_TYPES_H
#include<sys/types.h>
#endif
#ifndef PTHREAD_H
#define PTHREAD_H
#include<pthread.h>
#endif
#ifndef SIGNAL_H
#define SIGNAL_H
#include<signal.h>
#endif

#ifndef GIT_H
#define GIT_H

int str_len(char* str);
char* directoryname(char* gitname,char*directory);
char* bash_comand(char flag,char* argname);
int load_git(char* gitname,int time);
void print_make_result(FILE* fp,char* gitname,int time,char* directory);
int str_to_int(char* str);
#endif
