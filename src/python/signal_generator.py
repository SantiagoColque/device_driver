import RPi.GPIO as GPIO
import time

# Config GPIO PINs
GPIO_PIN1 = 26  
GPIO_PIN2 = 19  

# Config GPIO library
GPIO.setmode(GPIO.BCM)
GPIO.setup(GPIO_PIN1, GPIO.OUT)
GPIO.setup(GPIO_PIN2, GPIO.OUT)

# Function to generate a square signal
def generate_signal(pin, period, duration):
    half_period = period / 2
    end_time = time.time() + duration
    while time.time() < end_time:
        GPIO.output(pin, GPIO.HIGH)
        time.sleep(half_period)
        GPIO.output(pin, GPIO.LOW)
        time.sleep(half_period)

while True:
    signal = input("Select PIN to generate signal (1 or 2) or 0 to exit:")
    if signal == '1':
        generate_signal(GPIO_PIN1, 5, 25)
        continue
    if signal == '2':
        generate_signal(GPIO_PIN2, 10, 50)
        continue
    if signal == '0':
        break

print("Cleaning up GPIO...")
GPIO.cleanup()
