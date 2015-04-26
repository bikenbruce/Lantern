from Lantern import XbeePoleControl
from time import sleep
from numpy import random

# sleep(0.50)

control = XbeePoleControl()
control.open()

control.send(0, "\xFF")

control.close()

