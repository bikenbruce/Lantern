#include <DmxSimple.h>
#include <XBee.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TaskScheduler.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <EEPROM.h>
#include <StackArray.h>

#include "rgb.h"
#include "comm.h"

int POLE;

// Task t3(50, -1, &t3Callback);
Task t4(5,  -1, &t4Callback);
Task t5(10000, -1, &t5Callback);

Scheduler runner;

// void t3Callback() {
//   // Read the button state
//   // Send xbee data on button down and up events
//   readButton();
  
// }

void t4Callback() {
  // CHecks the state of the button, sends xbee data on press / release events
  readButton();

  // This function reads the incoming xbee data and applies any changes to the data
  readXbee();
  
  // send information from the data out to the lights
  DrawAll();

  // reply to xbee events....
  sendXbeeQueue();

}

void t5Callback() {
  // sends xbee status requests

  Serial.println("");
  //for (int i = 6; i < 9; i++) {
    // if (i != POLE) {
    //   sendXbeeStatusRequest(i);
    // }
  if (POLE == 6) {
    sendXbeeStatusRequest(7);
    sendXbeeStatusRequest(8);
  }
  //}
}

void setup() {
  //setup logging
  Serial.begin(115200);
  Serial.println("SETUP Start");

  // Read the pole number from the EEPROM
  POLE = EEPROM.read(0);
  
  setupDMX();
  setupXbee();
  setupSensors();
  setupPixel();

  //t3.enable();
  //Serial.println("Enabled t3");
  t4.enable();
  Serial.println("Enabled t4");
  if (POLE == 6) {
    t5.enable();
    Serial.println("Enabled t5");
  }

  runner.init();

  //runner.addTask(t3);
  //Serial.println("added t3");
  runner.addTask(t4);
  Serial.println("added t4");
  if (POLE == 6) {
    runner.addTask(t5);
    Serial.println("added t5");
  }

  delay(500);
  
}

void loop() {
  runner.execute();

}
