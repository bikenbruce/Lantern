#include <DmxSimple.h>
#include <XBee.h>
#include <SPI.h>
#include <SoftwareSerial.h>

// Xbee messages
extern ZBTxRequest msgToBroadcast;
extern ZBTxRequest msgToCoordinatorSJ;
extern ZBTxRequest msgToCoordinatorSD;
extern ZBTxRequest msgToPole1;
extern ZBTxRequest msgToPole2;
extern ZBTxRequest msgToPole3;
extern ZBTxRequest msgToPole4;
extern ZBTxRequest msgToPole5;
extern ZBTxRequest msgToPole6;
extern ZBTxRequest msgToPole7;
extern ZBTxRequest msgToPole8;
extern ZBTxRequest msgToPole9;

int frameCount = 0;
int pushButtonState = 0;

void setup() {
  //setup logging
  Serial.begin(115200);
  Serial.println("SETUP Start");
  
  setupDMX();
  setupXbee();
  setupSensors();
  
}

void loop() {    
  // read messages
  readXbee();

  // if (readSensors() == 1) {
  //   if (pushButtonState == 0) {
  //     pushButtonState = 1;
  //     Serial.println("button pressed.");

  //   } 
  // } else if (readSensors() == 0) {
  //   if (pushButtonState == 1) {
  //     pushButtonState = 0;
  //     Serial.println("button released.");

  //   }
  // }

  // frameCount += 1;
  // if (frameCount > 200) {
  //   frameCount = 0;
  //   //sendXbee();

  // }
  
}
