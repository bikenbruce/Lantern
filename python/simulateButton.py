from Lantern import XbeePoleControl
from time import sleep
from numpy import random

# sleep(0.50)

control = XbeePoleControl()
control.open()

try:
	while True:
		print '\n'
		sleep_time = random.uniform(0.3, 0.9)
		print 'sleeping for ' + str(sleep_time)
		sleep(sleep_time)
		control.send(4, "\x0D\x00\xFF")

		sleep_time = random.uniform(0.2, 0.9)
		print 'sleeping for ' + str(sleep_time)
		sleep(sleep_time)
		control.send(4, "\x0D\x00\xFF")

		sleep_time = random.uniform(0.3, 0.9)
		print 'sleeping for ' + str(sleep_time)
		sleep(sleep_time)
		control.send(4, "\x0D\x00\xFF")

		sleep_time = random.uniform(0.2, 0.9)
		print 'sleeping for ' + str(sleep_time)
		sleep(sleep_time)
		control.send(4, "\x0D\x00\xFF")

		sleep_time = random.uniform(10.2, 12.5)
		print '\nsleeping for ' + str(sleep_time)
		sleep(sleep_time)
except KeyboardInterrupt:
	pass

control.close()

