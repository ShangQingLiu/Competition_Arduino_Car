#include "ArduinoMovement.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char num1, num2, num3, num4, num5, clp, near;
  int sensorR_D;
  int sensorM_D;
  int sensorRB_D;
  int sensorLB_D;
   int sensorL_D;
  //New route sensor
   sensorR_D = digitalRead(SensorR_D); //right side 
   sensorM_D = digitalRead(SensorM_D); //mid
   sensorRB_D = digitalRead(SensorRB_D);//right back
   sensorLB_D = digitalRead(SensorLB_D);//right back
   sensorL_D = digitalRead(SensorL_D);//right back1
  clp = digitalRead(CLP);
  num1 = digitalRead(SS1);
  num2 = digitalRead(SS2);
  num3 = digitalRead(SS3);
  num4 = digitalRead(SS4);
  num5 = digitalRead(SS5);
  near = digitalRead(NEAR);
    turnVR();
    delay(1520);
    stopward();
    delay(2000);
}
