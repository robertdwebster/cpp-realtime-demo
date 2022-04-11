# cpp-realtime-demo

![The John A. Roebling Bridge between Covington, Kentucky and Cincinnati, Ohio. Image 'Roebling Suspension Bridge at night.jpg' used with permission and without changes, from Wikimedia Commons, author EEJCC, under the Creative Commons Attribution-Share Alike 4.0 International license, https://creativecommons.org/licenses/by-sa/4.0/deed.e](/img/roebling.jpg)

In real-time applications, data often needs to be accessed or mutated by multiple threads at once. Threads may also be used to trigger interrupts for time-sharing applications. This project attempts to demonstrate the sharing of a single struct between threads in a safe manner using mutex locks, and the use of threads to process the data in the struct once a given time interval has passed.

The project has two components which demonstrate this.
1. **sensor.out**: The "data source" for the project - meant to model a wind speed sensor which is providing a stream of real-time "live" data to the main application. The sensor continuously sends a randomly generated value representing the wind speed over UDP according to a defined time interval. It also sends a latitude and longitude reading of where the sensor is physically placed.
2. **main.out**: The core application, which is continuously listening for the latest data from the sensor over UDP. According to a set time interval, and independently from the sensor, prints the latest data received.

**How are these concepts relevant to a real application?**
In a real-time application environment, such as software controls running on a car or plane, an interface to manage incoming data from other onboard devices can be defined in a language such as C++. Further, the overall structure of main.cpp, with a ```processData()``` function and independent threads of execution to handle various functions, could be used in a similar way to provide live input to a code-generated Simulink model.

## Repository Structure
* sensor - directory containing components for the separate sensor executable
    * makefile - contains compile commands for the sensor application
    * sensor.cpp - C++ source for the sensor, generates and sends data over UDP
    * sensorData.h - sensor header file for definitions and include statements
* .gitignore
* README.md
* data.h - contains common definitions and include statements for main.cpp
* listener.cpp - C++ source for the main application's listener for data from the sensor
* listener.h - listener header file, which is included by main.cpp
* main.cpp - defines main method, thread execution, and the processData() function
* makefile - contains compile commands for the main application

## Compiling and Running
This project was developed on a Linux computer and proper function may depend on the use of a Unix machine to execute. Compilation is performed using the g++ compiler.

Both the main application and the sensor have their own makefiles which define compile commands and a ```make clean``` command.

1. Compile the main application. Run ```make``` in the root project directory.
2. Compile the sensor application. Run ```make``` in the ```/sensor``` directory.
3. Run the main application with ```./main.out```.
4. Run the sensor application with ```./sensor.out```.

To remove all generated objects and executables, run ```make clean``` both in the main project directory and in the ```/sensor``` directory.