#include <wiringPi.h>
#include <iostream>

int main() {
    int pin = 3; // GPIO pin number
    int edgecounter = 0;
    wiringPiSetupPinType(WPI_PIN_PHYS);

    pinMode(pin, OUTPUT);
    digitalwrite(pin, 1);
    sleep(0.05);
    digitalWrite(pin, 0);
    sleep(0.002);
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);

    wiringPiISR(pin, INT_EDGE_BOTH, []() {
        edgecounter++;
    });
    std::cout << "Edge count: " << edgecounter << std::endl;
    return 0;
}