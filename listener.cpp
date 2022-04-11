#include "data.h"

// Include statements required for socket communication
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

// In terms of client-server communication, this listener.cpp acts as the SERVER, it is waiting for data from a "client".

/*
    The receiveFromSensor() function opens a port for UDP socket communication, and continually listens for data from the sensor application on this port.
    Once data is received, the new data is copied into the currentSensorData struct, which the main.cpp functions also have access to.
*/
void receiveFromSensor() {
   
    int socketFD;                               // Socket file descriptor
    struct sockaddr_in serverSockAddr = {};     // A sockaddr_in struct representing the "server's" address, THIS address.
    struct sockaddr_in clientSockAddr = {};     // A sockaddr_in struct which will store the "client's" address after receiving data
    unsigned int clientAddrLen;                 // Length of the clientSockAddr struct
    int recvMsgSize;                            // Size of received message
    int flags;                                  // Variable for use to specify any flags for the recvfrom() call

    struct SENSOR_DATA *newSensorData = new SENSOR_DATA; // A new struct for the incoming sensor data

    // Initialize variables for server IP address and port
    char listenerIP[] = LISTENER_IP;
    unsigned short serverPort = LISTENER_PORT;

    // Create socket for receiving over UDP, exit if error.
    if ((socketFD = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        std::cerr << "listener.cpp call to socket() failed. Thread exiting.";
        return;
    }

    // Create the sockaddr_in struct needed to define the server address
    serverSockAddr.sin_family = AF_INET;                        // Set internet address family constant to specify use of IPv4 addresses
    serverSockAddr.sin_addr.s_addr = inet_addr(listenerIP);     // IP address of the server set as LISTENER_IP defined in data.h
    serverSockAddr.sin_port = htons(serverPort);                // Use htons() to convert the listener port from "host byte order" to "network byte order" (big endian)

    // Bind to the local address, exit if error.
    if (bind(socketFD, (struct sockaddr *)&serverSockAddr, sizeof(serverSockAddr)) < 0) {
        std::cerr << "listener.cpp call to bind() failed. Thread exiting.";
        return;
    }

    std::cout << "listener.cpp socket binding success. Now listening for sensor data.\n";
    
    flags = 0; // Set flags needed for recvfrom() here. In this case, no flags are needed for the recvfrom() call.

    while (true) { // Run forever - always listen for updates from the sensor

        // Set the size of the in-out parameter
        clientAddrLen = sizeof(clientSockAddr);

        // Block until receive message from the sensor - report an error and wait again if recvfrom() returns -1.
        // https://pubs.opengroup.org/onlinepubs/007904875/functions/recvfrom.html
        if ((recvMsgSize = recvfrom(socketFD, newSensorData, sizeof(*newSensorData), flags, (struct sockaddr *)&clientSockAddr, &clientAddrLen)) == -1) {
            std::cerr << "listener.cpp call to recvfrom() indicated an error. Continue listening for data.";
            continue;
        }

        /* 
        Outside of the scope of this project, but worth acknowledging in terms of security,
        would be a mechanism here to confirm the validity of the received data before copying the data into the currentSensorData struct.
        Though this project is more focused on demostrating the use of UDP and thread, if this data were critical to a real-time system,
        it would be imperative to provide a check that confirms the correctness of the received data before providing it to other functions. 
        */

        // Lock the sensor data mutex, copy the new data into the currentSensorData struct, then unlock the sensor data mutex.
        currentSensorDataMutex.lock();
        std::cout << "listener.cpp received data from sensor. Copying new data from sampleSensorData to currentSensorData.\n";
        currentSensorData.windspeed = newSensorData->windspeed;
        currentSensorData.latitude = newSensorData->latitude;
        currentSensorData.longitude = newSensorData->longitude;
        currentSensorDataMutex.unlock();

    }

}
