"""
:file: main.py
:author: support@redisage.com
:brief: Hello World example for ESP32 Open IoT and IIoT Gateway 
:copyright: 2024 Redisage Electronics - all rights reserved
"""

import time
import machine
import esp
import gc

print('Hello world!\n')

flash_size = esp.flash_size() / (1024 * 1024)
print(f'{flash_size} MB of flash\n')
heap_size = gc.mem_free()
print(f'Minimum free heap size: {heap_size} bytes\n')

for i in range(10, 0, -1):
    print(f'Restarting in {i} seconds...')
    time.sleep(1)

print('Restarting now\n')
machine.reset()