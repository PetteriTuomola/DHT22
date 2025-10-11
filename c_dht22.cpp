#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

static int edgeupcounter;
static int edgedowncounter;

static void cb_both(WPIWfiStatus status, void* userdata) {
    if (status.edge == INT_EDGE_RISING)
        edgeupcounter++;
    else if (status.edge == INT_EDGE_FALLING)
        edgedowncounter++;
}


int main() {
    int pin = 3; // GPIO pin number
    wiringPiSetupPinType(WPI_PIN_PHYS);
    wiringPiISR2(pin, INT_EDGE_BOTH, &cb_both, 0, NULL);
    for (int i = 0; i < 100; i++) {
        edgeupcounter = 0;
        edgedowncounter = 0;
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 0);
        usleep(2000);
        pinMode(pin, INPUT);
        pullUpDnControl(pin, PUD_UP);

        sleep(3);
        printf("Rising edges: %d, Falling edges: %d\n", edgeupcounter, edgedowncounter);
    }
    return 0;
}