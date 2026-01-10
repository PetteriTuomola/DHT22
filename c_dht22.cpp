#include <wiringPi.h>
#include <iostream>
#include <cmath>
#include <array>
#include <unistd.h>

static int edgecounter;
static std::array<long long int, 90> timedata; // There are ~85 edges to record


// Define what happens when an edge is detected
static void cb_both(WPIWfiStatus status, void* userdata) {
    timedata[edgecounter] = status.timeStamp_us;
    edgecounter++;
}


int main() {
    int pin = 3; // GPIO pin number
    wiringPiSetupPinType(WPI_PIN_PHYS); // Use physical pin numbering for the Pi
    wiringPiISR2(pin, INT_EDGE_BOTH, &cb_both, 0, NULL); // Set an ISR function on edge detection
    for (int i = 0; i < 100; i++) {
        timedata.fill(0);
        edgecounter = 0;
        pinMode(pin, OUTPUT); // Set the pin as output to send the first master signal
        digitalWrite(pin, 0);
        usleep(2000); // Send LOW that lasts for 2 ms
        pinMode(pin, INPUT);
        pullUpDnControl(pin, PUD_UP); // Switch to input to receive the signal and pull to UP
        sleep(2); // Wait for two seconds, during which the data is received through the edge detection
        int bytes[5] = {0, 0, 0, 0, 0};
        int offset = 4; // The first four edges are the initial set-up signals
        if (timedata[2] - timedata[1] < 40) offset++; // Sometimes it detects the first up, this corrects for that
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 16; j += 2) {
                int time_diff = timedata[offset + j + i * 16 + 1] - timedata[offset + j + i * 16]; // Calculate the pulse length
                if (time_diff > 45) bytes[i] += std::pow(2, 7 - j / 2); // Check if 0 or 1 and convert to base-10
            }
        }
        if ((bytes[0] + bytes[1] + bytes[2] + bytes[3]) % 256 != bytes[4]) { // Check that the data is valid
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
