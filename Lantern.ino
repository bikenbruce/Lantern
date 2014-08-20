#include <DmxSimple.h>
#include <XBee.h>

extern ZBTxRequest msgToCoordinator;
extern ZBTxRequest msgToPole1;
extern ZBTxRequest msgToPole2;
extern ZBTxRequest msgToPole3;
extern ZBTxRequest msgToPole4;
extern ZBTxRequest msgToPole5;

int messageState = 0;

void setup() {
  //setup logging
  Serial.begin(9600);
  Serial.println("setup");
  
  setupDMX();
  setupXbee();
  
}

void loop() {
  // button pressed.... send a message
  if (readDMXButtonStatus()) {
    if (messageState == 0) {
      // send message
      sendMessage(msgToCoordinator);
      sendMessage(msgToPole1);
      sendMessage(msgToPole2);
      sendMessage(msgToPole3);
      sendMessage(msgToPole4);
      //sendMessage(msgToPole5);
      
      setDMXBoardLED(true);
      messageState = 1;
    } else {
      setDMXBoardLED(false);
    }
    
  } else {
    if (messageState == 1) {
      messageState = 0;
      setDMXBoardLED(false);
    }
    
  }
  
  // read messages
  readXbee();
  
  delay(100);
}
