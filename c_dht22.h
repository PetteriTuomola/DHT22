// c_dht22.h
// header guards
#pragma once
#include <wiringPi.h>

// declaring functions
static void cb_both(WPIWfiStatus status, void* userdata);
extern "C" void measure();