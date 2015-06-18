from Lantern import XbeePoleControl
from time import sleep
from numpy import random

# sleep(0.50)

control = XbeePoleControl()
control.open()

control.send(7, "\x00\xFF")
control.send(7, "\x0E\x01\xFF")

control.close()

