#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdlib.h>

#define THREADS 5
typedef struct t_struct{
	int ID,i,dcount;
	char name[11];
}thread_struct;
void *func(void* arg){
	thread_struct* farg=arg;
	int count=0,i;
	for(i=0;i<farg->i;i++){
		printf("NAME:%s  ID:%d  I:%d  COUNT:%d\n",farg->name,farg->ID,i,count);
		count+=farg->dcount;
		usleep(1);	
	}
}
void random_name(char name[11]){
	int i;
	for(i=0;i<10;i++){
		name[i]=(char)(rand()%25+65);
	}
	name[10]='\0';
}
void generate_arg(thread_struct* arg,int ID){
	arg->ID=ID;
	arg->i=rand()%20;
	arg->dcount=rand()%10-10;
	random_name(arg->name);
}
int main()
{
	pthread_t threads[THREADS];
	thread_struct arg[THREADS];
	int rc,i;
	for(i=0;i<THREADS;i++){
		generate_arg(&arg[i],i);
		rc = pthread_create(&threads[i], NULL, func, &arg[i]);
 		if (rc) {
 			printf("ERROR\n");
			 exit(-1);
 		}
	}
	for(i = 0; i < THREADS; i++) {
		pthread_join(threads[i], NULL);
 	}
	return 0;
}
