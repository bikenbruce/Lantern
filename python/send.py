from Lantern import Open, Close, Pole

xbee = Open()


xbee.send("tx",data="\xff", dest_addr_long=Pole(9), dest_addr="\xff\xfe")
response = xbee.wait_read_frame()
shot_addr = response["dest_addr"]

xbee.send("tx",data="\x1e\x01\x01\xff", dest_addr_long=Pole(9), dest_addr=shot_addr)
response = xbee.wait_read_frame()

# xbee.send("tx",data="\x1e\x02\x01\xff", dest_addr_long=Pole(1), dest_addr=shot_addr)
# response = xbee.wait_read_frame()

# xbee.send("tx",data="\x1e\x03\x01\xff", dest_addr_long=Pole(1), dest_addr=shot_addr)
# response = xbee.wait_read_frame()

# xbee.send("tx",data="\x1e\x04\x01\xff", dest_addr_long=Pole(1), dest_addr=shot_addr)
# response = xbee.wait_read_frame()

# xbee.send("tx",data="\x1e\x05\x01\xff", dest_addr_long=Pole(1), dest_addr=shot_addr)
# response = xbee.wait_read_frame()

# xbee.send("tx",data="\x1e\x06\x01\xff", dest_addr_long=Pole(1), dest_addr=shot_addr)
# response = xbee.wait_read_frame()

# xbee.send("tx",data="\x1e\x07\x01\xff", dest_addr_long=Pole(1), dest_addr=shot_addr)
# response = xbee.wait_read_frame()

# xbee.send("tx",data="\x1e\x08\x01\xff", dest_addr_long=Pole(1), dest_addr=shot_addr)
# response = xbee.wait_read_frame()

# xbee.send("tx",data="\x1e\x09\x01\xff", dest_addr_long=Pole(1), dest_addr=shot_addr)
# response = xbee.wait_read_frame()

# xbee.send("tx",data="\x1e\x0a\x01\xff", dest_addr_long=Pole(1), dest_addr=shot_addr)
# response = xbee.wait_read_frame()
    
Close()
