#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int count=1,Num_Threads;
int* ready_threads;
void* func(void * arg){
	int ID=*(int*)arg,i;
	count+=1;
	sleep(count);
	printf("thread %d ready\n",ID);
	ready_threads[ID]=-1;
	pthread_mutex_lock(&mut);
	if(all_ready()){
		pthread_cond_broadcast(&cond);
	}
	else{
		pthread_cond_wait(&cond,&mut);
	}
	pthread_mutex_unlock(&mut);
	printf("thread %d finish\n",ID);
}
int all_ready(){
	int i;
	for(i=0;i<Num_Threads;i++){
		if(ready_threads[i]!=-1)
			return 0;
	}
	return 1;
}
int main(){
	int i,rc;
	pthread_t* threads;
	printf("enter number of thread\n");
	scanf("%d",&Num_Threads);
	ready_threads=malloc(sizeof(int)*Num_Threads);
	threads=malloc(sizeof(pthread_t)*Num_Threads);
	for(i=0;i<Num_Threads;i++){
		ready_threads[i]=i;
		rc = pthread_create(&threads[i], NULL, func, &ready_threads[i]);
 		if (rc) {
 			printf("ERROR\n");
			exit(-1);
 		}
	}
	for(i = 0; i < Num_Threads; i++) {
		pthread_join(threads[i], NULL);
 	}
	free(threads);
	free(ready_threads);
	return 0;
}
