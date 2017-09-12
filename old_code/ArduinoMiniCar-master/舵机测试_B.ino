#include <Servo.h> 
/*
*This is test for Servo_B
*range from 0~180  
*10 88 172
*---------------------------------------------------------------------------
*
*      | |                   | |                    | |  
*      | |      左侧   10    | |  口   中间 88      | |  右侧 172  
*      | |                   | |                 口 | |
*       O  口                 O                      O
*   ----------             --------               -------
*   |        |             |      |               |     |
*   |        |             |      |               |     |
*---------------------------------------------------------------------------
*/
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int temp;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90); //复位
  Serial.begin(9600);

} 
 
 
void loop() 
{ 
  /*
  for(pos = 0; pos<200; pos = pos+1)
  {
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    temp = myservo.read();
    Serial.println(temp);
    delay(200000);         
    }
    */
    myservo.write(10);              // tell servo to go to position in variable 'pos' 
    temp = myservo.read();
    Serial.println(temp);
    delay(400000);      
   myservo.write(88);              // tell servo to go to position in variable 'pos' 
    temp = myservo.read();
    Serial.println(temp);
    delay(400000);      
      myservo.write(172);              // tell servo to go to position in variable 'pos' 
    temp = myservo.read();
    Serial.println(temp);
    delay(400000);     
 
} 