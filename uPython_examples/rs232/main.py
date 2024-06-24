"""
:file: main.py
:author: support@redisage.com
:brief: RS232 example for ESP32 Open IoT and IIoT Gateway
:copyright 2024 Redisage Electronics - all rights reserved
"""

from machine import UART
import time

# configure UART ports
uart0 = UART(1, 115200, bits=8, parity=None, stop=1, tx=32, rx=35, rxbuf=2048, timeout=10)
uart1 = UART(2, 115200, bits=8, parity=None, stop=1, tx=5, rx=37, rxbuf=2048, timeout=10)

# test string to send
test_string = 'test RS232 communication'
test_string_len = len(test_string)

while True:
    # send through RS232
    uart0.write(test_string)
    uart0.flush()
    uart1.write(test_string)
    uart1.flush()

    # read from RS232
    buf0 = uart0.read(test_string_len)
    buf1 = uart1.read(test_string_len)

    if buf0 != None:
        buf0 = buf0.decode()
        print(f'received on RS232 1 string: {buf0}')
    else:
        print('reading from RS232 1 error')
    
    if buf1 != None:
        buf1 = buf1.decode()
        print(f'received on RS232 2 string: {buf1}')
    else:
        print('reading from RS232 2 error')
        
    print() # new line
    
    time.sleep(1)