// Contains include statements for headers, as well as a central place to declare the time intervals used throughout the application.

// Headers for using time interrupts:
#include <chrono>
#include <thread>

// Set the interval for when the application should process data, in milliseconds:
#define TIME_STEP_INTERVAL 1000

/* The definition for the struct of data representing readings from the sensor.
For this example program, we'll say this "sensor" sends the main application three data values:
1. Wind speed, in kilometers per hour
3. Latitude location of the sensor 
4. Longitude location of the sensor
*/
struct SENSOR_DATA
{
    float windspeed;
    float latitude;
    float longitude;
} typedef SENSOR_DATA;

// By declaring an extern variable representing a pointer to the current sensor data, each source file that includes data.h is able to reference it.
// It is declared and instantiated in main.cpp.
extern SENSOR_DATA *currentSensorData;