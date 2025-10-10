import RPi.GPIO as GPIO
import dht22
import time
import datetime

# initialize GPIO
GPIO.setwarnings(True)
GPIO.setmode(GPIO.BOARD)

# read data using pin 7
instance = dht22.DHT22(pin=7)

try:
	while True:
		result = instance.read()
		if result.is_valid():
			print("Last valid input: " + str(datetime.datetime.now()))
			print("Temperature: %-3.1f C" % result.temperature)
			print("Humidity: %-3.1f %%" % result.humidity)
		else:
			print("Non-valid input.")
		time.sleep(2)

except KeyboardInterrupt:
    print("\nCleanup")
    GPIO.cleanup()