#include <VarSpeedServo.h>
VarSpeedServo myservo;
char c;


const int ENA = 3;
const int IN1 = 24;
const int IN2 = 26;
const int ENB = 2;
const int IN3 = 28;
const int IN4 = 30;

int motor_speed = 120;
int motor_speed2 = 100;
int turn_time = 1000;

void setup()
{
  myservo.attach(9); 
  Serial.begin(9600);
}
void loop()
{

  myservo.write(50,100,true);
  if(Serial.available() >0)
  {
    c=Serial.read();
    if(c=='B')
    {
   myservo.write(0,100,true);  
   delay(500);
  
    }
  if(c=='C')
    {
 myservo.write(107,100,true);  
   delay(500);
      
      }
  if(c=='A')
    {
   myservo.write(0,200,true);  
   delay(150);
   myservo.write(107,200,true);  
   delay(150);
   myservo.write(0,200,true);  
   delay(150);
   myservo.write(107,200,true);  
   delay(150);
      
      }
      
      if(c=='E')
    {
      analogWrite(ENB,motor_speed);
analogWrite(ENA,motor_speed2);
digitalWrite(IN1, HIGH);//forwards
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);//forwards  
digitalWrite(IN4, HIGH); 
delay(500);
 digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
      
      }

        if(c=='F')
    {
analogWrite(ENA,motor_speed2);
digitalWrite(IN1, LOW);//forwards
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);//backwards  
digitalWrite(IN4, LOW); //turn left
delay(500);
 digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
      
      }

        if(c=='D')
    {
      analogWrite(ENB,motor_speed);
analogWrite(ENA,motor_speed2);
digitalWrite(IN1, HIGH);//forwards
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);//backwards  
digitalWrite(IN4, LOW); //turn left
delay(turn_time);
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);//turn right
delay(turn_time);
digitalWrite(IN1, HIGH);//forwards
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);//backwards  
digitalWrite(IN4, LOW); //turn left
delay(turn_time);
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);//turn right
delay(turn_time);
 digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
      
      }   
  }
}
