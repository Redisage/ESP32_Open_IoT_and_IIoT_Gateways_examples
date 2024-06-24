"""
:file: main.py
:author: support@redisage.com
:brief: I2C scanner example for ESP32 Open IoT and IIoT Gateway
:copyright: 2024 Redisage Electronics - all rights reserved
"""

from machine import I2C

skip_addr = 0x50

lis3dh_found = False;
si7006_found = False;
eeprom_found = False;
hts221_found = False;
lsm6ds33_found = False;

# configure I2C bus
i2c = I2C(1, scl=2, sda=13, freq=100000, timeout=10000)

print('looking for I2C devices...\n')

# look for I2C devices
i2c_list = i2c.scan()

for device in i2c_list:
    if device == 0x18 or device == 0x19:
        lis3dh_found = True
    elif device == 0x40:
        si7006_found = True
    elif device == 0x54:
        eeprom_found = True
    elif device == 0x5F:
        hts221_found = True
    elif device == 0x6B:
        lsm6ds33_found = True

    print(f'found I2C device: {hex(device)}')
    
print() # new line

# print if devices are present
if lis3dh_found == True:
    print('LIS3DH found')
if si7006_found == True:
    print('Si7006 found')
if eeprom_found == True:
    print('EEPROM found')
if hts221_found == True:
    print('HTS221 found')
if lsm6ds33_found == True:
    print('LSM6DS33 found')