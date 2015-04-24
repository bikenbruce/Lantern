import serial
from xbee import ZigBee

poles = {1: "\x00\x13\xA2\x00\x40\x8D\x9E\x0E",
	2: "\x00\x13\xA2\x00\x40\x91\x40\xB6",
	3: "\x00\x13\xA2\x00\x40\x91\x40\x18",
	4: "\x00\x13\xA2\x00\x40\x8D\x9E\x5F",
	5: "\x00\x13\xA2\x00\x40\x91\x40\xB1",
	6: "\x00\x13\xA2\x00",
	7: "\x00\x13\xA2\x00",
	8: "\x00\x13\xA2\x00",
	9: "\x00\x13\xA2\x00\x40\x8C\xDB\x45"
}

def Open():
	# SJSU Controller
	PORT='/dev/tty.usbserial-A600eIdg'

	# Steve's Controller
	# PORT='/dev/tty.usbserial-A600eIcJ'
	BAUD_RATE = 115200

	ser = serial.Serial(PORT, BAUD_RATE)
	xbee = ZigBee(ser,escaped=True)

	return(xbee)

def Close():
	ser.close()

def Pole(number):
	return poles[number]