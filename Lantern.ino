#include <DmxSimple.h>
#include <XBee.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TaskScheduler.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <EEPROM.h>

#include "rgb.h"
#include "comm.h"

int POLE;

// Task t3(50, -1, &t3Callback);
Task t4(5,  -1, &t4Callback);
Task t5(10000, -1, &t5Callback);
Task t6(1000, 1, &t6Callback);

Scheduler runner;

void t4Callback() {
  // CHecks the state of the button, sends xbee data on press / release events
  readButton();

  // This function reads the incoming xbee data and applies any changes to the data
  // If a message is read that needs a reply, a new task will be crated and will 
  // responed a second later.  This seems to resolve an issue with communication
  // between the xbees and the arduinos.
  readXbee();
  
  // send information from the data out to the lights.
  DrawAll();

}

void t5Callback() {
  // sends xbee status requests

  Serial.println("");
  for (int i = 6; i < 9; i++) {
    if (i != POLE) {
      sendXbeeStatusRequest(i);
    }
  }
}

void t6Callback() {
  Serial.println("t6 Called");

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
  Serial.println("t4 Enabled");
  if (POLE == 6) {
    t5.enable();
    Serial.println("t5 Enabled");
  }

  t6.enable();
  Serial.println("t6 Enabled");

  runner.init();

  //runner.addTask(t3);
  //Serial.println("added t3");
  runner.addTask(t4);
  Serial.println("t4 added");
  if (POLE == 6) {
    runner.addTask(t5);
    Serial.println("t5 added");
  }
  runner.addTask(t6);
  Serial.println("t6 added");

  delay(500);
  
}

void loop() {
  runner.execute();

}
