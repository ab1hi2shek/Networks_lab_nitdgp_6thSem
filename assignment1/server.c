
#include <stdio.h>
#include <sys/types.h>
//header file to be included for networking in C
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
  int sockfd, newsockfd;
  int clilen;

  struct sockaddr_in cli_addr, serv_addr;
  int i;
  char buf[100];

//connection end point
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("cannot create socket\n");
    exit(0);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(6001);

  //associating server with its port
  if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) <0){
    printf("Unable to bind socket\n");
    exit(0);
  }

  listen(sockfd,5); //% concurrent client can be queued up

  while(1){
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

    if(newsockfd < 0){
      printf("Accept Error\n");
      exit(0);
    }
    // for(i=0;i<100;i++) //reseting the buffer to get client message
    //   buf[i] = '\0';

     strcpy(buf, "Message from server");
    send(newsockfd, buf, strlen(buf) + 1, 0); //send the message to the client

    for(i=0;i<100;i++) //reseting the buffer to get client message
      buf[i] = '\0';
    recv(newsockfd, buf, 100, 0); //recieving the message from client
    printf("%s\n", buf);

    close(newsockfd);

  }

  return 0;

}
