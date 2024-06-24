"""
:file: main.py
:author: support@redisage.com
:brief: ADC example for ESP32 Open IoT and IIoT Gateway
:copyright: 2024 Redisage Electronics - all rights reserved
"""

from machine import ADC
import time

# init ADC
adc = ADC(36, atten=ADC.ATTN_11DB)

while (True):
    val_raw = adc.read_u16() # read a raw analog value in the range 0-65535
    val_mV = adc.read_uv() / 1000 # read an analog value in mV

    print(f'raw reading: {val_raw}, voltage: {val_mV} mV')

    time.sleep_ms(100)