#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

struct rand_arg{
	int ot;
	int to;
	int count;
	int zadanoe_chislo;
};

void* rand_func(void* args){
	srand(time(NULL));
	int rand_num = 0;
	struct rand_arg* targ = (struct rand_arg*)args;
	for(int i = 0; i < targ->count; i++){
		rand_num = rand() % (targ->to) - (targ->ot);
		fprintf(stdout, "rand number: %d\n", rand_num);
		if(rand_num == targ->zadanoe_chislo){
			fprintf(stderr, "End function, chislo polucheno!!!\n");
			pthread_exit(NULL);
		}
		sleep(1);
	}
	return NULL;
}

void* any_func(void* arg){
	int size = *(int*)arg;
	for(int i = 0;i<size;i++){
		fprintf(stdout, "Child Thread. Iteration: %d\n", i);
		sleep(1);
	}
	return NULL;
}

int main(void){
	pthread_t thread1, thread2;
	struct rand_arg targ;
	int count = 10;

	targ.ot = 0;
	targ.to = 20;
	targ.count = 10;
	targ.zadanoe_chislo = 15;

	if(pthread_create(&thread1,NULL,&any_func,&count) != 0){
		fprintf(stderr, "error thred\n");
		return 1;
	}

	if(pthread_create(&thread2,NULL,&rand_func,&targ) != 0){
		fprintf(stderr, "error thred\n");
		return 1;
	}

	if(pthread_join(thread1, NULL) != 0){
		fprintf(stderr, "Join error thread 1\n");
		return 1;
	}

	if(pthread_join(thread2, NULL) != 0){
		fprintf(stderr, "Join error thread 2\n");
		return 1;
	}

	fprintf(stderr, "\nMain thread finish working!!!\n");
	while(1);
	return 0;
}