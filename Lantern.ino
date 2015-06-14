#include <DmxSimple.h>
#include <XBee.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include <TaskScheduler.h>

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// struct RGB {
//   byte r;
//   byte g;
//   byte b;
// };

// RGB red   = {255, 0, 0};
// RGB green = {0, 255, 0};
// RGB blue  = {0, 0, 255};

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

int pushButtonState = 0;

Task t1(50, -1, &t1Callback);
Task t2(20, -1, &t2Callback);

Scheduler runner;

void t1Callback() {
    // Serial.print("t1: ");
    // Serial.println(millis());
    SeqUp();
    DrawAll();

}

void t2Callback() {
    // Serial.print("t2: ");
    // Serial.println(millis());
    SeqDown();
    DrawAll();

}

void setup() {
  //setup logging
  Serial.begin(115200);
  Serial.println("SETUP Start");
  
  setupDMX();
  setupXbee();
  setupSensors();
  setupPixel();

  t1.enable();
  Serial.println("Enabled t1");
  t2.enable();
  Serial.println("Enabled t2");

  runner.init();

  runner.addTask(t1);
  Serial.println("added t1");
  runner.addTask(t2);
  Serial.println("added t2");

  SeqOff();
  SeqOn();
  delay(1000);
  SeqOff();
  
}

void loop() {    
  // read messages
  //readXbee();
  //readPixel();

  runner.execute();

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
