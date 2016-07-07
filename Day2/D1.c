#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREADS 5
typedef struct t_struct{
	int ID,i,dcount;
	char name[10];
}thread_struct;
void func(void *arg){
	int count=0,i;
	arg=(thread_struct*)arg;
	for(i=0;i<arg->i;i++){
		printf("%s %d %d count=%d",arg->name,arg->ID,i,count);
		count++;	
	}
}

int main()
{

    return 0;
}
