/*
 * This is the test for Servo_C
 * The range is around 35~180
 * ------------------------------------------------------------------------------------------------------
 * -                                |
 * -        ---   右转90 50         |   直线  111        ___  左转90   163
 * -        |                       |                       |
 * -        |                       |                       |
 * -----------------------------------------------------------------------------------------------------
 */
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
 // myservo.write(90); //复位
  Serial.begin(9600);
} 
 
 
void loop() 
{ 
  
    myservo.write(163);              // tell servo to go to position in variable 'pos' 
    pos = myservo.read();
    Serial.println(pos);
    delay(400000);     
    // myservo.write(180);
   // delay(400000);  
   //  myservo.write(190);
    //delay(400000);  
    // waits 15ms for the servo to reach the position 
   // myservo.write(90);
  //  delay(400000);
 //     myservo.write(-30);
   //    delay(400000);  
   //   delay(400000);
   //     myservo.write(90);
    //delay(400000);  

     // myservo.write(35);
    //delay(400000);  
   //   myservo.write(40);
   // delay(400000);  
    //     myservo.write(50);
   // delay(400000);  
                    // waits 15ms for the servo to reach the position 
 
} 