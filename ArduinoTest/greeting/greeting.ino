#include <VarSpeedServo.h>
VarSpeedServo left;
VarSpeedServo right;
VarSpeedServo top;
VarSpeedServo bottom;

const int TrigPin1 = 24;
const int EchoPin1 = 22;
int dl;
const int TrigPin2 = 28;
const int EchoPin2 = 26;
int dm;
const int TrigPin3 = 30;
const int EchoPin3 = 32;
int dr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  left.attach(8);
  right.attach(9);
  top.attach(10);
  bottom.attach(11);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  right.write(130,150,true);
//  left.write(40,150,true);
//  delay(200);
//  bottom.write(120,50,true);
//  delay(400);
//  bottom.write(60,50,true);
//  delay(400);
//  bottom.write(120,50,true);
//  delay(400);
//  bottom.write(60,50,true);
//  delay(200);
//  bottom.write(90,50,true);
//  delay(200);
//  left.write(90,200,true); 
//  right.write(90,200,true); 
//  delay(1000);
    digitalWrite(TrigPin1, LOW); 
  delayMicroseconds(2);
  digitalWrite(TrigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin1, LOW);
  dl = pulseIn(EchoPin1, HIGH) / 58.0; 
  delay(50); 
  Serial.print("left = ");
  Serial.println(dl);

  digitalWrite(TrigPin2, LOW); 
  delayMicroseconds(2);
  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);
  dm = pulseIn(EchoPin2, HIGH) ;
  delay(50);
  Serial.print("middle = ");
  Serial.println(dm);
  
  digitalWrite(TrigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin3, LOW);
  dr = pulseIn(EchoPin3, HIGH) ;
  delay(50);
  Serial.print("right = ");
  Serial.println(dr);

  
  

}
