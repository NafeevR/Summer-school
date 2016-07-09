#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#define N 3 // количество рабочих потоков

typedef struct dat{
    int id;
    char m[10];
    int num;
    int disp;
}dat;

void *iter(void *fdat1){
    int count = 0;
    int i;
    dat *fdat= (dat*)fdat1;
    printf("Name : %s|  id of stream: %d  |cycle number: %d  | counter: %d\n\n", fdat->m, fdat->id, 0, 0);
    for (i=0; i<fdat->num; i++){
        count += fdat->disp;
        printf("Name : %s|id of stream: %d|cycle number: %d| counter: %d\n\n", fdat->m, fdat->id, i+1, count);
    }
}
int main(){
    pthread_t mas[N];
    dat dat[N];
    long status;
    srand(time(0));
    char buf[3] = "";
    char name[10] = "name";
    long i;
    for (i=0; i<N; i++){
        dat[i].id = i;
        dat[i].num = rand()%(20);
        dat[i].disp = rand()%1000;
        sprintf(name, "st%d", rand()%100);
        strcpy(dat[i].m, name);
        printf("\nid =%d, numcycl = %d, disp=%d, name = %s\n\n",dat[i].id,dat[i].num, dat[i].disp, dat[i].m);
        status = pthread_create(&mas[i], NULL, iter, (void*)&dat[i]);
        if (status != 0) {
            printf("Main error: can't create thread, status = %d\n", status);
            exit(-1);
        }
    }

    for (i=0; i<N; i++){
    status = pthread_join(mas[i], NULL);
    if (status != 0) {
    printf("Main error: can't join thread, status = %d\n", status);
    exit(-2);
    }
    }
}
