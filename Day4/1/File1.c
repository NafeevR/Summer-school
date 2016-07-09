#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "bin_sem.h"
#define BUF	 10000000
int main(){
char *ap;
char *s;
s = (char*) malloc(BUF*sizeof(char));
key_t key = ftok("File1.c", 1);
int id = shmget(key,BUF,IPC_CREAT | 0666);
int semid = binary_semaphore_allocation(key, 0666 | IPC_CREAT);
FILE *d; 
if ((d = fopen("100mb_file.txt","r"))==0 ){
	printf("Error\n");
	exit(11);
}
printf("Good\n" );
while(fread(s, sizeof(char), BUF, d)==BUF){
	printf("FIRST_ZAPUSK: Try take the sem to copy from FILE to MEMORY\n");
	binary_semaphore_take(semid);
	ap = (char *) shmat(id,0,0);
	sprintf(ap,s);
	shmdt(ap);
	binary_semaphore_free(semid);
	printf("FIRST_ZAPUSK: and release\n");
}
binary_semaphore_deallocate(semid);
printf("pr1: proc1 release the semaphore\n");
free(s);
exit(0);
}