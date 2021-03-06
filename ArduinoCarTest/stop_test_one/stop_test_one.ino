/********************
 * Our Arduino Mini Car Competition Code
 * Author:SQL
 * Date:0919
 * Note:Finish most of the Movement But need to configure the delay time.
 *********************/
/*********************
 * Core .h file for basic movement
 * 1. runfoward
 * 2. turnL
 * 3. turnVL
 * 4. turnR
 * 5. turnVR
 * 6. runback
 * 7. runback_slow
 */
#include "ArduinoMovement.h"
/**************************
 * Infrarad  .h files
 */
#include "SR04.h"
#define ECHO_PIN 8
#define TRIG_PIN 9
/*
 * 低电平= 0为黑
 * 高电平 = 1 为白
 */
/*********************************
 * Note: ratio
 *  runfoward: runback_slow 2000:740
 */
/***************************
 * Flags
 */
int flag_A = 0; //X
int flag_B = 1; //第一次抓取
int flag_C = 1; //控制全黑的第一次要右偏
int flag_D = 1;//for second special case only process one time
int flag_E = 0; // debug for second time BBB up slope
int flag_F = 1; //for ignoring the first meet black cross line
int flag_G = 0; //control second time before upslope
int flag_SensorDelay = 1;
int sig_pre1 = 0;//control all White condition
int sig_pre2 = 0;
int refresh = 1;
int sig = 0;
int i, j = 1, k;
int trig_upslope = 1;
int count_W = 0; //count the white times
int count_runback  = 0;//for runback time counting

//count_decrese time for adjust2
int count_de_C1 = 0;
int count_de_C2 = 0;
int count_de_C = 0;
int key = 0;

int count_de2_C1 = 0;
int count_de2_C2 = 0;
int count_de2_C = 0; 
int fix_de2_number1 = 0;
int fix_de2_number2 = 0;
/**********************
 * time counting for seconde T
 */
 int flag_time = 0;
unsigned long touchtime;
 unsigned long nowtime;
 int flag_pass = 0;
/**********************
 * adjust value
 */
 int flag_turn_to_180 = 0;
 int turn_to_180_value = 0;
int adjust_value = 1; //for adjust loop
int adjust2_value = 1; //for adjust2 loop
int adjust3_value = 1;
int adjust_de_value = 1;
int adjust_de2_value = 1;

   //sensor
   int sensorR_D;
  int sensorM_D;
  int sensorRB_D;
  int sensorLB_D;
   int sensorL_D;
  char num1, num2, num3, num4, num5, clp, near;
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
void resetsig()
{
  sig_pre1 = 0;
  sig_pre2 = 0;
}
    void turn_to_180(){
      while(turn_to_180_value){
            Serial.println("turn_to_180");
      sensorR_D = digitalRead(SensorR_D); //right side 
     sensorM_D = digitalRead(SensorM_D); //mid
     sensorRB_D = digitalRead(SensorRB_D);//right back
     sensorLB_D = digitalRead(SensorLB_D);//right back
     sensorL_D = digitalRead(SensorL_D);//right back1
          if(sensorLB_D){
            if(flag_turn_to_180){
                turn_to_180_value = 0;
              }
              flag_turn_to_180 = 1;
              turnVL();
              delay(190);
            }
            turnVL();
            delayMicroseconds(1);
        }
      }
    void adjust(){
   while(adjust_value)
    {
      Serial.println("adjust");
      sensorR_D = digitalRead(SensorR_D); //right side 
     sensorM_D = digitalRead(SensorM_D); //mid
     sensorRB_D = digitalRead(SensorRB_D);//right back
     sensorLB_D = digitalRead(SensorLB_D);//right back
     sensorL_D = digitalRead(SensorL_D);//right back1
      
            if(!sensorR_D && !sensorL_D){
                runback_slow();
                 Serial.println("adjust_test1");
                delayMicroseconds(1);
               // count_runback++;
               continue;
              }
            else if(!sensorR_D && sensorL_D){
                Serial.println("adjust_test2");
              turnVR_slow();
               delay(50);
              continue;
              }
            else if(sensorR_D && !sensorL_D){
              Serial.println("adjust_test3");
                turnVL_slow();
           delay(50);
                continue;
              }
           else  if(sensorR_D && sensorL_D){
                Serial.println("adjust_test4");
               adjust_value = 0;
              }
             stopward();
             delay(500);
    }
  }
  int fix_number1 = 0, fix_number2 = 0;
  void adjust2(){
     while (adjust2_value)
    {
      Serial.println("adjust2");
      sensorR_D = digitalRead(SensorR_D); //right side 
     sensorM_D = digitalRead(SensorM_D); //mid
     sensorRB_D = digitalRead(SensorRB_D);//right back
     sensorLB_D = digitalRead(SensorLB_D);//right back
     sensorL_D = digitalRead(SensorL_D);//right back1
                /****/
                adjust_value = 1;
                /***/
            if(/*sensorRB_D && !sensorLB_D*/0){
                runback();
                 Serial.println("test1");
                delayMicroseconds(1);
               // count_runback++;
              }
           else if(!sensorRB_D && sensorLB_D){
                Serial.println("test2");
                runfoward();
                delay(370);
                stopward();
                delay(500);
              turnVL();
                delay(1520);
                 stopward();
                delay(500);
                runfoward();
                delay(150 - count_de_C2 - count_de_C1 + fix_number1 + fix_number2);
                 stopward();
                delay(500);
                turnVR();
                delay(1520);
                 stopward();
                delay(500);
                runback_slow();
                delay(1000);
         
                /////////////////////////////////////////////////////////////////////////////////////////////
                //adjust
                                         while(adjust_value)
                            {
                              Serial.println("adjust");
                              sensorR_D = digitalRead(SensorR_D); //right side 
                             sensorM_D = digitalRead(SensorM_D); //mid
                             sensorRB_D = digitalRead(SensorRB_D);//right back
                             sensorLB_D = digitalRead(SensorLB_D);//right back
                             sensorL_D = digitalRead(SensorL_D);//right back1
                              
                                    if(!sensorR_D && !sensorL_D){
                                        runback_slow();
                                         Serial.println("adjust_test1");
                                        delayMicroseconds(1);
                                       // count_runback++;
                                       continue;
                                      }
                                    else if(!sensorR_D && sensorL_D){
                                        Serial.println("adjust_test2");
                                      turnVR_slow();
                                       delay(50);
                                      continue;
                                      }
                                    else if(sensorR_D && !sensorL_D){
                                      Serial.println("adjust_test3");
                                        turnVL_slow();
                                   delay(50);
                                        continue;
                                      }
                                   else  if(sensorR_D && sensorL_D){
                                        Serial.println("adjust_test4");
                                       adjust_value = 0;
                                      }
                                     stopward();
                                     delay(500);
                            }
                
                /////////////////////////////////////////////////////////////////////////////////////////////
              
                 stopward();
                delay(500);
                count_de_C1 = count_de_C1 + 2;
                 if(count_de_C1 % 6 == 0)
                fix_number1 = count_de_C2 + 10;
                
              }
          else  if(sensorRB_D && !sensorLB_D){
              Serial.println("test3");
                  runfoward();   
                delay(370);
                 stopward();
                delay(500);
              turnVR();
                delay(1520);
                 stopward();
                delay(500);
                runfoward();
                delay(90 - count_de_C2 - count_de_C1 + fix_number2 + fix_number1);
                 stopward();
                delay(500);
                turnVL();
                delay(1520);
                 stopward();
                delay(500);
                runback_slow();
                delay(1000);
                    /////////////////////////////////////////////////////////////////////////////////////////////
                //adjust
                                         while(adjust_value)
                            {
                              Serial.println("adjust");
                              sensorR_D = digitalRead(SensorR_D); //right side 
                             sensorM_D = digitalRead(SensorM_D); //mid
                             sensorRB_D = digitalRead(SensorRB_D);//right back
                             sensorLB_D = digitalRead(SensorLB_D);//right back
                             sensorL_D = digitalRead(SensorL_D);//right back1
                              
                                    if(!sensorR_D && !sensorL_D){
                                        runback_slow();
                                         Serial.println("adjust_test1");
                                        delayMicroseconds(1);
                                       // count_runback++;
                                       continue;
                                      }
                                    else if(!sensorR_D && sensorL_D){
                                        Serial.println("adjust_test2");
                                      turnVR_slow();
                                       delay(50);
                                      continue;
                                      }
                                    else if(sensorR_D && !sensorL_D){
                                      Serial.println("adjust_test3");
                                        turnVL_slow();
                                   delay(50);
                                        continue;
                                      }
                                   else  if(sensorR_D && sensorL_D){
                                        Serial.println("adjust_test4");
                                       adjust_value = 0;
                                      }
                                     stopward();
                                     delay(500);
                            }
                
                /////////////////////////////////////////////////////////////////////////////////////////////
                 stopward();
                delay(500);
                count_de_C2 = count_de_C2 + 2;
                if(count_de_C2 % 6 == 0)
                fix_number2 = count_de_C2 + 10;
                
              }
          else  if(sensorRB_D && sensorLB_D){
                Serial.println("test4");
               
                Serial.println("test5");
                adjust2_value = 0;
                 
              }
  }
  }
  void adjust3(){
        while(adjust3_value){
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
/**********
 * speed control
 *  1         2         3         4            5
 * V100  120 80   40    0   -40  -80   -120  V-100
 */


   if ((num1) & (num2) & (num3) & (!num4)  &(!num5)) // 右黑黑(45)
  {
    Serial.print("右黑黑");
    turnVR();
    delayMicroseconds(2);
    
  }
  else if ((num1) & (num2) & (!num3) & (!num4)  &(num5)) // 右黑黑(34)
  {
    Serial.print("右黑黑");
    turnVR();
    delayMicroseconds(2);
    
  }
  else if ((num1) & (!num2) & (!num3) & (num4)  &(num5)) // 左黑黑(23)
  {
    Serial.print("右黑黑");
    turnVL();
    delayMicroseconds(2);
 
  }
  else if ((!num1) & (!num2) & (num3) & (num4)  &(num5)) // 左黑黑(12)
  {
    Serial.print("右黑黑");
    turnVL();
    delayMicroseconds(2);
    
  }
  else if (num5 == 0) //第5个传感器检测到黑线用200的速度右转
  {
    Serial.println("turnVR100");
    turnVR();
   delayMicroseconds(2);
    
  }
  else if (num1 == 0) //第1个传感器检测到黑线用200的速度左转
  {
    Serial.println("turnL250");
    turnVL();
    delayMicroseconds(2);

  }

  else if (num2 == 0) //第2个传感器检测到黑线用150的速度左转
  {
    Serial.println("turnL200");
    turnVL();
    delayMicroseconds(2);
   
  }
   else if (num4 == 0) //第4个传感器检测到黑线用150的速度右转
  {
    Serial.println("turnR80");
    turnR();
    delayMicroseconds(2);

  }
  else if (num3 == 0) //第3个传感器检测到黑线goforward
  {
    Serial.println("runforward");
    runfoward();
    delayMicroseconds(2);
  adjust3_value = 0;
  }

 
    }
  }




void adjust_de(){
     while(adjust_de_value){
     Serial.println("adjust_de");
      sensorR_D = digitalRead(SensorR_D); //right side 
     sensorM_D = digitalRead(SensorM_D); //mid
     sensorRB_D = digitalRead(SensorRB_D);//right back
     sensorLB_D = digitalRead(SensorLB_D);//right back
     sensorL_D = digitalRead(SensorL_D);//right back1
      
            if(!sensorR_D && !sensorL_D){
                runfoward();
                 Serial.println("adjust_de_test1");
                delayMicroseconds(1);
               // count_runback++;
               continue;
              }
            else if(!sensorR_D && sensorL_D){
                Serial.println("adjust_de_test2");
              turnVL_slow();
               delay(50);
              continue;
              }
            else if(sensorR_D && !sensorL_D){
              Serial.println("adjust_de_test3");
                turnVR_slow();
           delay(50);
                continue;
              }
           else  if(sensorR_D && sensorL_D){
                Serial.println("adjust_de_test4");
               adjust_de_value = 0;
              }
             stopward();
             delay(500);
    }
  }

  void adjust_de2(){
    while (adjust_de2_value)
    {
      Serial.println("adjust_de2_value");
      sensorR_D = digitalRead(SensorR_D); //right side 
     sensorM_D = digitalRead(SensorM_D); //mid
     sensorRB_D = digitalRead(SensorRB_D);//right back
     sensorLB_D = digitalRead(SensorLB_D);//right back
     sensorL_D = digitalRead(SensorL_D);//right back1
            adjust_de_value = 1;
            adjust_de();
            Serial.println("jump");
            if(/*sensorRB_D && !sensorLB_D*/0){
                runback();
                 Serial.println("adjustde2_test1");
                delayMicroseconds(1);
               // count_runback++;
              }
           else if(!sensorRB_D && sensorLB_D){
                Serial.println("adjustde2_test2");
                runback();
                delay(400);
                stopward();
                delay(500);
              turnVL();
                delay(1520);
                 stopward();
                delay(500);
                runfoward();
                delay(60 - count_de2_C2 - count_de2_C1 + fix_de2_number1 + fix_de2_number2);
                 stopward();
                delay(500);
                turnVR();
                delay(1520);
                 stopward();
                delay(500);
                runfoward();
                delay(100);
                adjust_de_value = 1;
                adjust_de();
                 stopward();
                delay(500);
                count_de2_C1 = count_de2_C1 + 2;
                 if(count_de2_C1 % 6 == 0)
                fix_number1 = count_de2_C2 + 10;
              }
          else  if(sensorRB_D && !sensorLB_D){
              Serial.println("adjustde2_test3");
                  runback();
                delay(400);
                 stopward();
                delay(500);
              turnVR();
                delay(1520);
                 stopward();
                delay(500);
                runfoward();
                delay(40 - count_de2_C2 - count_de2_C1 + fix_de2_number2 + fix_de2_number1);
                 stopward();
                delay(500);
                turnVL();
                delay(1520);
                 stopward();
                delay(500);
                runfoward();
                delay(100);
                adjust_de_value = 1;
                adjust_de();
                 stopward();
                delay(500);
                count_de2_C2 = count_de2_C2 + 2;
                if(count_de2_C2 % 6 == 0)
                fix_de2_number2 = count_de2_C2 + 10;
              }
          else  if(sensorRB_D && sensorLB_D){
                Serial.println("adjustde2_test4");
               
                adjust_de2_value = 0;
                 
              }
  }
  }
 /*******************************************************************************************************************************************************/
void loop()
{
  
 
 
 
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
  if(flag_time){
      Serial.println("flag_time");
      nowtime = millis();
      Serial.println("touchtime");
      Serial.println(nowtime);
      if(nowtime-touchtime > 7000){
        Serial.println("flag_pass");
        flag_pass = 1;
        }
        
    }
  if (3 < distance && distance < 15) //接近的时后
  {
    Serial.print("near");
    turnVR();
    delay(1520);
    runfoward();
    delay(2000);
    turnVL();
    delay(1520);
    trig_upslope = 1;
    unsigned long touchtime=millis();
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
     else if (num1 == 1 && num2 == 1 && num3 == 1 && num4 == 1 && num5 == 1 && sensorR_D == 0 && sensorM_D == 0 && sensorRB_D == 0 && sensorLB_D == 0 && sensorL_D == 0) //全W debug
    {
      if(sig_pre1<20){
        sig_pre1++;
        Serial.println(sig_pre1);
        runfoward();
        delayMicroseconds(2);
        }
      else{
        Serial.println("runback");
        runback();
      delay(2500);
      sig_pre1 = 0;
      }
    }
  else if (num1 == 0 && num2 == 0 && num3 == 0 && num4 == 0 && num5 == 0) //全B debug 斜坡前//
  {
    Serial.print("全B debug 2斜坡");
    if (flag_C)
    {
      turnVR();
      delayMicroseconds(2);
    }
    else
    {
      runfoward();
      delayMicroseconds(2);
    }
  }


  else if (num1 == 0 && num2 == 0 && num3 == 0 && trig_upslope) // 黑黑黑(123) 1
  {
 //cyclek:
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
      Serial.print("黑黑黑 1");
  Serial.println("runback");
       runback();
    delay(1400);
    /*
    Serial.println("runfoward");
    runfoward;
    delay(1400);
    adjust3();
    stopward();
    delay(5000);
    while(1){
     if (num1 == 0 && num2 == 0 && num3 == 0 && sensorM_D){
        Serial.println("shit");
       runfoward();
    delay(3500);
    trig_upslope = 0;
    flag_C = 0;
    flag_D = 1;
     }
     else if (num1 == 0 && num2 == 0 && num3 == 0 ){
      goto cyclek;
      }
      runfoward();
      delayMicroseconds(2);
     }
    if(sensorM_D){
      Serial.println("M_D");
      }
      if(!num1){
          Serial.println("num1");
        }
         if(!num2){
          Serial.println("num2");
        }
         if(!num3){
          Serial.println("num3");
        }
 */
     runfoward();
     delay(5400);
     trig_upslope = 0;
     key = 1;
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
  /*else if ((num1 == 0 && num2 == 0 && num3 == 0 && !(trig_upslope))||(num1 == 0 && num2 == 0 && num3 == 0 && num4 == 0 && !(trig_upslope)) ) // 黑黑黑(123) 2
  {
    Serial.print("黑黑黑 直走");
    runfoward();
    delay(4500);
    flag_C = 0;
  }*/
      else if(num1==0 && num2==0 &&num3==0 &&num4==0 &&num5==0) //全黑(12345)直走
 {
     Serial.print("Condition a");
    runfoward();
    delay(1000);
   }
 else if(num3 == 0 && num4 == 0 && num5 == 0 && flag_F ){//右黑黑黑(345)
        runfoward();
        delay(100);
        flag_F = 0;
    }
    
  else if ((sensorR_D == 1  && key && flag_D ||flag_pass) ) //  转向特殊情况2
  {
    Serial.print("右黑黑黑 转向特殊情况2");
      runfoward();
      delay(160);
      turnVR();
      delay(1520);
      runfoward();
      delay(200);
      turnVR();
      delay(1720);
      runback();
      delay(350);
      turnVR();
      delay(1720);
      /***************************
       * 转到180就停止
       
          turn_to_180_value = 1;
         while(turn_to_180_value){
            Serial.println("turn_to_180");
            sensorR_D = digitalRead(SensorR_D); //right side 
           sensorM_D = digitalRead(SensorM_D); //mid
           sensorRB_D = digitalRead(SensorRB_D);//right back
           sensorLB_D = digitalRead(SensorLB_D);//right back
           sensorL_D = digitalRead(SensorL_D);//right back1
          if(sensorLB_D){
            Serial.println("turn_to_180_test1");
            if(flag_turn_to_180){
               Serial.println("turn_to_180_test4");
                turn_to_180_value = 0;
              }
              flag_turn_to_180 = 1;
              turnVL();
              delay(190);
            }
            turnVL();
            delayMicroseconds(1);
        }
       ********************************/
        runback();
        delay(200);
         turnVR();
      delay(1720);
      runback();
        delay(200);
         turnVL();
      delay(1720);
      //part 2
          adjust_de_value = 1;
         adjust_de();
         adjust_de2_value = 1;
         adjust_de2();
       //This is time for doing the fetch
        stopward();
        delay(2000);
        /******************/
      //back to route
        adjust_de2_value = 1;
        adjust_de2();
        
        runfoward();
        delay(100);
        turnVR();
        delay(1720);
        runfoward();
        delay(1000);
        stopward();
        delayMicroseconds(1);
        flag_D = 0;
        flag_pass = 0;  
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
     /*
      while(1){
          if(!num2){
            turnVL();
            delayMicroseconds(1);
            continue;
          }
          else{
              if(!num4){
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
      }
      */
         runfoward();
         delay(100);
        turnVL();
        delay(1520);
        stopward();
        delay(2000);
      //part 2
         adjust_value = 1;
         adjust();
         adjust2_value = 1;
         adjust2();
       //This is time for doing the fetch
       while(1){
        stopward();
        delay(2000);
        }
      //back to route
      
          runfoward();
          delay(500);
        
        
        turnVR();
        delay(1520);
        runfoward();
        delayMicroseconds(2);
      flag_B = 0;
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
    delayMicroseconds(2);
    resetsig();
  }
  else if ((num1) & (num2) & (!num3) & (!num4)  &(num5)) // 右黑黑(34)
  {
    Serial.print("右黑黑");
    turnR();
    delayMicroseconds(2);
    resetsig();
  }
  else if ((num1) & (!num2) & (!num3) & (num4)  &(num5)) // 左黑黑(23)
  {
    Serial.print("右黑黑");
    turnL();
    delayMicroseconds(2);
    resetsig();
  }
  else if ((!num1) & (!num2) & (num3) & (num4)  &(num5)) // 左黑黑(12)
  {
    Serial.print("右黑黑");
    turnL();
    delayMicroseconds(2);
    resetsig();
  }
  else if (num5 == 0) //第5个传感器检测到黑线用200的速度右转
  {
    Serial.println("turnVR100");
    turnVR();
   delayMicroseconds(2);
    resetsig();
  }
  else if (num1 == 0) //第1个传感器检测到黑线用200的速度左转
  {
    Serial.println("turnL250");
    turnVL();
    delayMicroseconds(2);
    resetsig();
  }

  else if (num2 == 0) //第2个传感器检测到黑线用150的速度左转
  {
    Serial.println("turnL200");
    turnL();
    delayMicroseconds(2);
    resetsig();
  }
  else if (num3 == 0) //第3个传感器检测到黑线goforward
  {
    Serial.println("runforward");
    runfoward();
    delayMicroseconds(2);
    resetsig();
  }

  else if (num4 == 0) //第4个传感器检测到黑线用150的速度右转
  {
    Serial.println("turnR80");
    turnR();
    delayMicroseconds(2);
    resetsig();
  }
        
    
  
 
  else //其他状态小车直走
  {
    Serial.println("runforward_else");
    runfoward();
    delayMicroseconds(4);
    resetsig();
  }
}





