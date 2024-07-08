#include <stdio.h>
#include <string.h>
#include "Server.h"
#include <unistd.h>

void launch(struct Server *server)
{
    char buffer[30000];
    char *hello = "HTTP/1.1 200 OK\nDate: Mon, 08 Jul 2024 17:10:20 GMT+3\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Sun 07 Jul 2024 19:15:30 GMT+3\nContent-Length: 88\nContent-Type: text/html\nConnection: Closed\n\n<html><body><h1>Hello, World!</h1></body></html>";
    int address_length = sizeof(server->address);
    int new_socket;
    
    while (1)
    {
        
        printf("===== WAITING FOR CONNECTION =====");
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        read(new_socket, buffer, 30000);
        printf("%s\n", buffer);
        write(new_socket, hello, strlen(hello));
        close(new_socket)
    }
}

int main()
{
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
    server.launch(&server);
}