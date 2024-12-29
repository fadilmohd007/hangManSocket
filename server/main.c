#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"
#include "hangMan.h"

int main(int argc, char *argv)
{
    //  SOCKET
    int server_fd , new_socket, ret, opt = 1;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = { 0 };
    ssize_t valread;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0)
    {
        printf("socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    ret = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR ,&opt, sizeof(opt));
    if(ret < 0)
    {
        printf("socket option setting failed\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    ret = bind(server_fd, (struct sockaddr*) &address, sizeof(address));
    if(ret < 0)
    {
        printf("socket binfing failed\n");
        exit(EXIT_FAILURE);
    }

    ret = listen(server_fd,3);
    if(ret < 0)
    {
        printf("socket listening failed\n");
        exit(EXIT_FAILURE);
    }
    initHangMan();
    getwelcomeNote(buffer);

    printf("waiting for client to join\n");
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket < 0) {
        printf("scocket accept error");
        exit(EXIT_FAILURE);
    }
    printf("Client joined\n");
    send(new_socket, buffer, strlen(buffer), 0);
    clearbuf(buffer);
    int x = 10;
    valread = read(new_socket, buffer, BUFFER_SIZE - 1);
    while(strlen(buffer) > 0)
    {
        char inputChar;
        strncpy(&inputChar,buffer, 1);
        clearbuf(buffer);
        ret = playGame(&inputChar,buffer);
        printf("ret %d\n",ret);
        if(ret <= 0)
        {
            send(new_socket,buffer,strlen(buffer),0); 
            printf("Game over exiting server\n");
            close(server_fd);
            close(new_socket);
            exit(EXIT_SUCCESS);
        }
        send(new_socket,buffer,strlen(buffer),0);        
        valread = read(new_socket, buffer, BUFFER_SIZE - 1);

       
        

    }
    close(server_fd); 
}
