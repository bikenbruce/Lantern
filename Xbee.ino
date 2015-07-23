XBee xbee = XBee();
PoleComm pole[12];

StackArray <ReplyBuff> replyStack;

ZBTxStatusResponse txStatus = ZBTxStatusResponse();
ZBRxResponse rx = ZBRxResponse();

int dataNum;

void setupXbee() {
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

}

void sendXbeeStatusRequest(int destination) {
  uint8_t msgNumber = 0;
  uint8_t message[] = {msgNumber, POLE};
  ZBTxRequest zbMessage = ZBTxRequest(pole[destination].address, message, sizeof(message));
  sendXbee(zbMessage, msgNumber, destination);
}

void sendXbeeStatusReply(int destination, int status) {
  uint8_t msgNumber = 1;
  uint8_t message[] = {msgNumber, POLE, status};
  ZBTxRequest zbMessage = ZBTxRequest(pole[destination].address, message, sizeof(message));
  //sendXbee(zbMessage, msgNumber, destination);
  ReplyBuff temp;
  temp.messageNumber = 1;
  temp.destination = destination; 
  replyStack.push(temp);
}

void sendXbeeAllOff(int destination) {
  uint8_t msgNumber = 10;
  uint8_t buttonPressed[] = {msgNumber, POLE};
  ZBTxRequest zbMessage = ZBTxRequest(pole[destination].address, buttonPressed, sizeof(buttonPressed));
  sendXbee(zbMessage, msgNumber, destination);

}

void sendXbeeButtonOnEvent(int destination, int velocity) {
  uint8_t msgNumber = 13;
  uint8_t message[] = {msgNumber, POLE, velocity};
  ZBTxRequest zbMessage = ZBTxRequest(pole[destination].address, message, sizeof(message));
  sendXbee(zbMessage, msgNumber, destination);
}

void sendXbeeButtonOffEvent(int destination) {
  uint8_t msgNumber = 14;
  uint8_t message[] = {msgNumber, POLE};
  ZBTxRequest zbMessage = ZBTxRequest(pole[destination].address, message, sizeof(message));
  sendXbee(zbMessage, msgNumber, destination);
}

void sendXbeeColorArray(int destination) {
  // todo
  uint8_t msgNumber = 15;

}

void sendXbeeSingleRGB(int destination, RGB value) {
  uint8_t msgNumber = 16;
  uint8_t message[] = {msgNumber, value.r, value.g, value.b};
  ZBTxRequest zbMessage = ZBTxRequest(pole[destination].address, message, sizeof(message));
  sendXbee(zbMessage, msgNumber, destination);

}

void sendStack() {
  while(!replyStack.isEmpty()) {
    ReplyBuff temp = replyStack.pop();
    // Serial.print("Message Number ");
    // Serial.print(temp.messageNumber);
    // Serial.print(" Destination ");
    // Serial.println(temp.destination);
    sendXbeeFromStack(temp.messageNumber, temp.destination, 1);
  }
}


void sendXbee(ZBTxRequest zbMessage, uint8_t msgNumber, int destination) {
  xbee.send(zbMessage);
  Serial.print(msgNumber);
  Serial.print(" Message sent to pole ");
  Serial.print(destination);

  //The readPacket Digit is for time out.
  if (xbee.readPacket(500)) {
  // got a response!
    if (xbee.getResponse().isAvailable()) {
      // should be a znet tx status             
      if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
        xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
        if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
          Serial.println("    confirmation received by sendXbee method");

        } else {
          // the remote XBee did not receive our packet. is it powered on?
          Serial.println("    confirmation not received");
        
        }
      } else if (xbee.getResponse().isError()) {
        Serial.print("  error reading packet. code: ");  
        Serial.println(xbee.getResponse().getErrorCode());

      }
    }
  } else {
    Serial.println("  time out. nothing to read.");
  }
}

void sendXbeeFromStack(uint8_t msgNumber, int destination, int status) {
  uint8_t message[] = {msgNumber, POLE, status};
  ZBTxRequest zbMessage = ZBTxRequest(pole[destination].address, message, sizeof(message));

  xbee.send(zbMessage);
  //Serial.print(msgNumber);
  Serial.print("1 Reply message sent to pole from stack ");
  //Serial.println(destination);

  //The readPacket Digit is for time out.
  if (xbee.readPacket(500)) {
  // got a response!
    if (xbee.getResponse().isAvailable()) {
      // should be a znet tx status             
      if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
        xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
        if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
          Serial.println("    confirmation received by sendXbeeFromStack method");

        } else {
          // the remote XBee did not receive our packet. is it powered on?
          Serial.println("    confirmation not received");
        
        }
      } else if (xbee.getResponse().isError()) {
        Serial.print("  error reading packet. code: ");  
        Serial.println(xbee.getResponse().getErrorCode());

      }
    }
  } else {
    Serial.println("  time out. nothing to read.");
  }
}


int readXbee() {
  xbee.readPacket();

  if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
    xbee.getResponse().getZBTxStatusResponse(txStatus);

    // get the delivery status, the fifth byte
    if (txStatus.getDeliveryStatus() == SUCCESS) {
      // success.  time to celebrate
      // Debug option:
      //Serial.println("  confirmation received- readXbee");
    } else {
      Serial.print("  tx error ");
      Serial.println(txStatus.getDeliveryStatus());

    }

  } else if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {

    if (xbee.getResponse().isAvailable()) {

      //Serial.println("Data is available.");
      xbee.getResponse().getZBRxResponse(rx);
      
      // Serial.print("message received. ");
      // Serial.print("length: ");
      // Serial.println(rx.getDataLength());

      switch (rx.getData(0)) {
        case 0:
          // hello, are you here?
          Serial.print("0 Status Request Received from ");
          Serial.println(rx.getData(1));

          statusReplyTimer.enable();
          statusReplyTimer.setInterval(500);
          statusReplyTimer.setIterations(1);
          sendXbeeStatusReply(rx.getData(1), 1);

          statusReplyTimer.setCallback(&sendStack);
          //Serial.println("statusReplyTimer Enabled");
          runner.addTask(statusReplyTimer);
          //Serial.println("statusReplyTimer Running");

          break;

        case 1:
          // set time and return new time
          Serial.print("1 Status Reply Received from ");
          Serial.print(rx.getData(1));
          if (rx.getData(2) == 1) {
            Serial.println(" Good");
          } else {
            Serial.println(" Bad");
          }
          break;

        case 10:
          // All Off
          Serial.println("10 all off");
          break;

        case 13:
          // push button event
          Serial.print("13 button on event received from pole ");
          Serial.println(rx.getData(1));
          //Serial.print(" with velocity of ");
          //Serial.println("0");
          break;

        case 14:
          Serial.print("14 button off received from pole ");
          Serial.println(rx.getData(1));
          break;

        case 15:
          Serial.print("15 color array received from pole ");
          Serial.println(rx.getData(1));
          break;

        case 16:
          Serial.print("16 color single received from pole ");
          Serial.println(rx.getData(1));
          // to do, set color received
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
