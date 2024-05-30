from machine import Pin, PWM
import utime
from time import sleep

pwm = PWM(Pin(1))
pwm.freq(50)


trigger = Pin(3, Pin.OUT)
echo = Pin(2, Pin.IN)

def ultra():
   trigger.low()
   utime.sleep_us(2)
   trigger.high()
   utime.sleep_us(5)
   trigger.low()
   while echo.value() == 0:
       signaloff = utime.ticks_us()
   while echo.value() == 1:
       signalon = utime.ticks_us()
   timepassed = signalon - signaloff
   distance = (timepassed * 0.0343) / 2
   print("The distance from object is ",distance,"cm")
   return distance

while True:
   dis = ultra()
   utime.sleep(1)
   if dis < 10:
       for position in range(1000,9000,50):
           pwm.duty_u16(position)
           sleep(0.01)
       for position in range(9000,1000,10):
           pwm.duty_u16(position)
           sleep(0.01)
   if dis >= 10:
       for position in range(9000,1000,-50):
           pwm.duty_u16(position)
           sleep(0.01)
    
       