#include <iostream>
#include <winsock2.h>
#include <cstring>
#include <sstream>

#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_SIZE 1024
#define PORT 8080

using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed." << endl;
        return 1;
    }   

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed." << endl;
        WSACleanup();
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if(bind(
        serverSocket, (sockaddr *)&serverAddr,
        sizeof(serverAddr)) == SOCKET_ERROR) {
            cerr << "Binding failed." << endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
    }

    if(listen(serverSocket, 3) == SOCKET_ERROR) {
        cerr << "Listening failed." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Waiting for connection..." << endl << endl;

    clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &addrLen);
    if(clientSocket == INVALID_SOCKET) {
        cerr << "Acceptance failed." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    string username, msg;

    cout << "=========================" << endl;
    cout << "     SIMPLE CHAT APP     " << endl;
    cout << "=========================" << endl << endl;
    cout << "Connection established." << endl;
    cout << "Introduce your username: ";
    getline(cin, username);
    cout << "Waiting for iteraction..." << endl << endl;

    cout << "=========================" << endl << endl;
    while(true) {
        int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if(bytesRead == 0) {
            cout << "Connection closed by peer." << endl;
            break;
        } else if(bytesRead < 0) {
            cerr << "Reception failed." << endl;
            break;
        }
        buffer[bytesRead] = '\0';

        cout << buffer << endl;
        cout << username << ": ";
        getline(cin, msg);
        if(msg == "q") {
            shutdown(serverSocket, SD_SEND);
            break;
        }
        msg = username + ": " + msg;

        send(clientSocket, msg.c_str(), strlen(msg.c_str()), 0);
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}