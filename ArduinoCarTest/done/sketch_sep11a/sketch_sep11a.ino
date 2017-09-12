#include"ArduinoMovement.h"



void setup() {
  /*initail*/
  Serial.begin(9600);

  /*input for 传感器*/
  pinMode(CLP, INPUT);
  pinMode(SS1, INPUT);
  pinMode(SS2, INPUT);
  pinMode(SS3, INPUT);
  pinMode(SS4, INPUT);
  pinMode(SS5, INPUT);
  pinMode(NEAR, INPUT);


  /*output for 电机*/
  pinMode(LFWHEEL_A, OUTPUT);
  pinMode(LFWHEEL, OUTPUT);
  pinMode(RFWHEEL_A, OUTPUT);
  pinMode(RFWHEEL, OUTPUT);
  pinMode(LBWHEEL_A, OUTPUT);
  pinMode(LBWHEEL, OUTPUT);
  pinMode(RBWHEEL_A, OUTPUT);
  pinMode(RBWHEEL, OUTPUT);
}

void loop()
{
  char num1, num2, num3, num4, num5, clp, near;
  clp = digitalRead(CLP);
  num1 = digitalRead(SS1);
  num2 = digitalRead(SS2);
  num3 = digitalRead(SS3);
  num4 = digitalRead(SS4);
  num5 = digitalRead(SS5);
  near = digitalRead(NEAR);
 
  if (near==1)//接近的时后
  { 
    Serial.print("near");
    runback();
    delay(400000);//test
    Serial.print("near1");
    turnVR();
    delay(350000);
    Serial.print("near2");
   // runfoward();
    delayMicroseconds(40000);
   // turnVL();
     delayMicroseconds(10000);
    
  }

   
  /*
  if(clp==1)
  {
    Serial.print("runback");
    delayMicroseconds(20);
     runback();
      delayMicroseconds(20000000);
    turnVR();
    delayMicroseconds(100);
    runfoward();
    delayMicroseconds(400);
    turnVL();
     delayMicroseconds(100);
 
    }
  */
 else if (num1 == 0 && num2 == 0 && num3 == 1)//循迹转弯
  {
    Serial.print("turnVL");
    turnVL();
    delayMicroseconds(3);
  }

  else  if (num1 == 0)          //第一个传感器检测到黑线用200的速度左转
  {
    Serial.println("turnL250");
    turnL();
    delayMicroseconds(2);
  }
  else if (num2 == 0)       //第二个传感器检测到黑线用150的速度左转
  {
    Serial.println("turnL200");
    turnL();
    delayMicroseconds(2);
  }
  else if (num3 == 0)       //第三个传感器检测到黑线goforward
  {
    Serial.println("runforward");
    runfoward();
    delayMicroseconds(2);
  }

  else if (num4 == 0)       //第4个传感器检测到黑线用150的速度右转
  {
    Serial.println("turnR150");
    turnR();
    delayMicroseconds(2);

  }
  else if (num5 == 0)        //第5个传感器检测到黑线用200的速度右转
  {
    Serial.println("turnR200");
    turnR();
    delayMicroseconds(2);
  }
  else                     //其他状态小车直走
  {
    Serial.println("runforward_else");
    runfoward();
    delay(2);
  }
}


