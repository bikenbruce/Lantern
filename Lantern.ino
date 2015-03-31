#include <DmxSimple.h>
#include <XBee.h>
#include <SPI.h>

// Xbee messages
extern ZBTxRequest msgToCoordinator;
extern ZBTxRequest msgToPole1;
extern ZBTxRequest msgToPole2;
extern ZBTxRequest msgToPole3;
extern ZBTxRequest msgToPole4;
extern ZBTxRequest msgToPole5;

int messageState = 0;
int frameCount = 0;
int frameRate = 1;

void setup() {
  //setup logging
  Serial.begin(115200);
  Serial.println("SETUP Start");
  
  setupDMX();
  setupXbee();
  setupSensors();
  
}

void loop() {
  // button pressed.... send a message
//  if (readDMXButtonStatus()) {
//    if (messageState == 0) {
//      // send message
//      sendMessage(msgToCoordinator);
//      sendMessage(msgToPole1);
//      sendMessage(msgToPole2);
//      sendMessage(msgToPole3);
//      //sendMessage(msgToPole4);
//      //sendMessage(msgToPole5);
//      
//      setDMXBoardLED(true);
//      messageState = 1;
//    } else {
//      setDMXBoardLED(false);
//    }
//    
//  } else {
//    if (messageState == 1) {
//      messageState = 0;
//      setDMXBoardLED(false);
//    }
//    
//  }
    
  // read messages
  readXbee();
  //readSensors();
  
  // make the lights.
  frameCount = frameCount + frameRate;
  lightUp(frameCount);
  
  // reset frame count
  if (frameCount > 150) {
    frameCount = 0;
  }
  
  if (frameCount == 30) {
    sendMessage(msgToPole2);
  }
  
  if (frameCount == 70) {
    sendMessage(msgToPole3);
  }
  
  delay(50);
}
