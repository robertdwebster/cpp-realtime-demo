/* The main application will have three threads:
1. Listener thread for the latest data from the "sensor" over UDP.
2. A "timer" thread which raises an interrupt on the process, triggering a function that processes the latest data.
3. The main thread of the process, which continues running while waiting for an interrupt.
*/

#include <iostream>

int main (int argc, char *argv[]) {

    std::cout << "hello, world";
    return 0;
}