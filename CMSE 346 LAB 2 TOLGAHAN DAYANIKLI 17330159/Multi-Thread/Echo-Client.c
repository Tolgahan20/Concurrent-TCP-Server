/*
 * echoclient.c - An echo client
 */

#include "nethelp.h"
#include <time.h>
#include <assert.h>

int main(int argc, char **argv) 
{
    int clientfd, port;
    char *host, buf[MAXLINE];
    int n;

    if (argc != 3) {
	fprintf(stderr, "USAGE: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);

    clientfd = open_clientfd(host, port);

    while (fgets(buf, MAXLINE, stdin) != NULL) {
	write(clientfd, buf, strlen(buf));
	n = readline(clientfd, buf, MAXLINE);
	write(1, buf, n);
	 
	 time_t t = time(NULL);
    	struct tm *tm = localtime(&t);
    	char s[64];
    	assert(strftime(s, sizeof(s), "%c", tm));
    	printf("%s","CURRENT DATE & TIME:");
    	printf("%s\n", s);
    }
    close(clientfd);
    exit(0);
}





