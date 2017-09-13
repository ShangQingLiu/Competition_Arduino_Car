#include"ArduinoMovement.h"
#include"SR04.h"
#define ECHO_PIN 8
#define TRIG_PIN 9
/*�͵�ƽ= 0Ϊ��
 * �ߵ�ƽ = 1 Ϊ��
 */
int flag_A= 1;
int flag_B= 1;
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long distance;
void setup() {
  /*initail*/
  Serial.begin(9600);

  /*input for ������*/
  pinMode(CLP, INPUT);
  pinMode(SS1, INPUT);
  pinMode(SS2, INPUT);
  pinMode(SS3, INPUT);
  pinMode(SS4, INPUT);
  pinMode(SS5, INPUT);
  pinMode(NEAR, INPUT);


  /*output for ���*/
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
  
  if (distance < 8)//�ӽ���ʱ��
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
  if(clp==1)//��ײ
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
  else if(num1==0 && num2==0 &&num3==0 &&num4==0 &&num5==0 && flag_A) //ȫ�� debug 2б��
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
    
    else if(num1==0 && num2==0 &&num3==0 &&num4==0 &&num5==0) //ȫ��ֱ��
 {
     Serial.print("Condition a");
    runfoward();
    delay(100000);
   }
else if(num1==0 && num2==0 &&num3==0 &&num4==0)//�ںںں� ֱ��
 {
     Serial.print("Condition a");
    runfoward();
    delay(100000);
   }
 else if(num1==0 && num2==0 &&num3==0)// �ںں� ֱ��
 {
     Serial.print("Condition1");
     turnR();
     delay(50000);
    runfoward();
    delay(50000);
   }

 else if(num3==0 && num4==0&& num5==0&&flag_B)// �Һںں� ת���������
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
     else if (num1 == 0 && num2 == 1 && num3 == 0)//�ڰ׺� ֱ�� debug
  {
    Serial.print("turnVL");
    runfoward();
    delay(350000);
    turnR();
          delay(50000);
  }
     else if (num1 == 0 && num2 == 1 && num3 == 1)//�ڰװ� ��ֱ��ת
  {
    Serial.print("turnVL");
    turnVL();
    delayMicroseconds(3);
  }
    else if (num1 == 0 && num2 == 0 && num3 == 1)  {//�ںڰ� ƫ��ת
    Serial.print("turnL");
    runfoward();
    delayMicroseconds(3);
  }
   else if (num5 == 0)        //��5����������⵽������200���ٶ���ת
  {
    Serial.println("turnR200");
    turnVR();
    delayMicroseconds(5);
  }
  else  if (num1 == 0)          //��һ����������⵽������200���ٶ���ת
  {
    Serial.println("turnL250");
    turnVL();
    delayMicroseconds(5);
  }
  else if (num2 == 0)       //�ڶ�����������⵽������150���ٶ���ת
  {
    Serial.println("turnL200");
    turnL();
    delayMicroseconds(2);
  }
  else if (num3 == 0)       //��������������⵽����goforward
  {
    Serial.println("runforward");
    runfoward();
    delayMicroseconds(2);
  }

  else if (num4 == 0)       //��4����������⵽������150���ٶ���ת
  {
    Serial.println("turnR150");
    turnR();
    delayMicroseconds(2);

  }
 
  else                     //����״̬С��ֱ��
  {
    Serial.println("runforward_else");
    runfoward();
    delay(2);
  }
}

