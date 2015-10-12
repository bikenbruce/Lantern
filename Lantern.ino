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
Task mainTimer(5,  -1, &mainCallback);
Task statusRequestTimer(10000, -1, &statusRequestCallback);
Task statusReplyTimer(1000, 1, &statusRequestCallback);

Scheduler runner;

void mainCallback() {
  // CHecks the state of the button, sends xbee data on press / release events
  readPushButton();
  // readSensors();

  // This function reads the incoming xbee data and applies any changes to the data
  // If a message is read that needs a reply, a new task will be crated and will 
  // responed a second later.  This seems to resolve an issue with communication
  // between the xbees and the arduinos.
  readXbee();
  
  // send information from the data out to the lights.
  // DrawAllPixel();
  //DrawAllLEDs();


}

void statusRequestCallback() {
  // sends xbee status requests

  for (int i = 1; i < 4; i++) {
    if (i != POLE) {
      // sendXbeeStatusRequest(i);
    }
  }
}


void setup() {
  //setup logging
  Serial.begin(115200);
  Serial.println("SETUP Start");

  // Read the pole number from the EEPROM
  POLE = EEPROM.read(0);

  Serial.print("I am pole ");
  Serial.println(POLE);
  
  setupDMX();
  setupXbee();
  setupSensors();
  //setupPixel();

  mainTimer.enable();
  Serial.println("mainTimer Enabled");

  statusRequestTimer.enable();
  Serial.println("statusRequestTimer Enabled");

  runner.init();

  runner.addTask(mainTimer);
  Serial.println("mainTimer added");

  runner.addTask(statusRequestTimer);
  Serial.println("statusRequestTimer added");

  delay(500);
  
}

void loop() {
  runner.execute();

}
