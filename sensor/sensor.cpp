/*
    The purpose of sensor.cpp is to represent a near real-time wind sensor, which is continually sending data to the main application over UDP.
    It is not compiled as part of the main executable, it is meant to represent a completely separate executable and entity.
    
    The receiveFromSensor() function opens a port for UDP socket communication, and continually listens for data from the sensor application on this port.
    Once data is received, the new data is copied into the currentSensorData struct, which the main.cpp functions also have access to.
*/

// Include statements are consolidated to sensorData.h
#include "sensorData.h"


int main() {

    // Begin code for initializing UDP communication.
    int socketFD;                                   // Socket file descriptor
    struct sockaddr_in destinationSockAddr = {};    // A sockaddr_in struct representing the "destination" address, this is describing the server's IP address and port.
        
    // Initialize variables for destination IP address and port
    char serverIP[] = SEND_IP;
    unsigned short serverPort = SEND_PORT;

    // Variable to specify any flags for the sendto() call
    int flags;

    // Create socket for sending over UDP
    if ((socketFD = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        std::cerr << "Call to socket() failed. Exiting.";
        return -1;
    }

    // Construct the sockaddr_in struct needed to define the server's address, i.e. the IP and port which listener.cpp is running on
    destinationSockAddr.sin_family = AF_INET;                       // Set internet address family constant to specify use of IPv4 addresses
    destinationSockAddr.sin_addr.s_addr = inet_addr(serverIP);      // IP address of the server set as SEND_IP defined in sensorData.h
    destinationSockAddr.sin_port = htons(serverPort);               // Use htons() to convert the destination port from "host byte order" to "network byte order" (big endian)

    /* 
    Note that for UDP communication, unlike the "server" which in this case is listener.cpp, a call to bind() is not necessary on the "client" end.
    Using the sendto() function allows the system to perform an implicit bind() as long as the IP and port of the destination are provided.
    This is so the data can be sent from an unspecified port - the system will prevent conflicts with other ports that could already be in use.
    */

    // Initialize empty struct of SENSOR_DATA
    SENSOR_DATA dataToSend = {};

    // Set flags needed for sendto() here.
    // In this case, specify the MSG_DONTROUTE flag so that the destination address must refer to a local network interface (loopback).
    // This is another check to ensure data is not sent out over UDP to on any other network interfaces.
    flags = MSG_DONTROUTE;

    // Initialize variables for random number generation of wind speed
    float newWindSpeedReading = 0.0;
    std::random_device rd;
    std::default_random_engine random_engine(rd());

    // Define a uniform distribution between WINDSPEED_MIN AND WINDSPEED_MAX to generate a random average wind speed for the lifetime of the sensor program
    std::uniform_real_distribution<float> uniform_dist(WINDSPEED_MIN, WINDSPEED_MAX);

    // Generate and send sensor data until program is exited manually - send data according to the SENSOR_SEND_INTERVAL in sensorData.h
    while (true) {
        
        // Wait for one SENSOR_SEND_INTERVAL before generating and sending data.
        std::this_thread::sleep_for(std::chrono::milliseconds(SENSOR_SEND_INTERVAL));

        // Call the normal distribution to generate a new wind speed reading, then update the dataToSend struct with this data.
        newWindSpeedReading = uniform_dist(random_engine);
        std::cout << "Current wind speed: " << newWindSpeedReading << " m/s\n";
        dataToSend = {newWindSpeedReading, SENSOR_LATITUDE, SENSOR_LONGITUDE};

        // Send the newly generated data to the listener. Detect any errors by checking for -1, and exit if so.
        // https://pubs.opengroup.org/onlinepubs/007904875/functions/sendto.html
        if (sendto(socketFD, &dataToSend, sizeof(dataToSend), flags, (struct sockaddr *)&destinationSockAddr, sizeof(destinationSockAddr)) == -1) {
            std::cerr << "A local error occurred on call to sendto(). Exiting.";
            return -1;
        } else {
            std::cout << "Sent sensor data to listener.\n";
        }

    }
}