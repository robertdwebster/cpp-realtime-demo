// Contains include statements for headers, as well as a central place to declare the time intervals used throughout the application.

// Include statements required for socket communication
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

// Header for standard input/output stream
#include <iostream>

// Headers for using thread sleep functions:
#include <chrono>
#include <thread>

// Headers for generating random values
#include <random>

// Set the interval for when the application should send new data, in milliseconds:
#define SENSOR_SEND_INTERVAL 1000

// Set the port and IP address that the sensor will send data to over UDP
#define SEND_PORT 41011
#define SEND_IP "127.0.0.1"

// Set min and max values for windspeed "readings", in m/s. Used by generateWindSpeed().
#define WINDSPEED_MIN 1.34112 // 3 mph converted to m/s
#define WINDSPEED_MAX 1.78816 // 4 mph converted to m/s

// Set the latitude and longitude for the windspeed sensor - just having some fun, I wonder where this is located?
#define SENSOR_LATITUDE 39.093314910681286
#define SENSOR_LONGITUDE -84.50985879586851

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
