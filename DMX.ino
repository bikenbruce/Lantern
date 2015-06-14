#define DMX_LED_PIN 8
#define DMX_PUSH_BUTTON_PIN 1 //analog

void setupDMX() {
  // dmx board setup
  // ToDo: This might be channel 2 or 3.  
  DmxSimple.usePin(2);
  DmxSimple.maxChannel(40);
  
  // setup push button on dmx shield
  pinMode(DMX_PUSH_BUTTON_PIN, INPUT);
  
  // blinking light on dmx board
  pinMode(DMX_LED_PIN, OUTPUT);
  
  // sample off
  digitalWrite(8, LOW);
  
}


boolean readDMXButtonStatus() {
  // 0 is pressed, greater than 0 is released  
  if (analogRead(DMX_PUSH_BUTTON_PIN) > 0) {
    // button is released
    return false;
   
  } else {
    // button is pressed
    return true;
    
  }
}

void setDMXBoardLED(boolean state) {
  if(state) {
    digitalWrite(8, HIGH);

  } else {
    digitalWrite(8, LOW);
  
  }
}



