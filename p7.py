#7. Write a python program using Raspberry Pi blink led GPIO  using  SSh
from gpiozero import LED
from signal import pause

led=LED(4)
led.blink()

pause()