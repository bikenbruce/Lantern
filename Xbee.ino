XBee xbee = XBee();

// xbee addresses
XBeeAddress64 broadcast = XBeeAddress64(0x00000000, 0x0000ffff);

XBeeAddress64 coordinatorSD = XBeeAddress64(0x0013a200, 0x407054ac);  // coordinator @ steve's house
XBeeAddress64 coordinatorSJ = XBeeAddress64(0x0013a200, 0x408CDB42);  // coordinator @ SJSU
XBeeAddress64 pole1address = XBeeAddress64(0x0013a200, 0x408d9e0e);  // pole 1
XBeeAddress64 pole2address = XBeeAddress64(0x0013a200, 0x409140b6);  // pole 2
XBeeAddress64 pole3address = XBeeAddress64(0x0013a200, 0x40914018);  // pole 3
XBeeAddress64 pole4address = XBeeAddress64(0x0013a200, 0x408d9e5f);  // pole 4
XBeeAddress64 pole5address = XBeeAddress64(0x0013a200, 0x409140b1);  // pole 5
XBeeAddress64 pole6address = XBeeAddress64(0x0013a200, 0x409140b1);  // pole 6, unknown
XBeeAddress64 pole7address = XBeeAddress64(0x0013a200, 0x409140b1);  // pole 7, unknown
XBeeAddress64 pole8address = XBeeAddress64(0x0013a200, 0x409140b1);  // pole 8, unknown
XBeeAddress64 pole9address = XBeeAddress64(0x0013a200, 0x408cdb45);  // pole 9 (test at SJSU)

// message / string
uint8_t buttonPressed[] = {13, 1, 255};

//address with message
extern ZBTxRequest msgToBroadcast     = ZBTxRequest(broadcast,    buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToCoordinatorSD = ZBTxRequest(coordinatorSD, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToCoordinatorSJ = ZBTxRequest(coordinatorSJ, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole1       = ZBTxRequest(pole1address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole2       = ZBTxRequest(pole2address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole3       = ZBTxRequest(pole3address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole4       = ZBTxRequest(pole4address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole5       = ZBTxRequest(pole5address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole6       = ZBTxRequest(pole6address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole7       = ZBTxRequest(pole7address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole8       = ZBTxRequest(pole8address, buttonPressed, sizeof(buttonPressed));
extern ZBTxRequest msgToPole9       = ZBTxRequest(pole9address, buttonPressed, sizeof(buttonPressed));

ZBTxStatusResponse txStatus = ZBTxStatusResponse();
ZBRxResponse rx = ZBRxResponse();

void setupXbee() {
  Serial3.begin(115200);
  xbee.setSerial(Serial3);

}

//void sendXbee(XBeeAddress64 poleAddress, uint8_t message) {
void sendXbee() {
 //ZBTxRequest msgToPole = ZBTxRequest(coordinatorSJ, msgToCoordinatorSJ, sizeof(msgToCoordinatorSJ));
 xbee.send(msgToCoordinatorSJ);
 Serial.print("message sent\n");
 
 if (xbee.readPacket(500)) {
    // got a response!

    // should be a znet tx status            	
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
        Serial.println("confirmation received.");
        
      } else {
        // the remote XBee did not receive our packet. is it powered on?
        Serial.println("confirmation not received.");
        
      }
    }
  }
}

int readXbee() {
  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {
    
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      
      // fill out zb rx class
      xbee.getResponse().getZBRxResponse(rx);
      
      Serial.println("message received.");

      Serial.print("length: ");
      Serial.println(rx.getDataLength());

      switch (rx.getData(0)) {
        case 0:
          // get time
          Serial.println("0");
          break;

        case 1:
          // set time and return new time
          Serial.println("1");
          break;

        case 2:
          // what is the temperature
          Serial.println("2");
          break;

        case 3:
          // nothing at this point
          Serial.println("3");
          break;

        case 4:
          // what is the start time for day of week?
          Serial.println("4");
          break;

        case 5:
          // what is the stop time for day of week?
          Serial.println("5");
          break;

        case 6:
          // set start time for day of week
          Serial.println("6");
          break;

        case 7:
          // set stop time for day of week
          Serial.println("7");
          break;

        case 8:
          // nothing at this point
          Serial.println("8");
          break;

        case 9:
          // nothing at this point
          Serial.println("9");
          break;

        case 10:
          // nothing at this point
          Serial.println("10");
          break;

        case 11:
          // nothing at this point
          Serial.println("11");
          break;

        case 12:
          // nothing at this point
          Serial.println("12");
          break;

        case 13:
          // push button event
          Serial.print("push button event received from pole ");
          Serial.print(rx.getData(1));
          Serial.print(" with velocity of ");
          Serial.println(rx.getData(2));
          break;

        case 30:
          // Set a Board, R/G/B, Value
          Serial.print("Set Board: ");
          Serial.print(rx.getData(1));
          Serial.print(" Color: ");
          Serial.print(rx.getData(2));
          Serial.print(" Value: ");
          Serial.println(rx.getData(3));

          DmxSimple.write((rx.getData(1) - 1) * 4 + rx.getData(2), rx.getData(3));
          DmxSimple.write(11, 255);
          break;

        case 31:
          // All Off
          allOff();
          break;

        case 32:
          // off on
          allOn();
          break;

        case 77:
          break;
          // bruce test thing.....


        default:
          Serial.print("Nothing set for this value, which is ");
          Serial.println(rx.getData(0));
          // Oups!
      }
    }
  }
}
