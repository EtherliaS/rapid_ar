#include <Mouse.h>
#include <Keyboard.h>

int xState = 0;
int yState = 0;
bool xPressed = false;
bool yPressed = false;
unsigned long endTime = 1000000;
long loopCount = 0;
bool printed = false;

int loopTimeTarget = 1000;


// Debounce Vars
unsigned long currentTime = 0;
unsigned long prevTime = 0;
bool rollover = false;
unsigned long xCount = 0;
unsigned long yCount = 0;
long releaseDebounce = 20;

int xDiff = 0;
int yDiff = 0;
int xDiff2 = 0;
int yDiff2 = 0;
int last_xState1 = 0;
int last_yState1 = 0;
int last_xState2 = 0;
int last_yState2 = 0;
int last_xState3 = 0;
int last_yState3 = 0;




void setup() {

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
  xState = 10*pow(10*(analogRead(A1) - 484), 0.41);
  yState = 10*pow(10*(analogRead(A2) - 497), 0.42);
  
  xDiff = xState - last_xState1;
  xDiff2 = xState - last_xState3;
  yDiff = yState - last_yState1;
  yDiff2 = yState - last_yState3;

  //Serial.print("x Wert: ");
  //Serial.println(xState);
  
  
  if(yState < 4){
    if(last_yState1 > 10){
      yCount = 0;
    }
  }

  if(xState < 4){
    if(last_xState1 > 10){
      xCount = 0;
    }
  }
  
  // Asymmetric Debounce X
  if (xDiff > 24){
    if(xCount >= releaseDebounce){
      //Serial.print("xDiff: ");
      //Serial.println(xDiff);
      pressX();
      
     
    }
  } else {

    xCount ++;
    
    if (xDiff < -10 && xDiff2 < -10){
      //Serial.print("xDiff: ");
      //Serial.println(xDiff);
      releaseX();
    }
  }
    
  // Asymmetric Debounce y
  if (yDiff > 24){
    if(yCount >= releaseDebounce){
      //Serial.print("yDiff: ");
      //Serial.println(yDiff);
      //Serial.print("yState: ");
      //Serial.println(yState);
      pressY();
      
    }
  } else {

    yCount ++;
    
    if (yDiff < -10 && yDiff2 < -10){
      //Serial.print("yDiff: ");
      //Serial.println(yDiff);
      releaseY();
    }
  }
  last_xState3 = last_xState2;
  last_yState3 = last_yState2;
  last_xState2 = last_xState1;
  last_yState2 = last_yState1;   
  last_xState1 = xState;
  last_yState1 = yState;


  if (xState > 240) {
    pressX();    
    }
  if (yState > 240) {
    pressY();    
    }

  if (xState < 5) {
    releaseX();    
    }
  if (yState < 5) {
    releaseY();    
    }
}


void pressX(){
  if (!xPressed){
    Keyboard.press('x');
    xPressed = true;
   
  }
}

void releaseX(){
  if (xPressed){
    Keyboard.release('x');
    xPressed = false;
    
  }
}

void pressY(){
  if (!yPressed){
    Keyboard.press('z');
    yPressed = true;
    
  }
}

void releaseY(){
  if (yPressed){
    Keyboard.release('z');
    yPressed = false;
    
  }
}

