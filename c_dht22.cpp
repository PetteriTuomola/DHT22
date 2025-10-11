#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

static int edgecounter;

static void cb_both() {
    edgecounter++;
}


int main() {
    int pin = 3; // GPIO pin number
    edgecounter = 0;
    wiringPiSetupPinType(WPI_PIN_PHYS);

    pinMode(pin, OUTPUT);
    digitalWrite(pin, 1);
    sleep(50000);
    digitalWrite(pin, 0);
    usleep(2000);
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);

    wiringPiISR(pin, INT_EDGE_BOTH, &cb_both);
    std::cout << "Edge count: " << edgecounter << std::endl;
    return 0;
}