import serial
from xbee import ZigBee
import time

# SJSU Controller
# PORT='/dev/tty.usbserial-A600eIdg'

# Steve's Controller
PORT='/dev/tty.usbserial-A600eIcJ'
BAUD_RATE = 115200

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

xbee.send("tx",data="\xff", dest_addr_long=POLE3, dest_addr="\xff\xfe")
response = xbee.wait_read_frame()
shot_addr = response["dest_addr"]
print response

xbee.send("tx",data="\x20", dest_addr_long=POLE3, dest_addr=shot_addr)
response = xbee.wait_read_frame()
print response

ser.close()
