//
// Created by Ivan Zharov on 2019-02-04.
//


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <math.h>
#include <set>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <time.h>

int sleeptime = 50;
int rad_active = 0;
sf::Clock clock1;
sf::Clock clock2;

sf::TcpSocket socket1;
sf::TcpSocket socket2;

char last1[1024];
char last2[1024];


char in1[1024];
char in2[1024];

bool newdata1 = false;
bool newdata2 = false;

void waitforclient1data() {
    while (true) {
        std::size_t received1;
        if (socket1.receive(in1, sizeof(in1), received1) != sf::Socket::Done) {
            std::cout << "'OK' ERROR" << std::endl;
        } else {
            std::cout << "Answer received from the client1: \"" << in1 << "\"" << std::endl;
        }
        newdata1 = true;
        for (int i=received1; i<1024; ++i) {
            in1[i] = ' ';
        }
        if (socket2.send(in1, sizeof(in1)) != sf::Socket::Done) {
            std::cout << "Message ERROR from client1 not delievered to the client2: \"" << in1 << "\"" << std::endl;
        }
        std::cout << "Message sent to the client2: \"" << in1 << "\"" << std::endl;
        newdata1 = false;
//        Sleep(sleeptime);
    }
}

void waitforclient2data() {
    while (true) {
        std::size_t received2;
        if (socket2.receive(in2, sizeof(in2), received2) != sf::Socket::Done) {
            std::cout << "'OK' ERROR" << std::endl;
        } else {
            std::cout << "Answer received from the client2: \"" << in2 << "\"" << std::endl;
        }
        newdata2 = true;
        for (int i=received2; i<1024; ++i) {
            in2[i] = ' ';
        }
        if (socket1.send(in2, sizeof(in2)) != sf::Socket::Done) {
            std::cout << "Message ERROR from client2 not delievered to the client1: \"" << in2 << "\"" << std::endl;
        }
        std::cout << "Message sent to the client1: \"" << in2 << "\"" << std::endl;
        newdata2 = false;
//        Sleep(sleeptime);
    }
}

void runTcpServer(unsigned short port)
{

    int gotclients=0;
    bool firsttime = true;
    sf::TcpListener listener;
//    listener.setBlocking(false);
    socket1.setBlocking(true);
    socket2.setBlocking(true);

    // Create a server socket to accept new connections

    // Listen to the given port for incoming connections
    if (listener.listen(port) != sf::Socket::Done)
        return;
    std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

    // Wait for a connection

    if (listener.accept(socket1) != sf::Socket::Done)
        return;
    gotclients++;
    std::cout << "Client 1 connected: " << socket1.getRemoteAddress() << std::endl;
    // Send a message to the connected client

    char out1[] = "Hi, wait for an companion ";
    if (socket1.send(out1, sizeof(out1)) != sf::Socket::Done) {
        std::cout << "'OK' ERROR" << std::endl;
    }
    std::cout << "Message sent to the client: \"" << out1 << "\"" << std::endl;

    // Receive a message back from the client
//    char in1[1024];
//    std::size_t received1;
//    if (socket1.receive(in1, sizeof(in1), received1) != sf::Socket::Done)
//        return;
//    std::cout << "Answer received from the client: \"" << in1 << "\"" << std::endl;

    /// new client

    if (listener.accept(socket2) != sf::Socket::Done)
        return;
    gotclients++;
    std::cout << "Client 2 connected: " << socket2.getRemoteAddress() << std::endl;
    // Send a message to the connected client

    char out2[] = "Hi, wait for a start ";
    if (socket2.send(out2, sizeof(out2)) != sf::Socket::Done) {
        std::cout << "'OK' ERROR" << std::endl;
    }
    std::cout << "Message sent to the client: \"" << out2 << "\"" << std::endl;

    // Receive a message back from the client
//    char in2[1024];
//    std::size_t received2;
//    if (socket2.receive(in2, sizeof(in2), received2) != sf::Socket::Done)
//        return;
//    std::cout << "Answer received from the client: \"" << in2 << "\"" << std::endl;

    sf::Thread thread1(&waitforclient1data);
    thread1.launch();
    sf::Thread thread2(&waitforclient2data);
    thread2.launch();

    bool serverisrunning = true;


}

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Choose an arbitrary port for opening sockets
    const unsigned short port = 50001;

    // TCP, UDP or connected UDP ?
//    char protocol = 'y';
//    std::cout << "Do you want to use Telegram2 yes (y) or no (n)? ";
//    std::cin  >> protocol;

    // Client or server ?

    runTcpServer(port);
//    runTcpClient(port);

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
