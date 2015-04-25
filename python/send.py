from Lantern import XbeePoleControl

lantern = XbeePoleControl()
lantern.open()
lantern.send(4, "\x00")
lantern.send(4, "\x01")
lantern.close()

