#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

 void *receive(void *socketptr){

  int socket = *(int*)socketptr;
  int tam;
  char buffer[4024];

  while (1) {
  
  memset(buffer, 0, 4024);
  tam = recv((int)socket, buffer, 4024, 0);
  if (tam >= 1)
   buffer[tam - 1] = '\0';
  
  if(tam == 0)
      exit(0);

  printf("\nServer: %s\n", buffer); 
  fflush(stdout);
  }

  return NULL;

}
int main(){

  int socketFD = socket(AF_INET,SOCK_STREAM, 0);
  
  char* ip = "127.0.0.1";
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(2007);
  inet_pton(AF_INET,  ip, &address.sin_addr);
  

  int result = connect(socketFD,(const struct sockaddr *) &address, sizeof(address));
  
  if (result == 0)
    printf("connection on\n");
  else {
    printf("error: can't find the server\n");
    return 0;
    }

  pthread_t thread1;
  pthread_create(&thread1, NULL,receive, (void*)&socketFD);

  char msg[4024];
  
  while (1) {
  
  memset(msg, 0, 4024);
  fgets(msg, 4024, stdin);
  send(socketFD, msg , strlen(msg), 0);
  
  if (strcmp(msg, "q\n") == 0) 
    break;
  
  }
  close(socketFD);
  
  return 0;

}



