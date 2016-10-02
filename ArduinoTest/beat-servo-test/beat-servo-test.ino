#include <VarSpeedServo.h>
VarSpeedServo left;
VarSpeedServo right;
VarSpeedServo top;
VarSpeedServo bottom;
char c;
unsigned long time;
int buchang = 110;

int interval1 ;
int time5 = 464;
int time6 = 557;
int time7 = 650;
int time8 = 743;
int time9 = 836;
int k =0;
int m =0;

 
void setup(){
  //Serial.begin(9600);
  left.attach(8);
  right.attach(9);
  top.attach(10);
  bottom.attach(11);
  Serial.begin(9600);

}
void loop(){
 if (Serial.available()>0)
 {
    c=Serial.read();
    Serial.println(c);
    if (c =='s'){  // if stop, reset all
      delay(100);
      left.write(90,255,true); 
      right.write(90,255,true); 
      top.write(90,255,true); 
      bottom.write(90,255,true);     
    }
    
    else if (c=='9')
     {  
       randomdance2(time9);
      } 
      else if (c=='8')
     {  
       randomdance2(time8);  
      } 
      else if (c=='7')
     {  
      randomdance2(time7);
      } 
      else if (c=='6')
     {  
      randomdance2(time6);  
      } 
      if (c=='5')
     {  
       randomdance2(time5);   
      } 
 
  }
}


int shake( VarSpeedServo servo,int time_n,int turn_time, int turn_degree)
{
       if (k==0)
       {
         delay(time_n-turn_time-buchang);
         servo.write(turn_degree,255,true);  
         k=1;
        }
        else if (k==1)
        {
          delay(time_n-turn_time-buchang);
         servo.write(90,255,true); 
          k=0;
         }
  return 0;
}

int randomdance(int time_n)
{
  m = m + 1;
  if (m<=4){
    shake(top,time_n,50,110);
  }
  else if (m<=8){
    shake(left,time_n,50,120);
  }
  else if (m<=12){
    shake(right,time_n,50,60);
  }
  else if (m<=16){
   if (k==0)
       {
         delay(time_n-50-buchang);
         left.write(120,255,true);  
         right.write(60,255,true); 
         k=1;
        }
        else if (k==1)
        {
          delay(time_n-50-buchang);
         left.write(90,255,true); 
          right.write(90,255,true); 
          k=0;
         }
  }
  else if (m<=20){
    shake(bottom,time_n,70,130);
  }
 else if (m<=23){
    shake(bottom,time_n,70,50);
  }
  else if (m=24){
    shake(bottom,time_n,70,50);
    m =0 ;
  }
  return 0;
  }

int randomdance2(int time_n)
{
  m = m + 1;
  if (m<=4){
    shake(top,time_n,50,120);
  }
  else if (m<=8){
    shake(left,time_n,50,120);
  }
  else if (m<=12){
    shake(right,time_n,50,60);
  }
  else if (m<=15){
   if (k==0)
       {
         delay(time_n-50-buchang);
         left.write(120,255,true);  
         right.write(60,255,true); 
         k=1;
        }
        else if (k==1)
        {
          delay(time_n-50-buchang);
         left.write(90,255,true); 
          right.write(90,255,true); 
          k=0;
         }
  }
   else if (m=16){
   if (k==0)
       {
         delay(time_n-50-buchang);
         left.write(120,255,true);  
         right.write(60,255,true); 
         k=1;
        }
        else if (k==1)
        {
          delay(time_n-50-buchang);
         left.write(90,255,true); 
          right.write(90,255,true); 
          k=0;
         }
         m=0;
  }
 
  return 0;
  }

