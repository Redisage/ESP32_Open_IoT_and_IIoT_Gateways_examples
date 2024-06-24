"""
:file: main.py
:author: support@redisage.com
:brief: WiFi example for ESP32 Open IoT and IIoT Gateway
:copyright: 2024 Redisage Electronics - all rights reserved
"""

import network
import machine

# set the Ethernet interface
lan = network.LAN(mdc=machine.Pin(23), mdio=machine.Pin(18),
                  reset=None, power=None,
                  phy_type=network.PHY_IP101, phy_addr=1,
                  ref_clk=machine.Pin(0), ref_clk_mode=machine.Pin.OUT)

lan.active(False)
lan.active(True) # activate the interface

if not lan.isconnected():
    print('connecting to ethernet...')
    while not lan.isconnected():
        pass

print('ethernet connected')
print('network config:', lan.ifconfig())

# idle loop
while True:
    pass