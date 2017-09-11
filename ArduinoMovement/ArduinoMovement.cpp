/*This is the movement part of our mini car
*Date:2017-07-19
*Editor:SQL
*Source Code:
*http://transcoder.tradaquan.com/from=844b/bd_page_type=1/ssid=0/uid=0/pu=usm%401%2Csz%401320_2001%2Cta%40iphone_1_10.3_3_603/baiduid=D8E547DCF857FFAC980886835E7F4F46/w=0_10_/t=iphone/l=3/tc?ref=www_iphone&lid=13612792800971297501&order=1&fm=alop&waplogo=1&h5ad=1&srd=1&dict=32&tj=www_normal_1_0_10_title&vit=osres&waput=3&cltj=normal_title&asres=1&nt=wnor&title=Arduino%E6%95%99%E7%A8%8B%28%E5%AE%9E%E4%BE%8B%E7%AF%87%29%E5%B7%A1%E7%BA%BF%E5%B0%8F%E8%BD%A6%E7%9A%84%E5%88%B6%E4%BD%9C-Arduino%E4%B8%AD%E6%96%87...&w_qd=IlPT2AEptyoA_yi9DkOsIis8OlkRqntro5NurPCSdP2ZGBRM&sec=22571&di=318cbc4c84361421&bdenc=1&tch=124.383.58.217.0.0&nsrc=IlPT2AEptyoA_yixCFOxXnANedT62v3IEQGG_y6G2iu8o50te4qaUbBuWiHqMXvLUpOddivPvB9PaDD7Qq&eqid=bcea5aedc6e3900010000006596df0df&wd=&clk_info=%7B%22srcid%22%3A%221533%22%2C%22tplname%22%3A%22www_normal%22%2C%22t%22%3A1500377315417%2C%22sig%22%3A%223622%22%2C%22xpath%22%3A%22div-a-h3-em3%22%7D
*/

#include"ArduinoMovement.h"

void motor(char pwmpin,char anapin,char state,int val)
{
    pinMode(anapin, OUTPUT);   

  if(state==1)
  {  
    analogWrite(pwmpin,val);
    digitalWrite(anapin,1);
   }
  else if(state==2)
{  
   analogWrite(pwmpin,val);
   digitalWrite(anapin,0);
}
else if(state==0)
{
    analogWrite(pwmpin,0);
    digitalWrite(anapin,0);
}
}

void runfoward()   //前进
{
   motor(2,A8,2,210);
  motor(4,A4,2,190);
  motor(3,A3,1,50);
  motor(6,A6,2,200);
}
void runback()    //后退
{
  motor(2,A8,1,210);
  motor(4,A4,1,190);
  motor(3,A3,2,50);
  motor(6,A6,1,200);
}
void turnL()     //左转
{
  motor(2,A8,2,160);
  motor(4,A4,2,190);
  motor(3,A3,1,100);
  motor(6,A6,2,200);
}
void turnR()      //右转 
{
  motor(2,A8,2,210);
  motor(4,A4,2,140);
  motor(3,A3,1,50);
  motor(6,A6,2,150);
}
void stop()            //停止
{
  motor(1,A1,0,0);
  motor(4,A4,0,0);
  motor(3,A3,0,0);
  motor(6,A6,0,0); 
}

void turnVR()
{
  motor(2,A8,2,220);
  motor(4,A4,1,10);
  motor(3,A3,1,30);
  motor(6,A6,1,20);
}

void turnVL()
{
motor(2,A8,1,20);
  motor(4,A4,2,210);
  motor(3,A3,2,235);
  motor(6,A6,2,220);

}
/*void setup()
{
}
void loop()
{
   runfoward(180); 
   delay(1000);
   runback(180);
   delay(1000);
   turnL(180);
   delay(1000);
   turnR(180);
   delay(1000);
}
*/