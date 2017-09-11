#ifndef ARDUINOMOVEMENT_H
#define ARDUINOMOVEMENT_H

//#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
//#else
//	#include "WProgram.h"   //老旧版本的库

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
