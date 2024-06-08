// C20app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")


/*
    Steps for using windows socket library
    1. Initialize winsock library
    2. create the socket
    3. get the ip and port
    4. bind the ip/port with the socket
    5. Listen on the socket
    6. accept
*/

bool Initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;

}
int main()
{
    if (!Initialize())
    {
        cout << "winsock initialization failed" << endl;
        return 1;
    }
    std::cout << "Server Programming\n";


    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET)
    {
        cout << "Socket Programming failed" << endl;
        return 1;
    }
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(12345);

    if(InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1)
    {
        cout << "setting address structure failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    // Convert the IP address (0.0.0.0) put it inside the sin_family in binary format
    if(bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
    {
        cout << "Bind Failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "Listen Failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;

    }
    cout << "Server has started listening on port " << 3000<<endl;
    SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Invalid client Socket" << endl;
        return 1;
    }
    char buffer[4096];
    int bytesrcvd = recv(clientSocket, buffer, sizeof(buffer), 0);   
    string message(buffer, bytesrcvd);
    cout << "message from client : " << message << endl;
    closesocket(clientSocket);
    closesocket(listenSocket);


    WSACleanup();
    return 0;
   
}

