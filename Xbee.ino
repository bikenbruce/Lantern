XBee xbee = XBee();

PoleComm pole[12];

ZBTxStatusResponse txStatus = ZBTxStatusResponse();
ZBRxResponse rx = ZBRxResponse();

int dataNum;

void setupXbee() {
  //Serial3.begin(57600);
  Serial3.begin(57600);
  xbee.setSerial(Serial3);

  pole[0].address = XBeeAddress64(0x00000000, 0x0000ffff);  // broadcast
  pole[1].address = XBeeAddress64(0x0013a200, 0x408d9e0e);  // pole 1
  pole[2].address = XBeeAddress64(0x0013a200, 0x409140b6);  // pole 2
  pole[3].address = XBeeAddress64(0x0013a200, 0x40914018);  // pole 3
  pole[4].address = XBeeAddress64(0x0013a200, 0x408d9e5f);  // pole 4
  pole[5].address = XBeeAddress64(0x0013a200, 0x40c91adf);  // pole 5
  pole[6].address = XBeeAddress64(0x0013a200, 0x40d61a48);  // pole 6
  pole[7].address = XBeeAddress64(0x0013a200, 0x40c91ae4);  // pole 7
  pole[8].address = XBeeAddress64(0x0013a200, 0x40c5f951);  // pole 8
  pole[9].address = XBeeAddress64(0x0013a200, 0x408cdb45);  // pole 9
  pole[10].address = XBeeAddress64(0x0013a200, 0x408CDB42);  // coordinator

  // poleAddress[11] = XBeeAddress64(0x0013a200, 0x407054ac);  // extra unit now.....
  // poleAddress[12] = XBeeAddress64(0x0013a200, 0x408cdb45);  // pole 9 (test at SJSU)

  // To Do:
  // Need to confirm xbee setup with Poles / Lanterns 1 through 3 with the coordinator.

  // Initialize xbees by testing network to each one

}

void sendXbeeHello(int poleDestination) {
  uint8_t message[] = {0, POLE};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}

void sendXbeeHelloReply(int poleDestination, int status) {
  uint8_t message[] = {1, POLE, status};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}

void sendXbeePushButtonEvent(int poleDestination, int velocity) {
  uint8_t message[] = {13, POLE, velocity};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}

void sendXbeeButtonOnEvent(int poleDestination, int velocity) {
  uint8_t message[] = {16, POLE, velocity};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}

void sendXbeeButtonOffEvent(int poleDestination) {
  uint8_t message[] = {17, POLE};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}

void sendXbeeLongColorTest(int poleDestination) {
  uint8_t message[31];
  message[0] = 77;

  for (int i = 1; i < 31; i++) {
    message[i] = random(0,10);

  }

  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);

}

void sendXbeeAllOff(int poleDestination) {
  uint8_t buttonPressed[] = {31, POLE};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, buttonPressed, sizeof(buttonPressed));
  sendXbee(msgToPole, poleDestination);

}

void sendXbee(ZBTxRequest msgToPole, int poleDestination) {
  xbee.send(msgToPole);
  Serial.print("Message sent to pole ");
  Serial.println(poleDestination);

  //Not srue what the digit is for.
  if (xbee.readPacket(500)) {
  // got a response!
    if (xbee.getResponse().isAvailable()) {
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
      } else if (xbee.getResponse().isError()) {
        Serial.print("Error reading packet.  Error code: ");  
        Serial.println(xbee.getResponse().getErrorCode());

      }
    }
  }
}

int readXbee() {

  xbee.readPacket();

  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {

    if (xbee.getResponse().isAvailable()) {

      Serial.println("Data is available.");
      
      // fill out zb rx class
      xbee.getResponse().getZBRxResponse(rx);
      
      Serial.println("message received.");

      Serial.print("length: ");
      Serial.println(rx.getDataLength());

      switch (rx.getData(0)) {
        case 0:
          // hello, are you here?
          Serial.print("0");
          Serial.print(" Hello / Basic Status Request Received ");
          Serial.println(rx.getData(1));

          sendXbeeHelloReply(rx.getData(1), 1);

          break;

        case 1:
          // set time and return new time
          Serial.print("1");
          Serial.print(" Hello / Basic Status Received ");
          if (rx.getData(1) == 1) {
            Serial.println("Good");
          } else {
            Serial.println("Bad");
          }
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
          Serial.print("13 push button event received from pole ");
          Serial.print(rx.getData(1));
          Serial.print(" with velocity of ");
          Serial.println(rx.getData(2));

          // Trigger the green animation downward.
          gRateChange = 1;
          break;

        case 14:
          Serial.print("14");
          break;

        case 15:
          Serial.print("15 Color Array received from pole ");
          Serial.println(rx.getData(1));

          RGB colorArray[10];
          for (int i = 0; i < 10; i++) {
            colorArray[i].r = 10;
            colorArray[i].g = 10;
            colorArray[i].b = 10;
          }

          DrawArray(colorArray);
          break;

        case 16:
          Serial.print("16 button on received from pole ");
          Serial.println(rx.getData(1));
          if (rx.getData(1) == 6) {
            b[5] = 10;
          } else if (rx.getData(1) == 7) {
            b[6] = 10;
          } else if (rx.getData(1) == 8) {
            b[7] = 10;
          }
          
          break;

        case 17:
          Serial.print("17 button off received from pole ");
          Serial.println(rx.getData(1));
          if (rx.getData(1) == 6) {
            b[5] = 0;
          } else if (rx.getData(1) == 7) {
            b[6] = 0;
          } else if (rx.getData(1) == 8) {
            b[7] = 0;
          }

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
          Serial.println("31 All Off.");
          allOff();

          for (int i = 0; i < 10; i++) {
            r[i] = 0;
            g[i] = 0;
            b[i] = 0;

          }
          break;

        case 32:
          Serial.println("33");
          // off on
          allOn();
          break;

        case 77:
          Serial.println("77 Full Color Test");

          dataNum = 1;
          for (int i = 0; i < 10; i++) {
            r[i] = rx.getData(dataNum);
            dataNum += 1;
            g[i] = rx.getData(dataNum);
            dataNum += 1;
            b[i] = rx.getData(dataNum);
            dataNum += 1;
 
          }
          break;

        default:
          Serial.print("Nothing set for this value, which is ");
          Serial.println(rx.getData(0));
          // Oups!
      }
    } else if (xbee.getResponse().isError()) {
      Serial.println("");
      Serial.print("Error reading packet.  Error code: "); 
      Serial.print(xbee.getResponse().getErrorCode()); 
      if (xbee.getResponse().getErrorCode() == CHECKSUM_FAILURE) {
        Serial.println(" Checksum Failure.");        
      } else if (xbee.getResponse().getErrorCode() == UNEXPECTED_START_BYTE) {
        Serial.println(" Unexpected start byte.");
      }
      
      Serial.println("");

    }
  }
}
