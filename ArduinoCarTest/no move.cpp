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

int count_runback = 0; //count runback for adjust position

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
  distance = sr04.Distance();
  Serial.print(distance);
  Serial.println("cm");
  // cycle:
  /* if(sig_pre1==1 && sig_pre2==1){1
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

  else if (sensorR_D  && flag_B) //  转向特殊情况1
  {
    Serial.print("右黑黑黑 转向特殊情况1");
    /************
     * design for adjust the position
     * **********
     *   part1
     *      Target: front (on line) + left back (miss line) + right back (miss line) + Mid (on line) + right (on line)
     *      make only num3 online
     *        doing num2 (on line) turnVL
     *        doing num4 (on line) turnVR
     *      if right back (on line)turnVL
     *      if left back (on line) turnVR
     *     
     *     -->turnVL 90 degree
     *   part2:
     *       runback(recording) until left side(on line) + right side(on line)
     *          if only left side(on line) turnVR back to runback
     *          if only right side(on line) turVL back to runback
     *       recover rocored and back to route
     *    
     */
     //part 1
      while(1){
          if(num2){
            turnVL();
            delayMicroseconds(1);
            continue;
          }
          else{
              if(num4){
                  turnVR();
                  delayMicroseconds(1);
                  continue;
                }
              else{
                  if(sensorRB_D){
                  turnVL();
                   delayMicroseconds(1);
                   continue;
                }
                else{
                    if(sensorLB_D){
                       turnVR();
                       delayMicroseconds(1);
                       continue;
                      }
                      else break;
                  }
            }
        }

        turnVL();
        delay(1900);
      //part 2
      while(1){
          if(!(sensorR_D)||!(sensorL_D)){
            runback();
            count_runback++;
            delayMicroseconds(2);
            continue;
         }
         else if(!(sensorR_D)||(sensorL_D)){
            turnVL();
             delayMicroseconds(1);
             continue;
          }
         else if((sensorR_D)||!(sensorL_D)){
               turnVR();
             delayMicroseconds(1);
             continue;
            }
          else break;
        }
       //This is time for doing the fetch
        stopward();
        delay(2000);
      //back to route
      for(;count_runback>=0;count_runback--){
          runfoward();
          delayMicroseconds(2);
        }
        
        turnVR();
        delay(1000);
        runfoward();
        delayMicroseconds(2);
      
  }
    
    
    
  }
  else if(num3 == 0 && num4 == 0 && num5 == 0 && flag_F ){//右黑黑黑(345)
        runfoward();
        delayMicroseconds(10);
        flag_F = 0;
    }
  else if ((sensorR_D == 1 && flag_A == 1 && flag_E) ) //  转向特殊情况2
  {
    Serial.print("右黑黑黑 转向特殊情况2");
    //part 1
      while(1){
          if(num2){
            turnVL();
            delayMicroseconds(1);
            continue;
          }
          else{
              if(num4){
                  turnVR();
                  delayMicroseconds(1);
                  continue;
                }
              else{
                  if(sensorRB_D){
                  turnVL();
                   delayMicroseconds(1);
                   continue;
                }
                else{
                    if(sensorLB_D){
                       turnVR();
                       delayMicroseconds(1);
                       continue;
                      }
                      else break;
                  }
            }
        }

        turnVL();
        delay(1900);
      //part 2
      while(1){
        
         if(!(sensorR_D)||!(sensorL_D)){
            runback();
            count_runback++;
            delayMicroseconds(2);
            continue;
         }
         else if(!(sensorR_D)||(sensorL_D)){
            turnVL();
             delayMicroseconds(1);
             continue;
         }
          else if((sensorR_D)||!(sensorL_D)){
               turnVR();
             delayMicroseconds(1);
             continue;
            }
          else break;
        }
       //This is time for doing the fetch
        stopward();
        delay(2000);
      //back to route
      for(;count_runback>=0;count_runback--){
          runfoward();
          delayMicroseconds(2);
        }
        
        turnVR();
        delay(1000);
        runfoward();
        delayMicroseconds(2);
  }
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
  else if(num3 ==0 && sensorM_D == 1){
    Serial.println("GO forward 1");
    runfoward();
    delayMicroseconds(10);
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



