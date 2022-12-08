#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void* any_func(void* args){
	for(int i = 0;i<5;i++){
		fprintf(stdout, "Child Thread. Iteration: %d\n", i);
		sleep(1);
	}
	return NULL;
}

int main(void){
	pthread_t thread;
	int result;

	result = pthread_create(&thread,NULL,&any_func,NULL);

	if(result != 0){
		fprintf(stderr, "Error\n");
		return 1;
	}
	for(int i = 0;i<5;i++){
		fprintf(stdout,"Main Thread. Iteration: %d\n", i);
		sleep(1);
	}
	while(1);
	return 0;
}