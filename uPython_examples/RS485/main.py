from machine import UART
import machine
import time

Receiver = UART(1, 115200)
Receiver.init(115200, bits=8, parity=None, stop=1, tx=32, rx=35)
RTS_RCV_pin = machine.Pin(14, machine.Pin.OUT)
RTS_RCV_pin.off()

Sender = UART(2, 115200)
Sender.init(115200, bits=8, parity=None, stop=1, tx=5, rx=37)
RTS_SDR_pin = machine.Pin(12, machine.Pin.OUT)
RTS_SDR_pin.on() 

while(True):
    Sender.write('0x23')
    time.sleep_ms(200)
    buf = Receiver.read();
    print('buf = ', buf)
    
    time.sleep(1)
    
