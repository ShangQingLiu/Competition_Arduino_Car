#include"ArduinoMovement.h"
#include"SR04.h"
#define ECHO_PIN 8
#define TRIG_PIN 9
/*低电平= 0为黑
 * 高电平 = 1 为白
 */
int flag_A= 1;
int flag_B= 1;
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long distance;
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
  distance = sr04.Distance();
  Serial.print(distance);
  Serial.println("cm");
  
  if (distance < 8)//接近的时后
  { 
    Serial.print("neark");
    /*runback();
    delayMicroseconds(4);
    turnVR();
    delayMicroseconds(10);
    runfoward();
    delayMicroseconds(20);
    turnVL();
     delayMicroseconds(10);

  }
   /*test for time
   runback();
   Serial.print("runback1");
   delay(10000000);
      runfoward();
   Serial.print("forward");
   delay(1000000);
   Serial.print("runback2");
    runback();
    */
  if(clp==1)//碰撞
  {
    Serial.print("runback1");
     runback();
      delay(100000);
      Serial.print("runback2");
    turnVR();
    delay(400000);
    Serial.print("runback3");
    runfoward();
    delay(530000);
    Serial.print("runback4");
    turnVL();
      delay(400000);
 
    }
  else if(num1==0 && num2==0 &&num3==0 &&num4==0 &&num5==0 && flag_A) //全白 debug 2斜坡
 {
     Serial.print("Condition b");
     runfoward();
    delay(200000);
     Serial.print("runback4");
    turnVL();
      delay(370000);
      runback();
      delay(200000);
      runfoward();
      delay(200000);
      turnVR();
      delay(370000);
      flag_A = 0;
   }
    
    else if(num1==0 && num2==0 &&num3==0 &&num4==0 &&num5==0) //全黑直走
 {
     Serial.print("Condition a");
    runfoward();
    delay(100000);
   }
else if(num1==0 && num2==0 &&num3==0 &&num4==0)//黑黑黑黑 直走
 {
     Serial.print("Condition a");
    runfoward();
    delay(100000);
   }
 else if(num1==0 && num2==0 &&num3==0)// 黑黑黑 直走
 {
     Serial.print("Condition1");
     turnR();
     delay(50000);
    runfoward();
    delay(50000);
   }

 else if(num3==0 && num4==0&& num5==0&&flag_B)// 右黑黑黑 转向特殊情况
 {
    Serial.print("Condition2");
    runfoward();
    delay(100000);
     Serial.print("runback4");
    turnVL();
      delay(390000);
      runback();
      delay(200000);
      runfoward();
      delay(200000);
      turnVR();
      delay(390000);
      flag_B = 0;
   }
     else if (num1 == 0 && num2 == 1 && num3 == 0)//黑白黑 直走 debug
  {
    Serial.print("turnVL");
    runfoward();
    delay(350000);
    turnR();
          delay(50000);
  }
     else if (num1 == 0 && num2 == 1 && num3 == 1)//黑白白 垂直左转
  {
    Serial.print("turnVL");
    turnVL();
    delayMicroseconds(3);
  }
    else if (num1 == 0 && num2 == 0 && num3 == 1)  {//黑黑白 偏左转
    Serial.print("turnL");
    runfoward();
    delayMicroseconds(3);
  }
   else if (num5 == 0)        //第5个传感器检测到黑线用200的速度右转
  {
    Serial.println("turnR200");
    turnVR();
    delayMicroseconds(5);
  }
  else  if (num1 == 0)          //第一个传感器检测到黑线用200的速度左转
  {
    Serial.println("turnL250");
    turnVL();
    delayMicroseconds(5);
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
 
  else                     //其他状态小车直走
  {
    Serial.println("runforward_else");
    runfoward();
    delay(2);
  }
}

