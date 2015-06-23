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

Task t1(20,  -1, &t1Callback);
Task t2(200, -1, &t2Callback);
Task t3(50, -1, &t3Callback);
Task t4(5,  -1, &t4Callback);

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
  
}

void t4Callback() {
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
  t4.enable();
  Serial.println("Enabled t4");

  runner.init();

  runner.addTask(t1);
  Serial.println("added t1");
  runner.addTask(t2);
  Serial.println("added t2");
  runner.addTask(t3);
  Serial.println("added t3");
  runner.addTask(t4);
  Serial.println("added t4");

  SeqOff();
  SeqOn();
  delay(500);
  
}

void loop() {
  runner.execute();

}
