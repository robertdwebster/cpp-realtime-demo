# cpp-realtime-demo
In real-time applications, data often needs to be accessed or mutated by multiple threads at once. Threads may also be used to trigger interrupts for time-sharing applications. This project attempts to demonstrate the sharing of a single struct between threads in a safe manner using mutex locks, and the use of threads to process the data in the struct once a given time interval has passed.

The project has two components which demonstrate this.
1. **sensor**: Our "data source" for the project - meant to model a sensor which is providing a stream of real-time data to the main application. The sensor continuously sends a value over UDP according to a defined time interval.
2. **app**: The core application, which is continuously listening for the latest data from the sensor over UDP. According to a set time interval and independently from the sensor, performs an action on the latest data received.

## Repository Structure
todo once implemented.

## Compiling and Running
todo once implemented.