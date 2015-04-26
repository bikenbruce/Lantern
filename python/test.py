from Lantern import XbeePoleControl
from time import sleep
from numpy import random

# sleep(0.50)

control = XbeePoleControl()
control.open()

control.send(1, "\x00")
control.send(2, "\x00")
control.send(3, "\x00")
control.send(4, "\x00")
control.send(5, "\x00")
control.send(9, "\x00")

control.close()

