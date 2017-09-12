#include <Servo.h> 
/*
*This is test for Servo_A
*range from 0~63
*
*---------------------------------------------------------------------------
*
*   \       /                 | |                   /   \
*    \     /  完全张开   0    | |  完全夹起 >63     \   / 刚好可夹起物品 37
*     \   /                   | |                    \ /
*       O                      O                      O
*
*---------------------------------------------------------------------------
*/
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(70); //复位
  Serial.begin(9600);
  delay(400000); 
} 
 
 
void loop() 
{ 
  
    myservo.write(0);              // tell servo to go to position in variable 'pos' 
    pos = myservo.read();
    Serial.println(pos);
    delay(400000);                       // waits 15ms for the servo to reach the position 
    myservo.write(37);
      Serial.read();
    delay(400000);  
     myservo.write(63);
      Serial.read();
    delay(400000);  
                    // waits 15ms for the servo to reach the position 
 
} 