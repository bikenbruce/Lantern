from Lantern import XbeePoleControl

control = XbeePoleControl()
control.open()

control.send(0, "\x0D\x00\xFF")

control.close()