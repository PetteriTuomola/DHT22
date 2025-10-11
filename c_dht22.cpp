#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

static int edgecounter;
static long long int timedata[90];
static int index;

static void cb_both(WPIWfiStatus status, void* userdata) {
    edgecounter++;
    timedata[index] = status.timeStamp_us;
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

        sleep(2);
        int bytes[5] = {0, 0, 0, 0, 0};
        int offset = 4
        if (timedata[2] - timedata[1] < 40) offset++; // Sometimes it detects the first up, this corrects for that
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 8; j++) {
                int time_diff = timedata[offset + j + i * 8 + 1] - timedata[offset + j + i * 8];
                if (time_diff > 45) bytes[i] += pow(2, i);
            }
        }
        if ((bytes[0] + bytes[1] + bytes[2] + bytes[3]) & 0xFF != bytes[4]) {
            printf("Checksum error\n");
            continue;
        }
        float humidity = ((bytes[0] * 256) + bytes[1]) * 0.1;
        float temperature = ((bytes[2] * 256) + bytes[3]) * 0.1;
        printf("Humidity: %.1f %%\n", humidity);
        printf("Temperature: %.1f C\n", temperature);
        printf("Edge count: %d\n", edgecounter);
        sleep(1);
    }
    return 0;
}