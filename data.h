// Contains include statements for common headers, as well as a central place to declare the time intervals used throughout the application.

// Header for standard input/output stream
#include <iostream>

// Header for access to mutex, concurrency support library.
#include <mutex>

// Set the interval for when the application should process data, in milliseconds:
#define TIME_STEP_INTERVAL 3000

// Set the port and IP address that the listener will bind to for data from the sensor over UDP
#define LISTENER_PORT 41011
#define LISTENER_IP "127.0.0.1"

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

// By declaring an extern struct variable representing the current sensor data, each source file that includes data.h is able to reference the variable instantiated in main.cpp.
// This limits the scope from a global variable, to only those source files that include the data.h file.
extern SENSOR_DATA currentSensorData;

// By declaring a mutex for the current sensor data, a thread can use it as a locking mechanism while it is either reading the data in the struct or updating the data in the struct.
// The mutex is required for thread-safe sharing of the same struct of data. By declaring it as an extern, code from files that include data.h will be able to reference it.
// It is instantiated in main.cpp.
extern std::mutex currentSensorDataMutex;
