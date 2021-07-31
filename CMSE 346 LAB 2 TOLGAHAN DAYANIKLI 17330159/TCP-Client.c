#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <assert.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/

int
main(int argc, char **argv)
{
 int sockfd;
 struct sockaddr_in servaddr;
 char sendline[MAXLINE], recvline[MAXLINE];

 //basic check of the arguments
 //additional checks can be inserted
 if (argc !=2) {
  perror("USAGE: TCP Client <IP ADDRESS OF THE SERVER");
  exit(1);
 }

 //Create a socket for the client
 //If sockfd<0 there was an error in the creation of the socket
 if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  perror("PROBLEM DETECTED IN SOCKET CREATION");
  exit(2);
 }

 //Creation of the socket
 memset(&servaddr, 0, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr= inet_addr(argv[1]);
 servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order

 //Connection of the client to the socket
 if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
  perror("PROBLEM IN CONNECTIONG TO THE SERVER");
  exit(3);
 }

 while (fgets(sendline, MAXLINE, stdin) != NULL) {
 
 send(sockfd, sendline, strlen(sendline), 0);

  
  if (recv(sockfd, recvline, MAXLINE,0) == 0){
   //error: server terminated prematurely
   perror("THE SERVER TERMINATED");
   exit(4);
  }
  printf("%s", "STRING RECIEVED FROM THE SERVER: \n");
   
  fputs(recvline, stdout);
  
  time_t t = time(NULL);
    	struct tm *tm = localtime(&t);
    	char s[64];
    	assert(strftime(s, sizeof(s), "%c", tm));
    	printf("%s","CURRENT DATE & TIME:");
    	printf("%s\n", s);
  	
  
 }

 exit(0);
}
