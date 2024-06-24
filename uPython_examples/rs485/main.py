"""
:file: main.py
:author: support@redisage.com
:brief: RS485 example for ESP32 Open IoT and IIoT Gateway
:copyright: 2024 Redisage Electronics - all rights reserved
"""

from machine import UART
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

rts0 = machine.Pin(14, machine.Pin.OUT, value=0)
rts1 = machine.Pin(12, machine.Pin.OUT, value=0)

uart0 = UART(1, 115200, bits=8, parity=None, stop=1, tx=32, rx=35, rxbuf=2048, timeout=10)
uart1 = UART(2, 115200, bits=8, parity=None, stop=1, tx=5, rx=37, rxbuf=2048, timeout=10)

termination_state = 0

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


# line termination is set via 74HC595BQ shift register
def set_line_termination(com_num, termination_enable):
    global termination_state

    shift = 0;

    if com_num == 0:
        shift = 7; # Q7
    elif com_num == 1:
        shift = 3; # Q3
    else:
        print('wrong COM number')
        return

    if termination_enable == False:
        termination_state &= ~(1 << shift) # set 0
    else:
        termination_state |= (1 << shift) # set 1

    shift_reg_write_byte(termination_state)


set_line_termination(0, False) # False - termination disabled; True - termination enabled
set_line_termination(1, False) # False - termination disabled; True - termination enabled

# test string to send
test_string = 'test RS485 communication'
test_string_len = len(test_string)

while True:
    # send from RS485 1 to RS485 2
    rts0.on()
    rts1.off()
    uart0.write(test_string)
    uart0.flush()
    buf1 = uart1.read(test_string_len)

    # send from RS485 2 to RS485 1
    rts0.off()
    rts1.on()
    uart1.write(test_string)
    uart1.flush()
    buf0 = uart0.read(test_string_len)
    
    if buf0 != None:
        buf0 = buf0.decode()
        print(f'received on RS485 1 string: {buf0}')
    else:
        print('reading from RS485 1 error')
    
    if buf1 != None:
        buf1 = buf1.decode()
        print(f'received on RS485 2 string: {buf1}')
    else:
        print('reading from RS485 2 error')
        
    print() # new line
    
    time.sleep(1)
    
