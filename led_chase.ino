// LEDS
const int pinLed[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };  // declaration and initialization of the array 
// which will contain the pins corresponding to the leds

// pin values and a timer
int val = 0;
int timer = 100;

// variable button
#define button 2
volatile bool toggle = false;

// Potentiometer
#define potPin A0 // Reading of pin A0 to which the potentiometer is connected 
int potValue = 0; // value read in pin A0
int valPWM = 0; // PWM value of the potentiometer

void setup() {    
  Serial.begin(9600);
  initializationButton();
  initializationInteruption();
  // Mode initialization loop and 0V setting
  for (int i = 0; i < 8; i++) { // i will be used to browse the table of pins corresponding to the leds
    pinMode(pinLed[i], OUTPUT); // we use and initialize the values of the array
  }
}

void loop() {
  ////////////////////////////////////////////LEDS/////////////////////////////////////////////////////////////
  // we turn on the 8 LEDs (here using a loop) and we change the mode by the potentiometer
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (toggle) { // precondition test
    turnOff();
    if (Potent() >= val && Potent() < val) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(pinLed[i], HIGH); 
        delay(timer);
        digitalWrite(pinLed[i], LOW);
        delay(timer);
      }
   } else {
      for (int i = 0; i < 8; i++) {
        digitalWrite(pinLed[i], LOW); 
        delay(timer);
        digitalWrite(pinLed[i], HIGH);
        delay(timer);
      }
   }
  } else {
    turnOn();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

int Potent() {
  //////////////////////////////////////////////////POTENTIOMETER//////////////////////////////////////////////////////
  potValue = analogRead(potPin); // Potentiometer value
  valPWM = map(potValue, 0, 1023, 0, 255); // Rescale from 0 to 254
  for (int i = 0; i < 8; i++) {
     analogWrite(pinLed[i], valPWM); // Writes the rescaled value to the PWM output
  }
  // Serial.println(valPWM); // To know the value sent to the PWM output
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////Function turnOn et turnOff/////////////////////////////
void turnOff() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(pinLed[i], LOW);
  }
}

void turnOn() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(pinLed[i], HIGH);
  }
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////Button initialization and interruption///////////////////////
void initializationButton() {
  pinMode(button, INPUT_PULLUP); // Pullup resistance for anti-bounce
}

void initializationInteruption() {
  attachInterrupt(digitalPinToInterrupt(button), switch, RISING); // Info for the compiler: to keep
    // RISING detects the transition between LOW and HIGH and interrupts at that moment
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////Function toggle///////////////////////////////////
void switch() {
  toggle = !toggle;
  // Serial.println("interruption");
  if (toggle) { // test of preconditions either led turnOff() or turnOn()
    turnOff();
  } else {
    turnOn();
  }
}
//////////////////////////////////////////////////////////////////////////////////
