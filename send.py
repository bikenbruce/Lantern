import serial
from xbee import ZigBee
import time
import argparse

# SJSU Controller
# PORT = PORT='/dev/tty.usbserial-A600eIdg'

# Steve's Controller
PORT = PORT='/dev/tty.usbserial-A600eIcJ'
BAUD_RATE = 9600

ser = serial.Serial(PORT, BAUD_RATE)
xbee = ZigBee(ser,escaped=True)

POLE1 = "\x00\x13\xA2\x00\x40\x8D\x9E\x0E"
POLE2 = "\x00\x13\xA2\x00\x40\x91\x40\xB6"
POLE3 = "\x00\x13\xA2\x00\x40\x91\x40\x18"
POLE4 = "\x00\x13\xA2\x00\x40\x8D\x9E\x5F"
POLE5 = "\x00\x13\xA2\x00\x40\x91\x40\xB1"
POLE6 = "\x00\x13\xA2\x00"
POLE7 = "\x00\x13\xA2\x00"
POLE8 = "\x00\x13\xA2\x00"

xbee.send("tx",data="\xff", dest_addr_long=POLE1, dest_addr="\xff\xfe")
response = xbee.wait_read_frame()
shot_addr = response["dest_addr"]

xbee.send("tx",data="\x1e\x01\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()

xbee.send("tx",data="\x1e\x02\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()

xbee.send("tx",data="\x1e\x03\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()

xbee.send("tx",data="\x1e\x04\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()

xbee.send("tx",data="\x1e\x05\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()

xbee.send("tx",data="\x1e\x06\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()

xbee.send("tx",data="\x1e\x07\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()

xbee.send("tx",data="\x1e\x08\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()

xbee.send("tx",data="\x1e\x09\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()

xbee.send("tx",data="\x1e\x0a\x01\xff", dest_addr_long=POLE1, dest_addr=shot_addr)
response = xbee.wait_read_frame()
    
ser.close()
