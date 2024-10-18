#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "app.h"

#define BACKLOG 50

/*@todo
  - split into several files
  - request header
  - request pipeline
  - response handler
*/

void run(App *self)
{
  printf("Port:\t%d\nIP:\t%s\n", self->Port, self->IP);
  int serverSocket;
  int clientSocket;
  int optval;
  struct sockaddr_in serverSocket_addr;
  struct sockaddr_in clientSocket_addr;

  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  optval = 1;
  if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  serverSocket_addr.sin_family = AF_INET;
  serverSocket_addr.sin_port = htons(self->Port);
  serverSocket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(serverSocket, (struct sockaddr *)&serverSocket_addr, sizeof(serverSocket_addr)) < 0)
  {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  printf("[LISTEN] on %s:%d\n", self->IP, self->Port);
  if (listen(serverSocket, BACKLOG) == -1)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  int clientSocket_addr_len = sizeof(clientSocket_addr);
  clientSocket = accept(serverSocket, (struct sockaddr *)&clientSocket_addr, &clientSocket_addr_len);
  if (clientSocket < 0)
  {
    close(serverSocket);
    perror("accept");
    exit(EXIT_FAILURE);
  }

  char http_request[4096];
  size_t http_request_len = sizeof(http_request);

  if (recv(clientSocket, &http_request, http_request_len, 0) < 0)
  {
    close(serverSocket);
    close(clientSocket);
    perror("[recv]");
    exit(EXIT_FAILURE);
  }
  printf("%s\n", http_request);

  char response[] = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/json\r\n"
                    "\r\n"
                    "\"msg\": \"Hello, World!\"";

  if (send(clientSocket, response, sizeof(response), 0) < 0)
  {
    perror("[send]");
    exit(EXIT_FAILURE);
  }
  printf("sending data\n");
  close(clientSocket);
  close(serverSocket);
  printf("Server Closed\n");
}

App *new_App(short Port, char *IP)
{
  App *res = (App *)malloc(sizeof(App));
  if (res == NULL)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  res->Port = Port;
  res->IP = IP;
  res->run = &run;
  return res;
}

void delete_App(App *app)
{
  free(app);
  printf("App has been destructed\n");
}
