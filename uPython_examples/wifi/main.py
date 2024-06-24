"""
:file: main.py
:author: support@redisage.com
:brief: WiFi example for ESP32 Open IoT and IIoT Gateway
:copyright: 2024 Redisage Electronics - all rights reserved
"""

import network

# wifi credentials
ssid = 'ssid'
password = 'password'


# create station
def sta_connect():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('connecting to network...')
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            pass
    
    print('station created')
    print('network config:', wlan.ifconfig())
    

# create access point
def ap_connect():
    ap = network.WLAN(network.AP_IF)
    
    ap.config(ssid=ssid, security=3, key=password)
    """
    security:
    * 0 – open
    * 1 – WEP
    * 2 – WPA-PSK
    * 3 – WPA2-PSK
    * 4 – WPA/WPA2-PSK
    """

    ap.config(max_clients=10)
    ap.active(True)

    while ap.active() == False:
        pass

    print('access point created')
    print('network config:', ap.ifconfig())

    if not ap.isconnected():
        print('waiting for a device to connect...')
        while not ap.isconnected():
            pass
        
    print('device connected to AP')


# choose mode to use
# sta_connect()
ap_connect()
    
# idle loop
while True:
    pass