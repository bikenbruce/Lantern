from Lantern import XbeePoleControl

lantern = XbeePoleControl()
lantern.open()
lantern.send(1, "\x00")
lantern.send(1, "\x01")
lantern.send(2, "\x00")
lantern.send(2, "\x01")
lantern.send(3, "\x00")
lantern.send(3, "\x01")
lantern.send(4, "\x00")
lantern.send(4, "\x01")
lantern.send(5, "\x00")
lantern.send(5, "\x01")
lantern.send(9, "\x01")
lantern.send(9, "\x01")
lantern.close()

