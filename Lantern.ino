#include <DmxSimple.h>
#include <XBee.h>
#include <SPI.h>

// Sensors
const int cs = 53; //chip select
int led13pin = 13; int inLedpin = 34; int exLedpin = 24;

//digital inputs
int bigBtnpin = 28; int pir2pin = 32; int pir1pin = 36; 

//  ir receiever pin
int irPin = 26;
int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)
boolean ledtoggle = HIGH;

//analogs ins
int knockApin = 12;  int inTempApin =13; int exTempApin =14; int sonicApin = 15;

int dArrRaw[] = {0,0,0};
//items are btn, pir1, pir2

int anaArrRaw[] = {0,0,0,0};
// items are knock, sonic, intemp, extemp

// Xbee messages
extern ZBTxRequest msgToCoordinator;
extern ZBTxRequest msgToPole1;
extern ZBTxRequest msgToPole2;
extern ZBTxRequest msgToPole3;
extern ZBTxRequest msgToPole4;
extern ZBTxRequest msgToPole5;

int messageState = 0;

void setup() {
  //setup logging
  Serial.begin(115200);
  
  setupDMX();
  setupXbee();
  setupSensors();
  
  Serial.println("SETUP Start");
  
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
      //sendMessage(msgToPole4);
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
  readSensors();
  
  delay(50);
}
