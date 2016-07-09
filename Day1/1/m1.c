#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main() {
pid_t pid;
int f[2];
size_t size;
char str[6];
char s[6];
if (pipe(f)<0){
	printf("not create" );
	exit(1);
}
pid = fork();
if (pid == -1) {
	printf("Some error happened\n");
}
else if(pid == 0) {
	close(f[0]);
	while(strlen(s)!=6)
	{
		printf("child process %d\n", getpid());
		printf(" Введите строку из 6 символов\n");
		scanf("%s",s);
		if (strlen(s) == 6){
			size = write(f[1],&s,sizeof(s));
			if(size != 6){
				printf("Can't write all string\n"); 
				exit(-1); 
			}
		}
	}
	exit(10);
	}
	else {
		int stat;
		close(f[1]);
		wait(&stat);
		printf("parrent process %d\n", getpid());
		read(f[0],str,sizeof(str));
		printf("%s\n",str );
	}
return 0;
}