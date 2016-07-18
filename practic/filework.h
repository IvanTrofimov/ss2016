#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif
#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif
#ifndef DIRENT_H
#include <dirent.h>
#define DIRENT_H
#endif
#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif


 #ifndef FILEWORK_H
 #define FILEWORK_H

struct for_in
{
	FILE *list;
	char f_name[20], m_name[20], l_name[20], group[10], github[50], git_folder[20];
};
int GetGit(struct for_in *str1); 
void GroupDir(char group[10], char path[30]);
 
 #endif
