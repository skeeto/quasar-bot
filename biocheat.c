#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

SOCKET remote()
{
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        fprintf(stderr, "startup failed\n");
        exit(EXIT_FAILURE);
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "sock error\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server = {0};
    server.sin_family = 2;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2000);
    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) != 0) {
        fprintf(stderr, "bind error\n");
        exit(EXIT_FAILURE);
    }
    if (listen(sock, 2) != 0) {
        fprintf(stderr, "listen error\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client;
    int c = sizeof(client);
    SOCKET csock = accept(sock, (struct sockaddr *)&client, &c);
    if (csock == INVALID_SOCKET) {
        fprintf(stderr, "accpet error %ld\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //send(csock, msg, s, 0);
    return csock;
}

#define WHITE 0xffffff

int main(int argc, char **argv)
{
    while (1) {
        POINT p;
        GetCursorPos(&p);
        //GetDC(GetDesktopWindow())
        COLORREF color = GetPixel(GetWindowDC(GetDesktopWindow()), p.x, p.y);
        color = htonl(color) >> 8;
        printf("%ld %ld #%06lx\n", p.x, p.y, color);
        Sleep(100);
    }
    return 0;
}
