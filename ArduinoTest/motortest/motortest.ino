
const int ENA = 2;
const int IN1 = 23;
const int IN2 = 25;
const int ENB = 3;
const int IN3 = 27;
const int IN4 = 29;

int motor_speed = 120;  //b
int motor_speed2 = 100; //a
int turn_time = 500;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
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
 digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(5000);
 
}
