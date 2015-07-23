from Lantern import XbeePoleControl
from time import sleep

control = XbeePoleControl()
control.open()

control.send(0, "\x0D\x00\xFF")

control.close()