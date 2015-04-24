from serial import Serial
from xbee import ZigBee
from glob import glob

class XbeePoleControl:
	def __init__(self, number):
		self.number = number

		self.poles = {
			1: "\x00\x13\xA2\x00\x40\x8D\x9E\x0E",
			2: "\x00\x13\xA2\x00\x40\x91\x40\xB6",
			3: "\x00\x13\xA2\x00\x40\x91\x40\x18",
			4: "\x00\x13\xA2\x00\x40\x8D\x9E\x5F",
			5: "\x00\x13\xA2\x00\x40\x91\x40\xB1",
			6: "\x00\x13\xA2\x00",
			7: "\x00\x13\xA2\x00",
			8: "\x00\x13\xA2\x00",
			9: "\x00\x13\xA2\x00\x40\x8C\xDB\x45"
		}

		# setup USB port with xbee on it.
		usb_ports = glob("/dev/tty.usbserial-*")
		if len(usb_ports) == 1:
			self.usb_port = usb_ports[0]
		elif len(usb_ports) == 0:
			print "no usb devices found. usb port not set."
		elif len(usb_ports) > 1:
			print "many usb devices found. usb port not set."

		self.baud = 115200

		self.mac = self.poles[self.number]
		

	def open(self):
		self.serial = Serial(self.usb_port, self.baud)
		self.xbee   = ZigBee(self.serial, escaped=True)

	def close(self):
		self.serial.close()

