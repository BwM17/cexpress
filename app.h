#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

typedef struct App
{
    short Port;
    char *IP;
    void (*run)(struct App *);
} App;

App *new_App(short Port, char *IP);
void run(App *self);
void delete_App(App *app);

#endif