import serial
from xbee import ZigBee
import time

from Lantern import XbeePoleControl

control = XbeePoleControl()
control.open()

control.send(4, "\x1F")

control.close()
