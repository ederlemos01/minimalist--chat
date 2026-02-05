#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include  <pthread.h>

void *receive(void *socketptr){
 
  int socket = *(int*)socketptr;
  char buffer[4024];
  int tam;

  while (1) {
  
  memset(buffer, 0, 4024);
  tam = recv((int)socket, buffer, 4024, 0);
  
  if (tam >= 1)
    buffer[tam - 1] = '\0';
  
  if(tam == 0)
        exit(0);

  printf("\nclient: %s\n", buffer); 
  fflush(stdout);
  }
  return NULL;
}
int main (){

  int serverFD = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in endereco;
  endereco.sin_family = AF_INET;
  endereco.sin_port = htons(2007);
  endereco.sin_addr.s_addr = INADDR_ANY;

  int result = bind(serverFD,(const struct sockaddr *) &endereco, sizeof(endereco));
  
  if ( result == 0)
    printf("server on\n");

  int listenResult = listen(serverFD, 10);
  int clientFD = accept(serverFD,0, 0 );

  pthread_t thread1;

  pthread_create(&thread1, NULL,receive, (void*)&clientFD);

  char response[4024];
  while (1){
  
  fgets(response, 4024, stdin);
  send(clientFD, response, strlen(response), 0 );
  
  
  }

  close(serverFD);
  return 0;
  
} 
