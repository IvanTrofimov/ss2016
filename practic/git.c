#include<pthread.h>
#include"git.h"

int str_len(char* str){
	int i=0;
	while ((str[i]!='\0')&&(str[i]!='\n')){
		i++;
	}
	return i;
}
char* directory_name(char* gitname,char*directory){
	char* dirname;
	int i=0,j;
	while(gitname[i]!='\0')
		i++;
	while(gitname[i-1]!='/')
		i--;
	dirname=malloc(sizeof(char)*(str_len(&gitname[i])+str_len(directory)+2));
	for(j=0;j<str_len(&gitname[i]);j++){
		dirname[j]=gitname[j+i];
		dirname[j+1]='\0';
	}
	if(str_len(directory)!=0){
		i=str_len(&gitname[i]);
		dirname[i]='/';
		i++;
		for(j=0;j<str_len(directory);j++){
			dirname[i+j]=directory[j];
		}
	}
	return dirname;
}
char* bash_comand(char flag,char* argname){
	char* comand;
	int i;
	switch (flag){
	case('g'):
		comand=malloc(sizeof(char)*(10+str_len(argname)));
		strcpy(comand,"git clone ");
		for(i=0;i<str_len(argname);i++){
			comand[10+i]=argname[i];
		}
		break;
	case('c'):
		comand=malloc(sizeof(char)*(4+str_len(argname)));
		strcpy(comand,"cd ");
		for(i=0;i<str_len(argname);i++){
			comand[3+i]=argname[i];
		}
		break;
	case('m'):
		comand=malloc(sizeof(char)*(18+str_len(argname)));
		strcpy(comand,"make -f ");
		for(i=0;i<str_len(argname);i++){
			comand[8+i]=argname[i];
			comand[9+i]='\0';
		}
		comand=strncat(comand,"/Makefile",9);
		break;
	}
	return comand;
}

int load_git(char* gitname,int time){
	pid_t pid=fork();
	int cd;
	if(pid<0){
		printf("fork error\n");
		return 1;
	}
	else if(pid==0){
		execl("/usr/bin/git","git","clone",gitname,NULL);
	}
	else{
		sleep(time);
		kill(pid,SIGINT);
		cd=kill(pid+1,SIGINT);
		if (cd==-1) return 0;
		else return 1;
	}
}
void print_make_result(FILE* fp,char* gitname,int time,char* directory){
	int cd;
	char* dirname;
	char* comand;
	cd=load_git(gitname,time);
	if(cd)fprintf(fp," git not found");
	else fprintf(fp," git successfully loaded");
	dirname=directory_name(gitname,directory);
	comand=bash_comand('m',dirname);
	cd=system(comand);
	if (cd)
		fprintf(fp,"; makefile ERROR. Error N%d\n",cd);
	else
		fprintf(fp,"; makefile is working properly\n");
	str_free(dirname);
	str_free(comand);
}
void str_free(char* str){
	int i;
	for(i=0;i<str_len(str);i++) str[i]='\0';
	free(str);
}
int str_to_int(char* str){
	int i=0,value=0;
	while (str[i]!='\0'){
		value+=(int)str[i]-48;
		i++;
		value*=10;
	}
	value/=10;
	return value;
}
