#include <DmxSimple.h>
#include <XBee.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include <TaskScheduler.h>

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#include <EEPROM.h>

#include "rgb.h"

int POLE;

Task t1(20, -1, &t1Callback);
Task t2(20, -1, &t2Callback);
Task t3(10, -1, &t3Callback);

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

void t3Callback() {
  readPixel();
  readXbee();

}

void setup() {
  //setup logging
  Serial.begin(115200);
  Serial.println("SETUP Start");

  POLE = EEPROM.read(0);
  
  setupDMX();
  setupXbee();
  setupSensors();
  setupPixel();

  t1.enable();
  Serial.println("Enabled t1");
  t2.enable();
  Serial.println("Enabled t2");
  t3.enable();
  Serial.println("Enabled t3");

  runner.init();

  runner.addTask(t1);
  Serial.println("added t1");
  runner.addTask(t2);
  Serial.println("added t2");
  runner.addTask(t3);
  Serial.println("added t3");

  SeqOff();
  SeqOn();
  delay(500);
  
}

void loop() {
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
