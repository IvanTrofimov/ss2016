#include<pthread.h>
#include"git.h"

int str_len(char* str){
	int i=0;
	while ((str[i]!='\0')&&(str[i]!='\n')){
		i++;
	}
	return i;
}
char* Directoryname(char* gitname,char*Directory){
	char* Dirname;
	int i=0,j;
	while(gitname[i]!='\0')
		i++;
	while(gitname[i-1]!='/')
		i--;
	Dirname=malloc(sizeof(char)*(str_len(&gitname[i])+str_len(Directory+1)));
	for(j=0;j<str_len(&gitname[i]);j++){
		Dirname[j]=gitname[j+i];
	}
	Dirname=strncat(Dirname,"/",1);
	Dirname=strncat(Dirname,Directory,str_len(Directory));
	return Dirname;
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
		}
		comand=strncat(comand,"/Makefile",9);
		break;
	}
	return comand;
}
void* load_control(void* arg){
	arg_t* input=arg;
	sleep(input->time);
	if(*input->flag!=0){
		printf("KILL\n");
		kill(input->pid+1, SIGINT);
		kill(input->pid, SIGINT);
	}
}
int load_git(char* gitname,int time){
	int i,cd=1;
	char* comand;
	arg_t arg;
	arg.time=time;
	arg.flag=&cd;
	pthread_t control_proces;
	comand=bash_comand('g',gitname);
	pthread_create(&control_proces,NULL,load_control,&arg);
	arg.pid=getpid()+3;
	cd=system(comand);
	pthread_join(control_proces,NULL);
	if(cd)
		return 1;
	else
		return 0;
	free(comand);
}
void print_make_result(FILE* fp,char* gitname,int time,char* Directory){
	int cd;
	char* Dirname;
	char* comand;
	cd=load_git(gitname,time);
	if (cd){
		fprintf(fp,":Git clone ERROR\n");
		exit(-1);
	}
	Dirname=Directoryname(gitname,Directory);
	comand=bash_comand('m',Dirname);
	cd=system(comand);
	free(Dirname);
	if (cd)
		fprintf(fp,":makefile ERROR. Error N%d\n",cd);
	else
		fprintf(fp,":makefile is working properly\n");
	free(comand);
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
