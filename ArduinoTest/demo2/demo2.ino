#include <VarSpeedServo.h>
VarSpeedServo left;
VarSpeedServo right;
VarSpeedServo top;
VarSpeedServo bottom;
char c;
unsigned long time;

const int TrigPin1 = 24;
const int EchoPin1 = 22;
int dl;
const int TrigPin2 = 28;
const int EchoPin2 = 26;
int dm;
const int TrigPin3 = 30;
const int EchoPin3 = 32;
int dr;

const int ENA = 2;
const int IN1 = 23;
const int IN2 = 25;
const int ENB = 3;
const int IN3 = 27;
const int IN4 = 29;

int motor_speed = 120;  //<-- same view as owl
int motor_speed2 = 120; //-->

int interval1 ;
int time5 = 464;
int time6 = 557;
int time7 = 650;
int time8 = 743;
int time9 = 836;
int k =0; // 0 or 1
int b =0; // 0 or 1 or 2 or 3  
int j =0; // 0 or 1 or 2 or....7
int m =0;
int n =0;
int s =0;

int i = 0;

 
void setup(){
  //Serial.begin(9600);
  left.attach(8);
  right.attach(9);
  top.attach(10);
  bottom.attach(11);
  Serial.begin(9600);

}
void loop(){
if (i ==1){
   // put your main code here, to run repeatedly:
  digitalWrite(TrigPin1, LOW); 
  delayMicroseconds(2);
  digitalWrite(TrigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin1, LOW);
  dl = pulseIn(EchoPin1, HIGH) / 58.0; 
  delay(10); 

  digitalWrite(TrigPin2, LOW); 
  delayMicroseconds(2);
  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);
  dm = pulseIn(EchoPin2, HIGH) ;
  delay(10);
  
  digitalWrite(TrigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin3, LOW);
  dr = pulseIn(EchoPin3, HIGH) ;
  delay(10);

  int min_dis1 = min(dr,dm);
  int min_dis = min(min_dis1, dl);

  if (min_dis <= 90){
    gostop();
    i=0;
    no();
  }
}
  
 if (Serial.available()>0)
 {
    c=Serial.read();
    Serial.println(c);
    if (c =='s')
    {  // if stop, reset all
      delay(100);
      left.write(90,255,true); 
      right.write(90,255,true); 
      top.write(90,255,true); 
      bottom.write(90,255,true);   
     
    }
    
    else if (c=='9')
     {  
      dance9(180,510,time9,170);
      } 
      else if (c=='8')
     {  
      dance78(180,410);
      } 
      else if (c=='7')
     {  
      dance78(180,350);
      } 
      else if (c=='6')
     {  
      dance6(time6,170,255);  
      } 
      else if (c=='5')
     {  
       dance5(time5,170,255);   
      } 
      else if(c=='B')
    {
       turn_r(1000);
       delay(200);
       i=1;
       goahead();
  
    }
      else if(c=='C')
    {
       turn_l(1000);
       delay(200);
       i=1;
       goahead();
      }
      else if(c=='A')
    {
       top.write(110,200,true);  
       delay(150);
       top.write(70,200,true);  
       delay(150);
       top.write(110,200,true);  
       delay(150);
       top.write(70,200,true);  
       delay(150);
       top.write(90,200,true);        
      }
      
     else if(c=='E')
    {
        i = 1 ;
        goahead();      
      }

      else if(c=='F')
    {
        goback();
        delay(1500);
        gostop();  
      }

       else if(c=='D')
    {
 
      no();
      }  
        else if(c=='G')
    {
        right.write(130,150,true);
        left.write(40,150,true);
        delay(200);
        bottom.write(120,50,true);
        delay(400);
        bottom.write(60,50,true);
        delay(400);
        bottom.write(120,50,true);
        delay(400);
        bottom.write(60,50,true);
        delay(200);
        bottom.write(90,50,true);
        delay(200);
        left.write(90,200,true); 
        right.write(90,200,true); 
        delay(1000);
      }  
// else {
//  Serial.flush();
// }
  }
}

// ****************************   NODE   ***********************************
int node ( VarSpeedServo servo,int time_n, int turn_degree, int buchang, int s)  // node
{
       if (k==0)
       {
         delay(time_n-buchang);
         servo.write(turn_degree,s,true);  
         k=1;
        }
        else if (k==1)
        {
          delay(time_n-buchang);
         servo.write(90,s,true); 
          k=0;
         }
  return 0;
}
//********************************shake**********************************
int shake ( VarSpeedServo servo, int d1, int d2, int upspeed, int interval)  // shake
{
      servo.write(d1,upspeed,true);
      delay(interval);  
      servo.write(d2,255, true); 
}

//********************************shake two hands**********************************
int nodehand ( int time_n,int buchang, int s) // two hand down and up at the same time
{
  if (k==0)
       {
         delay(time_n-buchang);
         left.write(120,s,true);  
         right.write(60,s,true); 
         k=1;
        }
        else if (k==1)
        {
          delay(time_n-buchang);
          left.write(90,s,true); 
          right.write(90,s,true); 
          k=0;
         }
  }
  int nodehand2 ( int time_n,int buchang, int s) // two hand down and up at the same time
{
  if (k==0)
       {
         delay(time_n-buchang-10);
         left.write(50,s,true);  
         right.write(130,s,true); 
         k=1;
        }
        else if (k==1)
        {
          delay(time_n-buchang-10);
          left.write(90,s,true); 
          right.write(90,s,true); 
          k=0;
         }
  }


// **********************************move hands like wave**********************************
int wavehand( int time_n, int buchang, int s)
{
  if(b==0){
    delay(time_n-buchang);
    left.write(120,s,true);
    b=1;
  }
 else if(b==1){
    delay(time_n-buchang);
    right.write(60,s,true);
    b=2;
  }
  else if(b==2){
    delay(time_n-buchang);
    left.write(90,s,true);
    b=3;
  }
  else if(b==3){
    delay(time_n-buchang);
    right.write(90,s,true);
    b=0;
  }
}

int bottomnode ( int time_n, int buchang, int s) // bottom wave 
{
  if(b==0){
    delay(time_n-buchang);
    bottom.write(120,s,true);
    b=1;
  }
 else if(b==1){
    delay(time_n-buchang);
    bottom.write(90,s,true);
    b=2;
  }
 else if(b==2){
    delay(time_n-buchang);
    bottom.write(60,s,true);
    b=3;
  }
  else if(b==3){
    delay(time_n-buchang);
    bottom.write(90,s,true);
    b=0;
  }
}
//*******************bottomwave**************************************
int bottomwave ( int time_n, int buchang, int s) // bottom wave 
{
  if(j==0){
    delay(time_n-buchang);
    bottom.write(120,s,true);
    j=1;
  }
 else if(j==1){
    delay(time_n-buchang);
    bottom.write(150,s,true);
    j=2;
  }
 else if(j==2){
    delay(time_n-buchang);
    bottom.write(120,s,true);
    j=3;
  }
  else if(j==3){
    delay(time_n-buchang);
    bottom.write(90,s,true);
    j=4;
  }
  else if(j==4){
    delay(time_n-buchang);
    bottom.write(60,s,true);
    j=5;
  }
  else if(j==5){
    delay(time_n-buchang);
    bottom.write(30,s,true);
    j=6;
  }
  else if(j==6){
    delay(time_n-buchang);
    bottom.write(60,s,true);
    j=7;
  }
  else if(j==7){
    delay(time_n-buchang);
    bottom.write(90,s,true);
    j=0;
  }
}

// ***************************** dance 5555555555 *********************************
int dance5 (int time_n, int buchang, int s)
{
  m = m + 1;
  if (m<=4){
    node(top,time_n,120,buchang,s);
  }
  else if (m<=8){
    node(left,time_n,120,buchang,s);
  }
  else if (m<=12){
    node(right,time_n,60,buchang,s);
  }
  else if (m<=15){
   nodehand(time_n,buchang,s);
  }
   else if (m=16){
   nodehand(time_n,buchang,s);
   m=0;
  }
  return 0;
  }
//********************************** dance 66666666 ***********************************
int dance6 (int time_n, int buchang, int s)
{
  //insert
  m = m + 1;
  if (m<=4){
    node(top,time_n,120,buchang,s);
  }
  else if (m<=12){
    wavehand (time_n,buchang+40,s);
  }
  else if (m==13){
    bottom.write(140,s,true);
    wavehand (time_n,buchang+40,s);
  }
  else if (m<=16){
    wavehand (time_n,buchang+40,s);
  }
  else if (m==17){
    bottom.write(90,s,true);
    wavehand (time_n,buchang+40,s);
  }
  else if (m<=20){
    wavehand (time_n,buchang+40,s);
  }
   else if (m==21){
    bottom.write(40,s,true);
    wavehand (time_n,buchang+40,s);
  }
  else if (m<=24){
    wavehand (time_n,buchang+40,s);
  }
   else if (m==25){
    bottom.write(90,s,true);
    wavehand (time_n,buchang+40,s);
  }
  else if (m<=28){
    wavehand (time_n,buchang+40,s);
  }
  else if (m<=44){
    bottomnode( time_n,buchang,s);
  }
  else if (m<=60){
    nodehand2 (time_n,buchang+30,s);
  }
   else if (m<=76){
    bottomnode( time_n,buchang,s);
  }
  else if (m<=91){
    nodehand2 (time_n,buchang+20,s);
  }
  else if (m==92){
    nodehand2 (time_n,buchang+20,s);
    m=0;
  }

  
}
////******************************* dance77777888888 ******************************
int dance78 ( int upspeed, int interval)
{
  m = m +1;
  if (m<=4)
  {
    shake(top,80,110,upspeed,interval);
  }
  else if (m<=8)
  {
    shake(left,60,110,upspeed,interval-20);
  }
   else if (m<=11)
  {
    shake(right,110,60,upspeed,interval-20);
  }
   else if (m==12)
  {
    shake(right,110,60,upspeed,interval-20);
    m = 0;
  }
  return 0;
}

//*************************    dance   99999999999   ***********************************
int dance9 ( int upspeed, int interval, int time_n, int buchang)
{
  //insert
  n = n +1;
  if (n<=8)
  {
    shake(top,60,90,upspeed,interval);
  }
  else if (n<=12)
  {
   shake(left,40,90,upspeed,interval-20);
  }
  else if (n<=16)
  {
    shake(right,140,90,upspeed,interval-20);
  }
  else if (n<=24)
  {
    shake(top,60,90,upspeed,interval);
  } 
  else if (n<=40)
  {
    shakewave(upspeed,interval);
  }
  else if (n<=55)
  {
    bottomwave(time_n,buchang,upspeed);
  }
   else if (n==56)
  {
    bottomwave(time_n,buchang,upspeed);
    n=0;
  } 
  
}

int shakewave (int upspeed, int interval)
{
  if (s==0){
    shake(right,140,90,upspeed,interval-20);
    s=1;
  }
  else if (s==1){
    shake(top,60,90,upspeed,interval);
    s=2;
  }
  else if (s==2){
    shake(left,40,90,upspeed,interval-20);
    s=3;
  }
   else if (s==3){
    shake(top,60,90,upspeed,interval);
    s=0;
  }
}

void goahead(){
  analogWrite(ENB,motor_speed);
  analogWrite(ENA,motor_speed2);
  digitalWrite(IN1, HIGH);//forwards
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);//forwards  
  digitalWrite(IN4, HIGH); 
}

void goback(){
  analogWrite(ENB,motor_speed);
  analogWrite(ENA,motor_speed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW); 
}

void gostop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
int turn_l (int d){
  analogWrite(ENB,motor_speed);
  analogWrite(ENA,motor_speed2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW); 
  delay(d);
  gostop();
}
int turn_r (int d){
  analogWrite(ENB,motor_speed);
  analogWrite(ENA,motor_speed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH); 
  delay(d);
  gostop();
}

void no(){
  bottom.write(120,180,true);
  delay(50);
  bottom.write(60,180,true);
  delay(100);
  bottom.write(120,180,true);
  delay(100);
  bottom.write(60,180,true);
  delay(50);
  bottom.write(90,180,true);
}

