#include "data.h"
#include <iostream>

SENSOR_DATA sampleSensorData = {4.0000000, 39.093314910681286, -84.50985879586851};

void receiveFromSensor() {

    // todo: implement UDP listener code
    // For now, wait 2 seconds and send a hello world message
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        

        // Try to lock the mutex for the currentSensorData struct
        // Comment out for now, testing use of try_lock.
        // currentSensorDataMutex.lock();

        if (currentSensorDataMutex.try_lock()) {
            // Access the currentSensorData struct, update the currentSensorData struct with the newest values
            std::cout << "receiveFromSensor() is copying from sampleSensorData to currentSensorData\n";
            currentSensorData.windspeed = sampleSensorData.windspeed;
            currentSensorData.latitude = sampleSensorData.latitude;
            currentSensorData.longitude = sampleSensorData.longitude;
        
            // Unlock the mutex for the currentSensorData struct
            currentSensorDataMutex.unlock();

        } else {

            // Else, continue to next loop iteration (wait) because the struct is busy.
            std::cout << "receiveFromSensor() couldn't update currentSensorData - mutex locked!\n";

        }
        
    }

}