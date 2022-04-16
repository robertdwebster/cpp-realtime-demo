# cpp-realtime-demo

![The John A. Roebling Bridge between Covington, Kentucky and Cincinnati, Ohio. Image 'Roebling Suspension Bridge at night.jpg' used with permission and without changes, from Wikimedia Commons, author EEJCC, under the Creative Commons Attribution-Share Alike 4.0 International license, https://creativecommons.org/licenses/by-sa/4.0/deed.e](/img/roebling.jpg)

In real-time applications, data often needs to be accessed or mutated by multiple threads at once. Threads may also be used to trigger interrupts for time-sharing applications. This project attempts to demonstrate the sharing of a single struct between threads in a safe manner using mutex locks, and the use of threads to process the data in the struct once a given time interval has passed.

The project has two components which demonstrate this.
1. **sensor.out**: The "data source" for the project. This is meant to model a wind speed sensor placed on a certain historic bridge in Cincinnati, Ohio - which is providing a stream of real-time data to the main application. The sensor continuously sends a randomly generated value representing a wind speed over UDP, according to a defined time interval. It also sends a latitude and longitude reading of where the sensor is physically placed.
2. **main.out**: The core multi-threaded application, which is continuously listening for the latest data from the sensor over UDP. According to a set time interval, and independently from the sensor, an interrupt service routine prints the latest data received.

**How are these concepts relevant to a real application?**
In a real-time application environment, such as software controls running on a car or plane, interfaces for managing incoming data from other onboard devices could be defined in a language such as C++. Further, the overall structure of main.cpp, with a ```processData()``` function and threads of execution to concurrently execute independent features, could be used in a similar way to provide real-time input to another device or to a code-generated Simulink model.

## Repository Structure
* **sensor** - directory containing components for the separate sensor executable
    * **makefile** - contains compile commands for the sensor application
    * **sensor.cpp** - C++ source for the sensor, generates and sends data over UDP
    * **sensorData.h** - sensor header file for definitions and include statements
* **.gitignore**
* **README.md**
* **data.h** - contains common definitions and include statements for main.cpp
* **listener.cpp** - C++ source for the main application's listener for data from the sensor
* **listener.h** - listener header file, which is included by main.cpp
* **main.cpp** - defines main method, thread execution, and the processData() function
* **makefile** - contains compile commands for the main application

## Compiling and Running
Since C implementations and standards differ by operating system, this application is intended for use on a Linux machine. Compilation is performed using the g++ compiler.

Both the main application and the sensor have their own makefiles which define compile commands and a ```make clean``` command.

To compile and run this project:

1. Compile the main application. Run ```make``` in the root project directory.
2. Compile the sensor application. Run ```make``` in the ```/sensor``` directory.
3. Run the main application executable first, with ```./main.out```.
4. Run the sensor application executable second, with ```./sensor.out```.

To remove all generated objects and executables, run ```make clean``` both in the main project directory and in the ```/sensor``` directory.