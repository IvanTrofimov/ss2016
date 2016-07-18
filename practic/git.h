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
typedef struct process_input{
	int* flag;
	int time;
	pid_t pid;
}arg_t;
int str_len(char* str);
char* Directoryname(char* gitname,char*Directory);
char* bash_comand(char flag,char* argname);
void* load_control(void* arg);
int load_git(char* gitname,int time);
void print_make_result(FILE* fp,char* gitname,int time,char* Directory);
int str_to_int(char* str);
#endif
