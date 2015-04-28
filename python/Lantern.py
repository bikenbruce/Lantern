from serial import Serial
from xbee import ZigBee
from glob import glob

class XbeePole:
	def __init__(self):
		self.pole = 0
		self.long = 0
		self.short = 0
		self.status = -1
		self.last_attempt = 0
		self.name = ""

class XbeePoleControl:
	def __init__(self):
		self.long = {
			0: "\x00\x00\x00\x00\x00\x00\xFF\xFE",
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

		self.short = {
			0: "",
			1: "",
			2: "",
			3: "",
			4: "",
			5: "",
			6: "",
			7: "",
			8: "",
			9: ""
		}
		self.status = 0
		self.last_time_check = 0

		# setup USB port with xbee on it.
		usb_ports = glob("/dev/tty.usbserial-*")
		if len(usb_ports) == 1:
			self.usb_port = usb_ports[0]
		elif len(usb_ports) == 0:
			print "no usb devices found. usb port not set."
		elif len(usb_ports) > 1:
			print "many usb devices found. usb port not set."

		self.baud = 115200

	def open(self):
		self.serial = Serial(self.usb_port, self.baud)
		self.xbee   = ZigBee(self.serial, escaped=True)

	def close(self):
		self.serial.close()

	def send(self, destination, message):
		if len(self.short[destination]) == 0:
			print 'first message to pole ' + str(destination) + '.'
			self.xbee.send("tx", data=message, dest_addr_long=self.long[destination], dest_addr="\xff\xfe")

		else:
			print 'second message to pole ' + str(destination) + '.'
			self.xbee.send("tx", data=message, dest_addr_long=self.long[destination], dest_addr=self.short[destination])
			
		response = self.xbee.wait_read_frame()
		# print response

		if response['id'] == 'rx':
		 	print 'rx packet received.'
		
		if response['id'] == 'tx_status' and len(self.short[destination]) == 0:
			self.short[destination] = response["dest_addr"]

		if response['id'] == 'tx_status':
			if response['discover_status'] == '\x01':
				print 'communication not received by pole ' + str(destination) + '.' # False / failed
		
			elif response['discover_status'] == '\x00':
				print 'commuincation received by pole ' + str(destination) + '.' # True / success



	def read(self):
		response = self.xbee.wait_read_frame()
		print response


# Broadcast event received by python example:
# {'source_addr_long': '\x00\x13\xa2\x00@\x91@\x18', 'rf_data': '\x0e\x01\xff', 'source_addr': '\x9e\xc5', 'id': 'rx', 'options': '\x02'}