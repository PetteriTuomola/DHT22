import RPi.GPIO as GPIO
import dht22
import time
import datetime


def main():
	# initialize GPIO
	GPIO.setwarnings(True)
	GPIO.setmode(GPIO.BOARD)

	# read data using pin 3
	instance = dht22.DHT22(pin=3)
	success = 0
	fail = 0

	while True:
		result = instance.read()
		if result.is_valid():
			print("Last valid input: " + str(datetime.datetime.now()))
			print("Temperature: %-3.1f C" % result.temperature)
			print("Humidity: %-3.1f %%" % result.humidity)
			success += 1
		else:
			fail += 1
		if (success + fail) % 150 == 0:
			print("Success: %d, Fail: %d" % (success, fail))
		time.sleep(4)

main()