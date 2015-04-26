from Lantern import XbeePoleControl
from time import sleep
from numpy import random

# sleep(0.50)

control = XbeePoleControl()
control.open()

try:
	while True:
		control.read()
except KeyboardInterrupt:
	pass

control.close()

