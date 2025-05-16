#include <iostream>
#include <sstream>
#include <winsock2.h>
#include <cstring>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed." << endl;
        return 1;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed." << endl;
        WSACleanup();
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(clientSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Connection failed" << endl;
        closesocket(clientSocket);
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

        cout << endl;

        cout << "=========================" << endl << endl;

        while(true) {
            cout << username << ": ";
            getline(cin, msg);
            if(msg == "q") {
                shutdown(clientSocket, SD_SEND);
                break;
            }

            msg = username + ": " + msg;

            send(clientSocket, msg.c_str(), msg.length(), 0);
            memset(buffer, 0, BUFFER_SIZE);

            int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if(bytesReceived == 0) {
                cout << "Connection closed by peer." << endl;
                break;
            } else if(bytesReceived < 0) {
                cerr << "Reception failed." << endl;
                break;
            }
            buffer[bytesReceived] = '\0';

            cout << buffer << endl;
        }

        closesocket(clientSocket);
        WSACleanup();
        return 0;
}