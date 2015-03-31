#define MY_POLE 1

XBee xbee = XBee();

// xbee addresses
XBeeAddress64 coordinator  = XBeeAddress64(0x0013a200, 0x407054ac);  // coordinator
XBeeAddress64 pole1address = XBeeAddress64(0x0013a200, 0x408d9e0e);  // pole 1
XBeeAddress64 pole2address = XBeeAddress64(0x0013a200, 0x409140b6);  // pole 2
XBeeAddress64 pole3address = XBeeAddress64(0x0013a200, 0x40914018);  // pole 3
XBeeAddress64 pole4address = XBeeAddress64(0x0013a200, 0x408d9e5f);  // pole 4
XBeeAddress64 pole5address = XBeeAddress64(0x0013a200, 0x409140b1);  // pole 5 - is this really pole 5?
// XBeeAddress64 pole5address = XBeeAddress64(0x0013a200, 0x409140b1);  // pole 6
// XBeeAddress64 pole5address = XBeeAddress64(0x0013a200, 0x409140b1);  // pole 7
// XBeeAddress64 pole5address = XBeeAddress64(0x0013a200, 0x409140b1);  // pole 8

// message / string
uint8_t buttonPressed[] = {MY_POLE, 'b'};

//address with message
extern ZBTxRequest msgToCoordinator = ZBTxRequest(coordinator, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole1       = ZBTxRequest(pole1address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole2       = ZBTxRequest(pole2address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole3       = ZBTxRequest(pole3address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole4       = ZBTxRequest(pole4address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole5       = ZBTxRequest(pole5address, buttonPressed, sizeof(buttonPressed));

ZBTxStatusResponse txStatus = ZBTxStatusResponse();
ZBRxResponse rx = ZBRxResponse();

void setupXbee() {
  Serial3.begin(9600);
  xbee.setSerial(Serial3);
  
}

void sendMessage(ZBTxRequest pole) {
 xbee.send(pole);
 Serial.print("message sent\n"); 
 
 if (xbee.readPacket(500)) {
    // got a response!

    // should be a znet tx status            	
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
        Serial.print("message received\n");
        
      } else {
        // the remote XBee did not receive our packet. is it powered on?
        Serial.print("message not received\n");
        
      }
    }
  }
}

int readXbee() {
  xbee.readPacket();
  
  if (xbee.getResponse().isAvailable()) {
    // got something
    
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      //get a zb rx packet
      
      // fill out zb rx class
      xbee.getResponse().getZBRxResponse(rx);
      
      return 1;
      
      Serial.println(rx.getData(0));
      Serial.println(rx.getData(1));
            
    }
  }
}
