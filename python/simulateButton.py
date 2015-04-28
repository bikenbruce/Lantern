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
		# print 'sleeping for ' + str(sleep_time)
		sleep(sleep_time)
		control.send(9, "\x0D\x01\xFF")

		sleep_time = random.uniform(0.2, 0.9)
		# print 'sleeping for ' + str(sleep_time)
		sleep(sleep_time)
		control.send(9, "\x0D\x01\xFF")

		sleep_time = random.uniform(0.3, 0.9)
		# print 'sleeping for ' + str(sleep_time)
		sleep(sleep_time)
		control.send(9, "\x0D\x01\xFF")

		sleep_time = random.uniform(0.2, 0.9)
		# print 'sleeping for ' + str(sleep_time)
		sleep(sleep_time)
		control.send(9, "\x0D\x01\xFF")

		sleep_time = random.uniform(4.2, 8.5)
		print '\nsleeping for ' + str(sleep_time)
		sleep(sleep_time)
except KeyboardInterrupt:
	pass

control.close()

