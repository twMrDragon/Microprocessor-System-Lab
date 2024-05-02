import Jetson.GPIO as GPIO
import time

#
SPICLK = 11
SPIMISO = 9
SPIMOSI = 10
SPICS = 8
output_pin = 17
output_pin_2 = 27
# photo resistor connected to adc #0
photo_cp = 0

# port init
def init():
    # BCM for I2C
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(SPIMOSI, GPIO.OUT)
    GPIO.setup(SPIMISO, GPIO.IN)
    GPIO.setup(SPICLK, GPIO.OUT)
    GPIO.setup(SPICS, GPIO.OUT)
    GPIO.setup(output_pin, GPIO.OUT, initial=GPIO.HIGH)
    GPIO.setup(output_pin_2, GPIO.OUT, initial=GPIO.HIGH)
    

def readadc(adcnum, clockpin, mosipin, misopin, cspin):
    if adcnum > 7 or adcnum < 0:
        return -1
    GPIO.output(cspin, True)
    GPIO.output(clockpin, False)
    GPIO.output(cspin, False)

    commandout = adcnum
    commandout |= 0x18
    commandout <<= 3
    for _ in range(5):
        if commandout & 0x80:
            GPIO.output(mosipin, True)
        else:
            GPIO.output(mosipin, False)
        
        commandout <<= 1
        GPIO.output(clockpin,True)
        GPIO.output(clockpin,False)

    adcout = 0
    for _ in range(12):
        GPIO.output(clockpin,True)
        GPIO.output(clockpin,False)
        adcout <<= 1
        if GPIO.input(misopin):
            adcout|=0x1
    GPIO.output(cspin,True)

    adcout >>=1
    return adcout


def main():
    init()
    while True:
        adc_value = readadc(photo_cp, SPICLK, SPIMOSI,SPIMISO,SPICS)
        print(f"adc_value= {adc_value}")

        # led 1
        if adc_value>500:
            GPIO.output(output_pin,GPIO.LOW)
            print("LED1 on")
        else:
            GPIO.output(output_pin,GPIO.HIGH)
            print("LED1 off")
        # led 2
        if adc_value>900:
            GPIO.output(output_pin_2,GPIO.LOW)
            print("LED2 on")
        else:
            GPIO.output(output_pin_2,GPIO.HIGH)
            print("LED2 off")
        
        time.sleep(1)


if __name__ == "__main__":
    try:
        main()
    except:
        print("main error")
