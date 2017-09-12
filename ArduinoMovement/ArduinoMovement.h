#ifndef ARDUINOMOVEMENT_H
#define ARDUINOMOVEMENT_H

//#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
//#else
//	#include "WProgram.h"   //老旧版本的库
#define LFWHEEL_A A1
#define LFWHEEL 1


#define RFWHEEL_A A4
#define RFWHEEL 4


#define LBWHEEL_A A3
#define LBWHEEL 3


#define RBWHEEL_A A6
#define RBWHEEL 6


#define CLP 25
#define SS1 26
#define SS2 27
#define SS3 28
#define SS4 29
#define SS5 30
#define NEAR 33

/*speed*/
#define VALU 180

//using anapin to detect the level of the turning speed and using pwmpin to determin it should go forward ,stop or backward
void motor(char pwmpin,char anapin,char state,int val);
void runfoward();
void runback();
void turnL() ;
void turnVL();

void turnR() ;
void turnVR();
void stop();
/*void setup();*/
/*void loop();*/
#endif
