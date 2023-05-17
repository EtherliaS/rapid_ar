
#include <Mouse.h>
#include <Keyboard.h>
int xKeyPin = 3;
int yKeyPin = 20;
int xLedPin = 5;
int yLedPin = 18;
bool xState = false;
bool yState = false;
bool xPressed = false;
bool yPressed = false;
unsigned long endTime = 1000000;
long loopCount = 0;
bool printed = false;

int loopTimeTarget = 1000;

int RXLED = 17;
int TXLED = 30;

// Debounce Vars
unsigned long currentTime = 0;
unsigned long prevTime = 0;
bool rollover = false;
unsigned long xCount = 0;
unsigned long yCount = 0;
long releaseDebounce = 12;


void setup() {
  pinMode(xKeyPin, INPUT_PULLUP);
  pinMode(yKeyPin, INPUT_PULLUP);
  pinMode(xLedPin, OUTPUT);
  pinMode(yLedPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RXLED, OUTPUT); // Set RX LED as an output
  pinMode(TXLED, OUTPUT); // Set TX LED as an output
  //attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
  
  Serial.begin(9600);
  Keyboard.begin();
  Mouse.begin();
}

void loop() {

  while(1){
    currentTime = micros();
    if(currentTime % 500 < 50){
      checkPins();
    }
  
    // Microsecond sleep
    //delayMicroseconds(loopTimeTarget - (currentTime - micros() + (rollover * 4294967295UL)));
  
    
    //digitalWrite(LED_BUILTIN, HIGH);
    //digitalWrite(RXLED, HIGH); // set the LED off
  
    /*if (currentTime >= endTime) {
      Serial.println(loopCount);
      endTime += 1000000;
      loopCount = 0;
    }*/
  }
  
}

void checkPins(){
  
  loopCount++;
  xState = digitalRead(xKeyPin);
  yState = digitalRead(yKeyPin);
  
  // Asymmetric Debounce X
  if (!xState){
    pressX();
    xCount = 0;
    
  } else {

    xCount ++;
    
    if(xCount >= releaseDebounce){
      releaseX();
    }
  }
    
  // Asymmetric Debounce Y
  if (!yState){
    
    pressY();
    yCount = 0;
    
  } else {

    yCount ++;
    if(yCount >= releaseDebounce){
      releaseY();
    }
    
  }
}


void pressX(){
  if (!xPressed){
    Keyboard.press('z');
    xPressed = true;
    digitalWrite(TXLED, LOW); // set the LED off
    digitalWrite(xLedPin, HIGH);
    digitalWrite(yLedPin, HIGH);
  }
}

void releaseX(){
  if (xPressed){
    Keyboard.release('z');
    xPressed = false;
    digitalWrite(TXLED, HIGH); // set the LED off
    digitalWrite(xLedPin, LOW);
    digitalWrite(yLedPin, LOW);
  }
}

void pressY(){
  if (!yPressed){
    Keyboard.press('x');
    yPressed = true;
    digitalWrite(RXLED, LOW); // set the LED off
    digitalWrite(xLedPin, HIGH);
    digitalWrite(yLedPin, HIGH);
  }
}

void releaseY(){
  if (yPressed){
    Keyboard.release('x');
    yPressed = false;
    digitalWrite(RXLED, HIGH); // set the LED off
    digitalWrite(xLedPin, LOW);
    digitalWrite(yLedPin, LOW);
  }
}

