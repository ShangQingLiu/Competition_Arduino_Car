#include "ArduinoMovement.h"
#include "SR04.h"
#define ECHO_PIN 8
#define TRIG_PIN 9
/*低电平= 0为黑
 * 高电平 = 1 为白
 */
int flag_A = 0; //control second fetch teh cube
int flag_B = 1; //control first fetch the cube
int flag_C = 1; //not use
int flag_D = 0;
int flag_E = 1; // debug for second time BBB up slope
int flag_F = 1; //for ignoring the first meet black cross line
int sig_pre1 = 0;
int sig_pre2 = 0;
int refresh = 1;
int sig = 0;
int i, j = 1, k;
int trig_upslope = 1;
int count_W = 0; //count the white times

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long distance;
void setup()
{
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
  delay(1000);
}

void loop()
{
  
 
  char num1, num2, num3, num4, num5, clp, near;
  int sensorA_D;
  int sensorB_D;
  //New route sensor
   sensorA_D = digitalRead(SensorA_D); //right side
  sensorB_D = digitalRead(SensorB_D); //mid

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
  // cycle:
  /* if(sig_pre1==1 && sig_pre2==1){
     Serial.print("sig_count");
      sig+=1;
      sig_pre1 = 0;
      sig_pre2 = 0;
    }
  if(sig==4){
   // runback();
   Serial.print("sig");
    delay(40);
      sig = 0;
    }*/
  if(trig_upslope)
  //judge while more than four being black
  if(((!num1) & (!num2) & (!num3) & (!num4)  &(num5) & flag_D)||((!num1) & (!num2) & (!num3) & (num4)  &(!num5) & flag_D)||((!num1) & (!num2) & (num3) & (!num4)  &(!num5) & flag_D)||((!num1) & (!num2) & (!num3) & (!num4)  &(!num5) & flag_D)||((num1) & (!num2) & (!num3) & (!num4)  &(!num5) & flag_D)||((!num1) & (!num2) & (!num3) & (!num4)  &(!num5) & flag_D))
     {flag_E = 1;
      flag_D = 0;
    }
  if (!(num1 == 1 && num2 == 1 && num3 == 1 && num4 == 1 && num5 == 1))
  {
    Serial.print("reset count_W");
    count_W = 0;
  }
  if (3 < distance && distance < 15) //接近的时后
  {
    Serial.print("near");
    turnVR();
    delay(1900);
    runfoward();
    delay(2300);
    turnVL();
    delay(1900);
    trig_upslope = 1;
    flag_D = 1;
  }

  //test for time
  /* runback();
   Serial.print("runback1");
   delay(10000000);
      runfoward();
   Serial.print("forward");
   delay(1000000);
   Serial.print("runback2");
    runback();
    */
  /* else if(clp==1)//碰撞
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
 
    }*/
  else if (num1 == 0 && num2 == 0 && num3 == 0 && num4 == 0 && num5 == 0) //全B debug 斜坡前//
  {
    Serial.print("全B debug 2斜坡");
    if (flag_C)
    {
      turnVR();
      delay(500);
    }
    else
    {
      runfoward();
      delayMicroseconds(80);
    }
  }


  else if (num1 == 0 && num2 == 0 && num3 == 0 && trig_upslope) // 黑黑黑(123) 1
  {
    Serial.print("黑黑黑 1");
    runback();
    delay(1500);
    trig_upslope = 0;
    flag_C = 0;
  }
    /* if(num3==0){
    turnL();
    delay(80);
  //  turnVL();
   // delay(40);
   /* for(i=0;i<10;i++){
    if(num1==0 && num2==0 && num3==0 && num4==0){
        runback();
        delay(500);
        turnR();
        delay(20);
        k=1;
        break;
      }
      break;
      delay(10);
    }
   }
  // if(k) goto cycle;
 
     Serial.print("Condition1");
    runfoward();
    delay(5000);
    
    flag_C = 0;
    flag_E = 1; //start the debug of second time BBB (upslope)
  }*/
  else if ((num1 == 0 && num2 == 0 && num3 == 0 && !(trig_upslope))||(num1 == 0 && num2 == 0 && num3 == 0 && num4 == 0 && !(trig_upslope)) ) // 黑黑黑(123) 2
  {
    Serial.print("黑黑黑 直走");
    runfoward();
    delay(4500);
    flag_C = 0;
  }
      else if(num1==0 && num2==0 &&num3==0 &&num4==0 &&num5==0) //全黑(12345)直走
 {
     Serial.print("Condition a");
    runfoward();
    delay(1000);
   }

  else if (sensorA_D  && flag_B) //  转向特殊情况1
  {
   /* Serial.print("右黑黑黑 转向特殊情况1");
    while(1){
      runfoward();
      delay(20);
      if(sensorA_D){
        Serial.println("tag");
        break;
      }
    }*/

    turnVL();
    delay(1900);
    runback();
    delay(1000);
    runfoward();
    delay(1000);
    turnVR();
    delay(1900);
    runfoward();
    delay(1000); 
    if (flag_B)
      flag_B = 0;
    flag_A = 1;
  }
  else if(num3 == 0 && num4 == 0 && num5 == 0 && flag_F ){//右黑黑黑(345)
        runfoward();
        delayMicroseconds(10);
        flag_F = 0;
    }
  else if ((sensorA_D == 1 && flag_A == 1 && flag_E) ) //  转向特殊情况2
  {
    Serial.print("右黑黑黑 转向特殊情况2");
    stopward();
    delay(200);
    turnVL();
    delay(1900);
    runback();
    delay(1000);
    runfoward();
    delay(1000);
    turnVR();
    delay(1900);
    runfoward();
    delay(1000);
    
    if(flag_A)
      flag_A = 0;
      flag_E = 0;
  }
/**********
 * speed control
 *  1         2         3         4            5
 * V100  120 80   40    0   -40  -80   -120  V-100
 */


  else if ((num1) & (num2) & (num3) & (!num4)  &(!num5)) // 右黑黑(45)
  {
    Serial.print("右黑黑");
    turnR();
    delayMicroseconds(12);
    resetsig();
  }
  else if ((num1) & (num2) & (!num3) & (!num4)  &(num5)) // 右黑黑(34)
  {
    Serial.print("右黑黑");
    turnR();
    delayMicroseconds(4);
    resetsig();
  }
  else if ((num1) & (!num2) & (!num3) & (num4)  &(num5)) // 左黑黑(23)
  {
    Serial.print("右黑黑");
    turnL();
    delayMicroseconds(4);
    resetsig();
  }
  else if ((!num1) & (!num2) & (num3) & (num4)  &(num5)) // 左黑黑(12)
  {
    Serial.print("右黑黑");
    turnL();
    delayMicroseconds(12);
    resetsig();
  }
  else if (num5 == 0) //第5个传感器检测到黑线用200的速度右转
  {
    Serial.println("turnVR100");
    turnVR();
   delayMicroseconds(10);
    resetsig();
  }
  else if (num1 == 0) //第1个传感器检测到黑线用200的速度左转
  {
    Serial.println("turnL250");
    turnVL();
    delayMicroseconds(10);
    resetsig();
  }

  else if (num2 == 0) //第2个传感器检测到黑线用150的速度左转
  {
    Serial.println("turnL200");
    turnVL();
    delayMicroseconds(80);
    sig_pre2 = 1;
  }
  else if (num3 == 0) //第3个传感器检测到黑线goforward
  {
    Serial.println("runforward");
    runfoward();
    delayMicroseconds(10);
    resetsig();
  }

  else if (num4 == 0) //第4个传感器检测到黑线用150的速度右转
  {
    Serial.println("turnR80");
    turnR();
    delayMicroseconds(8);
    sig_pre1 = 1;
  }
 /* else if (num1 == 1 && num2 == 1 && num3 == 1 && num4 == 1 && num5 == 1) //全W debug
  {
    Serial.println("全W debug");
    count_W++;
    runfoward();
    delay(25);

    if (count_W == 40)
    {
      runback();
      delay(4000);
    }
  }*/
  else //其他状态小车直走
  {
    Serial.println("runforward_else");
    runfoward();
    delayMicroseconds(4);
    resetsig();
  }
}

void resetsig()
{
  sig_pre1 = 0;
  sig_pre2 = 0;
}


