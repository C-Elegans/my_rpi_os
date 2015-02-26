#!/usr/bin/python
import serial

from cStringIO import StringIO
from xmodem import XMODEM, NAK
from time import sleep
import sys

def readUntil(char = None):
    def serialPortReader():
        while True:
            tmp = port.read(1)
            if not tmp or (char and char == tmp):
                break
            yield tmp
    return ''.join(serialPortReader())

def getc(size, timeout=1):
    x= port.read(size)
    print x
    return x

def putc(data, timeout=1):
    port.write(data)
    sleep(0.001)

stream = open(sys.argv[1], 'rb')
port = serial.Serial(port="/dev/tty.usbserial-FTXLR71L", parity=serial.PARITY_NONE, bytesize=serial.EIGHTBITS, stopbits=serial.STOPBITS_ONE,timeout=0,xonxoff=0,rtscts=0,dsrdtr=0,baudrate=115200)
xmod = XMODEM(getc,putc)
xmod.send(stream)
sleep(5)
port.write('g')
print port.read()
