from Lantern import XbeePoleControl
from time import sleep
from numpy import random

# sleep(0.50)

control = XbeePoleControl()
control.open()

# control.send(5, "\x0D\x01\xFF")
control.send(6, "\x0D\x01\xFF")
control.send(7, "\x0D\x01\xFF")
control.send(8, "\x0D\x01\xFF")

control.close()

