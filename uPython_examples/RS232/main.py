from machine import UART
import time

Receiver = UART(1, 115200)
Receiver.init(115200, bits=8, parity=None, stop=1, tx=32, rx=35)

Sender = UART(2, 115200)
Sender.init(115200, bits=8, parity=None, stop=1, tx=5, rx=37)

while(True):
    Sender.write('0x23')
    time.sleep_ms(200)
    buf = Receiver.read();
    print('buf = ', buf)
    
    time.sleep(1)
    