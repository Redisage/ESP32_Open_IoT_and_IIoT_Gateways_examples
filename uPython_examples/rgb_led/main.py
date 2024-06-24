"""
:file: main.py
:author: support@redisage.com
:brief: RGB LED example for ESP32 Open IoT and IIoT Gateway 
:copyright: 2024 Redisage Electronics - all rights reserved
"""

import machine
import time

CLK_GPIO = 33
DATA_GPIO = 4

HW_REVISION = 4 # hardware version

if HW_REVISION >= 3:
    LATCH_GPIO = 15
else:
    LATCH_GPIO = 13

print('initializing...')

clk = machine.Pin(CLK_GPIO, machine.Pin.OUT, value=0)
data = machine.Pin(DATA_GPIO, machine.Pin.OUT, value=0)
latch = machine.Pin(LATCH_GPIO, machine.Pin.OUT, value=1)

print('init done\n')


# RGB LED is controlled via 74HC595BQ shift register
def shift_reg_write_byte(byte):
    latch.off()

    # feed storage register
    for i in range(8):
        if byte & (1 << (7 - i)) == 0:
            data.off()
        else:
            data.on()
    
        clk.on()
        clk.off()

    latch.on() # push data to output


# change LED colors
while True:
    print('led red')
    shift_reg_write_byte(0b01000000)
    time.sleep(1);

    print('led green')
    shift_reg_write_byte(0b00010000)
    time.sleep(1)

    print('led blue\n')
    shift_reg_write_byte(0b00100000)
    time.sleep(1)