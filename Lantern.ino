#include <DmxSimple.h>
#include <XBee.h>
#include <SPI.h>
#include <SoftwareSerial.h>

// Xbee messages
extern ZBTxRequest msgToCoordinator;
extern ZBTxRequest msgToPole1;
extern ZBTxRequest msgToPole2;
extern ZBTxRequest msgToPole3;
extern ZBTxRequest msgToPole4;
extern ZBTxRequest msgToPole5;
extern ZBTxRequest msgToPole6;
extern ZBTxRequest msgToPole7;
extern ZBTxRequest msgToPole8;

//int frameCount = 0;
int frameRate = 1;

void setup() {
  //setup logging
  Serial.begin(115200);
  Serial.println("SETUP Start");
  
  setupDMX();
  setupXbee();
  setupSensors();

  //allOff();
  
}

void loop() {    
  // read messages
  readXbee();
  
  //delay(5);
}
