
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
int knockApin = 12; int inTempApin = 13; int exTempApin = 14; int sonicApin = 15;

int dArrRaw[] = {0,0,0};
//items are btn, pir1, pir2

int anaArrRaw[] = {0,0,0,0};
// items are knock, sonic, intemp, extemp

/////////////////////////// Reading inputs

void setupSensors() {
  RTC_init();
  
  //day(1-31), month(1-12), year(0-99), hour(0-23), minute(0-59), second(0-59)
  //SetTimeDate(10,10,14,1,6,0); 
  pinMode(led13pin, OUTPUT);   
  pinMode(inLedpin, OUTPUT); 
  pinMode(exLedpin, OUTPUT);   
  //initialize the digital pin as an input.
  pinMode(bigBtnpin, INPUT);   
  pinMode(pir2pin, INPUT); 
  pinMode(pir1pin, INPUT); 
  pinMode(irPin, INPUT);


  
}


int readSensors() {
  //digital inputs
  dArrRaw[0] = digitalRead(bigBtnpin);
  dArrRaw[1] = digitalRead(pir1pin);
  dArrRaw[2] = digitalRead(pir2pin);
  
  //analog inputs
  anaArrRaw[0] = analogRead(knockApin);
  anaArrRaw[1] = analogRead(sonicApin);
  anaArrRaw[2] = analogRead(inTempApin);
  anaArrRaw[3] = analogRead(exTempApin);
  
  float intemp = (anaArrRaw[2] * .004882814);  //getting the voltage reading from the temperature sensor
  intemp = (((intemp - .5) * 100) * 1.8)+32; 
  
  float outtemp = (anaArrRaw[3] * .004882814);  //getting the voltage reading from the temperature sensor
  outtemp = (((outtemp - .5) * 100) * 1.8)+32; 
 
  // Serial.print(ReadTimeDate()); // Print out time in month/day/year
  // Serial.print(" pz-"); // Print out ana value for piezo(knock) sensor from big button
  // Serial.print(anaArrRaw[0]); 
  // Serial.print(" bn-"); // Print out dig value from big button
  // Serial.print(dArrRaw[0]);
 
  // Serial.print(" it-"); // Print out ana value from internal temp sensor
  // Serial.print(intemp);
  // Serial.print(" et-"); // Print out ana value from internal temp sensor
  // Serial.print(outtemp);
 
  // Serial.print(" u-"); // Print out ana value from ultrasonic sensor
  // Serial.print(anaArrRaw[1]);
 
  // Serial.print(" p1-"); // Print out digital value from passive Ir sensor #1
  // Serial.print( dArrRaw[1]);
 
  // Serial.print(" p2-");  // Print out digital value from passive Ir sensor #2
  // Serial.print( dArrRaw[2]);
  // Serial.print(" ir-"); // Print out key value from Ir coded reciever
  int val = digitalRead(irPin);
  //int key = getIRKey();
  // Serial.print(val);
  // Serial.print(key);
  //Serial.println("--");	
  // delay(30);

  return dArrRaw[0];
}

  
void readPushButton() {
  // read the state of the pushbutton value:
  // buttonState = digitalRead(buttonPin);
  buttonState = readSensors();

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == 1) {     
    // turn LED on:   
    //digitalWrite(ledPin, HIGH);
    if (prevButtonState == false) {
      
      Serial.println("BUTTON ON");
      prevButtonState = true;

      for (int i = 1; i < 5; i++) {
        allOn(150);
        // ledBoardOn(POLE * 2);
        // ledBoardOn((POLE * 2) - 1);
        //if (i != POLE) {
          //sendXbeeButtonOnEvent(i, 10);
          //sendXbeeLongColorTest(i);

        //}
      }
    }
  } else {
    // turn LED off:
    //digitalWrite(ledPin, LOW);
    if (prevButtonState == true) {
      
      Serial.println("BUTTON OFF");
      prevButtonState = false;

      for (int i = 1; i < 5; i++) {
        // ledBoardOff(POLE * 2);
        // ledBoardOff((POLE * 2) - 1);
        allOn(100);

        // if (i != POLE) {
        //   sendXbeeButtonOffEvent(i);

        // }
      }
    }
  }
}


