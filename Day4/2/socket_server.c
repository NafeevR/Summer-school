#include <sys/types.h>

#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4

int server_sockfd, client_sockfd;
	struct sockaddr_un client_address;
int server_len, client_len;
void *potok(void*k) {
		client_len = sizeof(client_address);
	 client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
	 long t_id;
	 char ch;
	 t_id = (long) pthread_self();
	 printf("potok %ld\n",t_id );
	 read(client_sockfd, &ch, 1);
	 ch++;
	 long tt = (long)k;
	// sleep(tt);
	 write(client_sockfd, &ch, 1);
	 close(client_sockfd);
	 pthread_exit(NULL);
}
int main() {
 pthread_t threads[NUM_THREADS];
 int rc;
long t = 0;
 struct sockaddr_un server_address;
 unlink("server_socket");
 server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
 server_address.sun_family = AF_UNIX;
 strcpy(server_address.sun_path, "server_socket");
 server_len = sizeof(server_address);
 bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
 listen(server_sockfd, 5);
 while(t<5)
 {
 	printf("server waiting\n");
	rc = pthread_create(&threads[t], NULL, potok, (void *)t);
	t++;
}
 while(1)
 {
 	
}

}