#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdlib.h>

#ifndef SOCKET_H
#define SOCKET_H
#define PORT 8080
#define BUFFER_SIZE 1024
#define LOCAL_HOST "127.0.0.1"

static inline void clearbuf(char* buff)
{
    for(int i = 0; i < BUFFER_SIZE; i++ )
    {
        buff[i] = 0;
    }
}

#endif