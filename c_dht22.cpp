#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

static int edgecounter;

static void cb_both(WPIWfiStatus status, void* userdata) {
    edgecounter++;
    if (edgecounter % 10 == 0) {
        std::cout << "ten" << std::endl;
    }
}


int main() {
    int pin = 3; // GPIO pin number
    wiringPiSetupPinType(WPI_PIN_PHYS);
    for (int i = 0; i < 100; i++) {
        edgecounter = 0;
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 1);
        usleep(50000);
        digitalWrite(pin, 0);
        usleep(2000);
        pinMode(pin, INPUT);
        pullUpDnControl(pin, PUD_UP);

        wiringPiISR2(pin, INT_EDGE_BOTH, &cb_both, 20000, NULL);
        std::cout << "Edge count: " << edgecounter << std::endl;
        return 0;
    }
}