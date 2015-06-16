// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            25

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // delay for half a second

const int buttonPin = 24;     // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

int buttonState = 0;         // variable for reading the pushbutton status
bool prevButtonState = false;

int SeqUpLevel = 0;
int SeqUpValue = 0;

int SeqDownLevel = 7;
int SeqDownValue = 0;

extern int rRateChange = 1;
extern int gRateChange = 1;

int r[8];
int g[8];
int b[8];


void setupPixel() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  
  pixels.begin(); // This initializes the NeoPixel library.
}


void readPixel() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);
    if (prevButtonState == false) {
      prevButtonState = true;
      Serial.println("button on.");
      rRateChange = 1;
    }
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    if (prevButtonState == true) {
      Serial.println("button off.");
      prevButtonState = false;
    }
  }
}


void SeqUp() {
  SeqUpValue += rRateChange;

  if (SeqUpValue > 10) {
    // Resets the current lit LED to 0
    r[SeqUpLevel] = 0;
    // Reset the briightness to 0
    SeqUpValue = 0;
    // Jump to the next LED
    SeqUpLevel += 1;
  }

  if (SeqUpLevel > 7) {
    SeqUpLevel = 0;
    rRateChange = 0;
  }
}

void SeqDown() {
  SeqDownValue += gRateChange;

  if (SeqDownValue > 10) {
    // Set the current LED to 0
    g[SeqDownLevel] = 0;
    // Reset the brightness to 0
    SeqDownValue = 0;
    //Jump to the next LED
    SeqDownLevel -= 1;
  }

  if (SeqDownLevel < 0) {
    SeqDownLevel = 7;
    gRateChange = 0;
  }
}

void DrawAll() {
  r[SeqUpLevel] = SeqUpValue;
  g[SeqDownLevel] = SeqDownValue;

  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r[i], g[i], b[i]));
  }

  pixels.show();
}

void SeqOn() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(10,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}


void SeqOff() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(delayval); // Delay for a period of time (in milliseconds).
  }
}



