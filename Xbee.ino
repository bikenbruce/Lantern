XBee xbee = XBee();

XBeeAddress64 poleAddress[12];

ZBTxStatusResponse txStatus = ZBTxStatusResponse();
ZBRxResponse rx = ZBRxResponse();

void setupXbee() {
  Serial3.begin(115200);
  xbee.setSerial(Serial3);

  poleAddress[0] = XBeeAddress64(0x00000000, 0x0000ffff);  // broadcast
  poleAddress[1] = XBeeAddress64(0x0013a200, 0x408d9e0e);  // pole 1
  poleAddress[2] = XBeeAddress64(0x0013a200, 0x409140b6);  // pole 2
  poleAddress[3] = XBeeAddress64(0x0013a200, 0x40914018);  // pole 3
  poleAddress[4] = XBeeAddress64(0x0013a200, 0x408d9e5f);  // pole 4
  poleAddress[5] = XBeeAddress64(0x0013a200, 0x40c91adf);  // pole 5
  poleAddress[6] = XBeeAddress64(0x0013a200, 0x40d61a48);  // pole 6
  poleAddress[7] = XBeeAddress64(0x0013a200, 0x40c91ae4);  // pole 7
  poleAddress[8] = XBeeAddress64(0x0013a200, 0x40c5f951);  // pole 8
  poleAddress[9] = XBeeAddress64(0x0013a200, 0x408cdb45);  // pole 9
  poleAddress[10] = XBeeAddress64(0x0013a200, 0x407054ac);  // coordinator @ steve's house
  poleAddress[11] = XBeeAddress64(0x0013a200, 0x408CDB42);  // coordinator @ SJSU
  // XBeeAddress64 pole9address = XBeeAddress64(0x0013a200, 0x408cdb45);  // pole 9 (test at SJSU)

}

void sendXbeePushButtonEvent(int poleDestination, int velocity) {
  uint8_t buttonPressed[] = {13, POLE, velocity};
  ZBTxRequest msgToPole = ZBTxRequest(poleAddress[poleDestination], buttonPressed, sizeof(buttonPressed));
  sendXbee(msgToPole, poleDestination);
}

void sendXbee(ZBTxRequest msgToPole, int poleDestination) {
 xbee.send(msgToPole);
 Serial.print("Message sent to pole ");
 Serial.print(poleDestination);
 Serial.println(".");
 
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
    Serial.println("message available.");
    
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

          // Trigger the green animation downward.
          gRateChange = 1;
          break;

        case 14:
          Serial.print("event 14 received from pole ");
          Serial.print(rx.getData(1));
          break;

        case 15:
          Serial.print("Color Array received from pole ");
          Serial.println(rx.getData(1));
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
