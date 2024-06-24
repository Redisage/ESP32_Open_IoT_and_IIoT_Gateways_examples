"""
:file: main.py
:author: support@redisage.com
:brief: Switch example for ESP32 Open IoT and IIoT Gateway
:copyright: 2024 Redisage Electronics - all rights reserved
"""

import machine
import time

SWITCH_GPIO = 34

# init switch gpio
switch = machine.Pin(SWITCH_GPIO, machine.Pin.IN, machine.Pin.PULL_UP)

# interrupt handler
def irq_handler():
    if switch.value() == 1:
        print('switch pressed')
    else:
        print('switch released\n')

# register interrupt
switch.irq(lambda t: irq_handler())

# idle loop
while True:
    pass