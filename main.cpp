// This is the entry point for the application.

/* The main application will declare three threads:
1. Listener thread for the latest data from the "sensor" over UDP.
2. A "timer" thread which raises an interrupt on the process, triggering a function that processes the latest data.
3. The main thread of the process, which continues running while waiting for an interrupt.
*/

// Include statements for threads, interrupt, and access to sleep/time functions
#include <csignal>
#include <unistd.h> // required for getpid()
#include <thread>
#include <chrono>

// Headers for common variables and the listener.
#include "data.h"
#include "listener.h"

// Define an instance of the SENSOR_DATA struct, to be shared between the threads.
// Why does this struct need to be shared between threads? 
// 1. One thread is constantly trying to update this struct with the most up to date data from the sensor (job of the listener).
// 2. One thread is constantly trying to read the data within the struct so that it can be "processed" - in our case, writing it to the console.
SENSOR_DATA currentSensorData{};

// Define a mutex, to be used by threads for locking read/write access to the currentSensorData struct.
std::mutex currentSensorDataMutex;

// This is the interrupt service routine for a SIGUSR1 interrupt. 
// In this application, the interrupt is thrown every TIME_STEP_INTERVAL - see main() below.
// The main process will stop execution and service the interrupt.
void processData(int signal) {

    // This overrun variable represents whether processData() is currently running.
    // In C++, static variables are declared once for the lifetime of a program. 
    // It is assigned to false on the first run of processData(), but will not be reinitialized to false each time the function is called.
    // This allows the variable to be only be accessible within this function, while saving its value for the next function call.
    static bool overrun = false;

    // Disable the interrupt for SIGUSR1, so that interrupts triggered while checking for an overrun are ignored.
    // This is because the function calls in this service handler are not all signal-safe by the Linux/UNIX documentation standard.
    // Problems with unsafe functions are avoided by ignoring any incoming SIGUSR1 signals from the other threads.
    // https://man7.org/linux/man-pages/man7/signal-safety.7.html
    std::signal(SIGUSR1, SIG_IGN);

    // Check for overrun while the interrupt is disabled - if some other processData is still running, the OverrunFlag must be true.
    // If it is, re-enable the interrupt handler and return so another time step can pass.
    if (overrun) {
        std::cout << "processData() overrun - re-enable interrupt and wait another time step\n";
        std::signal(SIGUSR1, processData);
        return; // Return and wait another time step.
    }

    // Set overrun to true to signify the processing function has started.
    overrun = true;

    // With the task started, re-enable the SIGUSR1 interrupt. Other interrupts will trigger processData but return until this execution is complete.
    std::signal(SIGUSR1, processData);

    // "Process" the data here.
    // steps are, lock mutex, read the currentSensorData values, print them to the console. 
    // Potential to move this printing into a function defined in the SENSOR_DATA struct later.
    currentSensorDataMutex.lock();
    std::cout << "Printing last known data from sensor.\n";
    std::cout << "     windspeed: " << currentSensorData.windspeed << " m/s\n";
    std::cout << "     latitude: " << currentSensorData.latitude << "\n";
    std::cout << "     longitude: " << currentSensorData.longitude << "\n";
    currentSensorDataMutex.unlock();

    // Indicate the task is complete, set overrun to false.
    overrun = false;

}

int main() {
    
    // Set the signal handler for SIGUSR1, a user-defined signal which we will use as the real-time "timer", to be nothing for now.
    std::signal(SIGUSR1, SIG_IGN);

    // Create a new thread to listen for data from the sensor
    // This function runs forever because it has a while(true) loop.
    std::thread ListenForSensorDataThread([] {
        receiveFromSensor();
    });

    // Set the signal handler for SIGUSR1, to be processData().
    // Whenever SIGUSR1 is raised on the process, the main thread of the process will execute processData().
    std::signal(SIGUSR1, processData);

    // Create the "timer" thread, which throws a SIGUSR1 interrupt every TIME_STEP_INTERVAL.
    // The reason this is a separate thread from the main thread, is so that regardless of the computation time required to run processData(),
    // an interrupt is always triggered every TIME_STEP_INTERVAL from the start of the program's execution.
    // For a real time application with a requirement to call processData() every interval, this prevents the time between interrupts from increasing.
    std::thread clockThread([] {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP_INTERVAL));
            kill(getpid(), SIGUSR1);
        }
    });

    // After creating a thread to execute the listener function and another to control real-time execution via interrupts,
    // The main thread of the process continues here to service a SIGUSR1 interrupt every TIME_STEP_INTERVAL.
    // TODO: this is wasteful and should be replaced with a thread wait call, see open issue.
    while (true) {

        // Wait for an interrupt from the timer thread.

    }

}