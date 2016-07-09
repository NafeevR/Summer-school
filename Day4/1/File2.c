#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "bin_sem.h"
#define BUF	10000000
int main(){
key_t key = ftok("File1.c", 1);
char *ap;
int id = shmget(key,BUF,IPC_CREAT | 0666);
int semid = binary_semaphore_allocation(key, 0666 | IPC_CREAT);
FILE *d; 
if ((d = fopen("test.txt","wt"))==0 ){
	printf("Error\n");
	exit(11);
}
int i=0;
binary_semaphore_initialize(semid);
if (semid > 0) {
	while(i<10){
		printf("SECOND_ZAPUSK: Try take the sem to copy from MEMORY to FILE \n");
		binary_semaphore_take(semid);
		ap = (char *) shmat(id,0,0);
		fwrite(ap, sizeof(char), BUF, d);
		binary_semaphore_free(semid);
		printf("SECOND: And released....\n");
		shmdt(ap);
		usleep(10);
		i=i+1;
	}
}
 if (shmdt(ap) == -1) {

  fprintf(stderr, "shmdt failed\n");

  exit(1);

 }

 if (shmctl(id, IPC_RMID, 0) == -1) {

  fprintf(stderr, "shmctl(IPC_RMID) failed\n");

  exit(1);

 }
binary_semaphore_deallocate(semid);
exit(0);
}
