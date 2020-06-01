
#include "nethelp.h"

void * HandleClient(void * arg) 
{  
    int n;
    char buf[MAXLINE];

    int connfd = (int)arg;
    pthread_detach(pthread_self()); 

    while((n = read(connfd, buf, MAXLINE)) > 0) { 
        printf("server received %d bytes\n", n); 
        write(connfd, buf, n); 
    } 
    close(connfd);
    return NULL;
}

int main(int argc, char *argv[]) {
    int listenfd, connfd, port, clientlen, tid;
    struct sockaddr clientaddr;

    port = atoi(argv[1]); /* the server listens on a port passed 
                             on the command line */
    listenfd = open_listenfd(port); 

    clientlen = sizeof(clientaddr);
    while (1) {
        connfd = accept(listenfd, &clientaddr, &clientlen);
        pthread_create(&tid, NULL, HandleClient, (void*)connfd);
    }
}



