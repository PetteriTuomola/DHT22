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
    pullUpDnControl(pin, PUD_UP);
    for (int i = 0; i < 100; i++) {
        edgeupcounter = 0;
        edgedowncounter = 0;
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 0);
        usleep(2000);
        pinMode(pin, INPUT);

        sleep(3);
        printf(digitalRead(pin) ? "HIGH\n" : "LOW\n");
        printf("Rising edges: %d, Falling edges: %d\n", edgeupcounter, edgedowncounter);
    }
    return 0;
}