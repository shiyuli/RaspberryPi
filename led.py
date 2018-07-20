from gpiozero import LED
from time import sleep

def setup():
    global led
    led = LED(17)

def run():
    while True:
        led.on()
        sleep(1)
        led.off()
        sleep(1)

if __name__ == "__main__":
    setup()
    run()
