#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

static int edgecounter;
static long long int timedata[90];
static int index;

static void cb_both(WPIWfiStatus status, void* userdata) {
    edgecounter++;
    timedata[index] = status.timeStamp_um;
    index++;
}


int main() {
    int pin = 3; // GPIO pin number
    wiringPiSetupPinType(WPI_PIN_PHYS);
    wiringPiISR2(pin, INT_EDGE_BOTH, &cb_both, 0, NULL);
    for (int i = 0; i < 100; i++) {
        edgecounter = 0;
        index = 0;
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 0);
        usleep(2000);
        pinMode(pin, INPUT);
        pullUpDnControl(pin, PUD_UP);

        sleep(3);
        for (int j = 0; j < 89; j++) {
            std::cout << timedata[j + 1] - timedata[j] << ", ";
        }
        printf("\n");
        printf("Edge count: %d\n", edgecounter);
    }
    return 0;
}