#include "data.h"
#include <iostream>

// In terms of client-server communication, this listener.cpp acts as the client.

SENSOR_DATA sampleSensorData = {4.0000000, 39.093314910681286, -84.50985879586851};

void receiveFromSensor() {

    // todo: implement UDP listener code
    // For now, wait 2 seconds and send a hello world message
    while (true) {
        // time will be handled by the sensor
        // std::this_thread::sleep_for(std::chrono::milliseconds(1500)); 

        // Try to lock the mutex for the currentSensorData struct
        currentSensorDataMutex.lock();

        // Copy sample data for now into currentSensorData struct.
        std::cout << "receiveFromSensor() is copying from sampleSensorData to currentSensorData\n";
        currentSensorData.windspeed = sampleSensorData.windspeed;
        currentSensorData.latitude = sampleSensorData.latitude;
        currentSensorData.longitude = sampleSensorData.longitude;
        
        // Unlock the mutex for the currentSensorData struct
        currentSensorDataMutex.unlock();
        
    }

}