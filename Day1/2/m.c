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
int ss;
char str[500],str1[500],sss[50];
char des[30][50];
int a[50];
int ff,fff;
if (pipe(f)<0){
	printf("not create" );
	exit(1);
}
pid = fork();
if (pid == -1) {
	printf("Some error happened\n");
}
else if(pid == 0) {
	printf("child process%d\n",getpid() );
	close(f[0]);
	dup2(f[1], 1);
	dup2(f[1], 2);
	close(f[1]);
	execlp("ls", "ls", "-l","/tmp/", NULL);
	exit(10);
	}
	else {
		int stat;
		close(f[1]);
		wait(&stat);
		printf("parrent process %d\n", getpid());
		ss = read(f[0],str,sizeof(str));
		str[ss] = '\0';
		printf("%s\n",str );
		strcpy(str1,str);
		char *f = str1;
		char *q = des[0];
		char *b = strchr(str1,':');
		int i = 0;
		while(b != NULL){
			char *c = strchr(b,' ');
			b = strchr(c,'\n');
			if ( b == NULL)
			{
				b = strchr(c,'\0');
			}
			int dif = b+1-(c);
			memcpy(q,c,dif);
			des[i][dif]='\0';
			a[i]=strlen(des[i]);
			b = strchr(c,':');
			i++;
			q = des[i];
		}
		int nn = i;
		printf("Отсортированный список(хотя после 'ls -l' он уже отсортирован, сортировка на случай если не будет отсортирован)\n");
		int max = 300;
		int max1 = 0;
		int j=0;
		char *tmp = sss;
		i = 1;
		while(i<nn){
      	    while(j <= nn - i - 1){
           		if(strcmp(des[j],des[j+1])>0) {
              		strcpy(tmp,des[j]);
              		strcpy(des[j],des[j+1]);
              		strcpy(des[j+1],tmp);
           		}
           		j++;
        	}
        	i++;
    	}
    	i=0;
    	while ( i<nn)
    	{
       		printf("%s\n", des[i]);
       	i++;
       }
	}
return 0;
}