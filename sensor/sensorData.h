// Contains include statements for headers, as well as a central place to declare the time intervals used throughout the application.

// Header for standard input/output stream
#include <iostream>

// Headers for using time interrupts:
#include <chrono>
#include <thread>

// Set the interval for when the application should send new data, in milliseconds:
#define SENSOR_SEND_INTERVAL 1000

// Set the port and IP address that the sensor will send data to over UDP
#define SEND_PORT 41011
#define SEND_IP "127.0.0.1"

/* The definition for the struct of data representing readings from the sensor.
For this example program, we'll say this "sensor" sends the main application three data values:
1. Wind speed, in meters per second
3. Latitude location of the sensor 
4. Longitude location of the sensor
*/
struct SENSOR_DATA
{
    float windspeed;
    float latitude;
    float longitude;
} typedef SENSOR_DATA;
