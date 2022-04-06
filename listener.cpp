#include "data.h"
#include <iostream>

void receiveFromSensor() {

    // todo: implement UDP listener code
    // For now, wait 2 seconds and send a hello world message
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "hello from receiveFromSensor()\n" << std::flush;
    }

}