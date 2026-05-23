// Include Windows headers BEFORE any C++ standard headers to avoid
// std::byte vs Windows byte conflict with 'using namespace std'
#include <winsock2.h>
#include <ws2tcpip.h>

#include "SolarSystemSimulation.h"
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed!" << endl;
        return 1;
    }

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        cerr << "Socket creation failed!" << endl;
        WSACleanup();
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5050);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(server_fd, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        cerr << "Bind failed!" << endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    listen(server_fd, 1);
    cout << "C++ physics server running on port 5050" << endl;

    sockaddr_in clientAddr{};
    int clientLen = sizeof(clientAddr);
    SOCKET client = accept(server_fd, (sockaddr*)&clientAddr, &clientLen);
    if (client == INVALID_SOCKET) {
        cerr << "Accept failed!" << endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    cout << "Java client connected!" << endl;

    SolarSystemSimulation* sim = new SolarSystemSimulation();
    char buffer[256];

    while (true) {
        int bytes = recv(client, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;

        buffer[bytes] = '\0';
        
        // Check for RESET command
        if (strncmp(buffer, "RESET", 5) == 0) {
            delete sim;
            sim = new SolarSystemSimulation();
            
            // Send initial positions after reset
            string json = sim->update(0.0);
            json += "\n";
            send(client, json.c_str(), (int)json.size(), 0);
            continue;
        }
        
        // Otherwise parse as timestep
        double dt;
        if (sscanf(buffer, "%lf", &dt) != 1) continue;

        string json = sim->update(dt);
        json += "\n";
        send(client, json.c_str(), (int)json.size(), 0);
    }

    delete sim;

    closesocket(client);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
