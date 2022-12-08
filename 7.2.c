#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

struct thread_arg{
	char* name;
	char* str;
	int num;
};

void* any_func(void* args){
	struct thread_arg* targ = (struct thread_arg*) args;
		for(int j = 0; j < targ->num; j++){
			fprintf(stdout,"name = %s %d, ", targ->name, targ->num);
			fprintf(stdout,"str = %s %d, ", targ->str, targ->num);
			fprintf(stdout,"num = %d.\n", targ->num);
		}
	return NULL;
}

int main(void){
	pthread_t thread1, thread2, thread3, thread4;
	int result;
	struct thread_arg targ[4];
	for(int i = 0;i<4;i++){
		targ[i].name = "Thread";
		targ[i].str = "str";
		targ[i].num = i;
	}
	if(pthread_create(&thread1,NULL,&any_func,&targ[0]) != 0){
		fprintf(stderr, "Error (thread)\n");
		return 1;
	}
	if(pthread_create(&thread2,NULL,&any_func,&targ[1]) != 0){
                fprintf(stderr, "Error (thread)\n");
                return 1;
        }
	if(pthread_create(&thread3,NULL,&any_func,&targ[2]) != 0){
                fprintf(stderr, "Error (thread)\n");
                return 1;
        }
	if(pthread_create(&thread4,NULL,&any_func,&targ[3]) != 0){
                fprintf(stderr, "Error (thread)\n");
                return 1;
        }

	while(1);
	return 0;
}