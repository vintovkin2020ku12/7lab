#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

unsigned long int fact(int n){
	if(n == 0 || n == 1)
		return 1;
	unsigned long int f = 1;
	for(int i = 1; i<=n;i++){
		f = f * i;
	}
	return f;
}

int* simple_num(int n){
	int count = 0;
	int divis = 0;
	int capacity = 0;
	int* simpl=(int*)malloc(sizeof(int) * n);
	while(capacity != n){
		divis = 0;
		for(int i = count;i>0;i--){
			if((count % i) == 0){
				divis++;
			}
		}
		if(divis == 2){
			simpl[capacity] = count;
			capacity++;
		}
	count++;
	}
	return simpl;
}

void* katalana_number(void* arg){
	int size = *(int*)arg;
	unsigned long int buff[size];
	for(int i = 0;i<size;i++){
		buff[i] = fact(2 * i) / (fact(i + 1)*fact(i));
	}
	for(int i = 0;i<size;i++){
		fprintf(stdout,"katalina number num[%d] = %d\n", i, buff[i]);
		sleep(1);
	}
	return NULL;
}

void* simple_number(void* arg){
	int size = *(int*)arg;
	int* buff;
	int capacity;
	buff = simple_num(size);
	for(int i = 0;i<size;i++){
		fprintf(stdout,"simple number num[%d] = %d\n", i, buff[i]);
		sleep(1);
	}
	return NULL;
}

int main(void){
	pthread_t thread1, thread2;
	int count = 10;

	if(pthread_create(&thread1,NULL,&katalana_number,&count) != 0){
		fprintf(stderr, "error thred\n");
		return 1;
	}

	if(pthread_create(&thread2,NULL,&simple_number,&count) != 0){
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
	fprintf(stderr, "\nMain thread finish working!!! \n");
	while(1);
	return 0;
}