#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#pragma comment(lib, "ws2_32.lib")
// When compiling, use this command: gcc server.c -o server.exe -lws2_32

#define PORT 1234
#define BUFLEN 100

int main()
{
    WSADATA wsa; // this is struct that has the information about the Windows Socket implementations

    WSAStartup(MAKEWORD(2,2), &wsa); // WSAStartup functions allows us to specify which version of windows socket api to use.
    // MAKEWORD is a function macro that concatenates two bytes to create a single 2 byte value - version 2.2 here

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // creating a socket is like creating a door frame that is not yet attached to anything
    // AF - address family
    // AF_INET - means the ipv4 address; AF_INET6 - ipv6
    // socket(address type, type, protocol)
    // type - TCP or UDP. SOCK_STREAM - TCP; SOCK_DGRAM - UDP
    // 0 means to use the default protocol

    struct sockaddr_in addr = {.sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr = ADDR_ANY}; 
    //any address means from any ip address including anythin from localhost, wifi or ethernet

    bind(sock, (struct sockaddr*)&addr, sizeof(addr)); // assigns the socket to the port and the address

    listen(sock, 1); // 1 means, the number of pending connections that has to be in the queue for the listening socket

    printf("Server on the port %d\n", PORT);

    SOCKET client = accept(sock, NULL, NULL); // getting the client socket
    // we are passing the argument as NULL because, we do not need to know the address for now (as the client is also in localhost)

    char *msg = malloc(BUFLEN); // pointer for the message

    while(1)
    {

        int len = recv(client, msg, BUFLEN - 1, 0); // here if the message from the recv is 0, this means the connection is closed

        if(len <= 0)
        {
            printf("Client disconnected or error: %s\n", WSAGetLastError());
        }

        msg[len] = '\0';

        printf("Got the message: %s\n", msg);

        char* reply = "Got it!";

        send(client, reply, strlen(reply), 0);
    }
    // clean up
    free(msg);
    closesocket(sock);
    closesocket(client);
    WSACleanup();
    return 0;

    // here, why is there no loop?

}