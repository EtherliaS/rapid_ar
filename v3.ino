#include <Keyboard.h>

unsigned long time_activation_z = 0;
unsigned long time_activation_x = 0;

bool xPressed = false;
bool zPressed = false;
//Z 484-435 (~50)
//X 497-474 (~23 -- shit)

int pr_z = 0;
int pr_x = 0;
int previous_point_z = 0;
int previous_point_x = 0; // now pred predpred
int zState = 500;
int xState = 500;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  while(1){
    currentTime = micros();
    if(currentTime % 500 < 50){
      checkPins();
    }
  }
}

void checkPins(){
  zState = analogRead(A1);
  xState = analogRead(A2);
  pr_z = previous_point_z;
  pr_x = previous_point_x;
  previous_point_z = zState;
  previous_point_x = xState;
  
  //Z
  if(zState < 475){
    if (!zPressed && zState < previous_point_z+2 && previous_point_z < pr_z+2 && millis() - time_activation_z > 0.2)
    {
        time_activation_z = millis();
        pressZ();
    }
    else if (zState > previous_point_z+2 && previous_point_z > pr_z+2){
        releaseZ();
    }
  }
  else releaseZ();

  //X
  if(xState < 492){
    if (!xPressed && xState < previous_point_x+2 && previous_point_x < pr_x+2 && millis() - time_activation_x > 0.2)
    {
        time_activation_x = millis();
        pressX();
    }
    else if (xState > previous_point_x+2 && previous_point_x > pr_x+2){
        releaseX();
    }
    
  }
  else releaseX();
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

void pressZ(){
  if (!zPressed){
    Keyboard.press('z');
    zPressed = true;
  }
}

void releaseZ(){
  if (zPressed){
    Keyboard.release('z');
    zPressed = false;
  }
}
