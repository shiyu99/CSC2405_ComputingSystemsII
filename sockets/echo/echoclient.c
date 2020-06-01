#include "nethelp.h" 

/* usage: ./echoclient host port */
int main(int argc, char *argv[])
{ 
    int clientfd, port, n; 
    char *host, buf[MAXLINE]; 
        
    host = argv[1]; 
    port = atoi(argv[2]); 
 
    clientfd = open_clientfd(host, port);

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        write(clientfd, buf, strlen(buf));
        n = read(clientfd, buf, MAXLINE);
        write(1, buf, n);
    }
    close(clientfd);
    exit(0);
} 
