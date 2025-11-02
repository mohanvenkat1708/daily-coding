#include<stdio.h>
#include<winsock2.h>


#pragma comment(lib, "ws2_32.lib") //preprocessor directive that includes information to the compiler

#define PORT 1234
#define BUFLEN 100

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = { .sin_family=AF_INET, .sin_port=htons(PORT)};
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Remember: Here, we are not binding the address to the client's socket. instead we are creating the address so that the client will be
    // able to connect to the socket of the server.
    // * The Client will be running on a different port than the port specified for connection with the server (That is the port the server listens to and not the client)

    connect(sock, (struct sockaddr*)&addr, sizeof(addr)); // what does size of a struct really mean

    char* msg = malloc(BUFLEN);
    char* reply = malloc(BUFLEN);

    while(1)
    {
        printf("Enter the message (or enter \"quit\" to exit): ");
        if(fgets(msg, BUFLEN, stdin) == NULL)
        {
            break;
        }

        msg[strcspn(msg, "\n")] = '\0';

        if(!strcmp(msg, "quit"))
        {
            break;
        }
        send(sock, msg, strlen(msg), 0);
    
        int len = recv(sock, reply, BUFLEN-1, 0);

        reply[len] = '\0';
        printf("Got: %s\n", reply);

    }
    free(reply);
    free(msg);
    closesocket(sock);
    WSACleanup();
    return 0;
    // Question: Previously in server, we were sending and receiving things with the client. But, here we are using the same sock for connecting, sending and receiving?
    // Because, when the server accepts the connection reached out by the client, it uses the socket information of the server. Hence, that info is known to the client.
    // That is why the client socket is enough for sending information to the server

}