const int TrigPin1 = 8;
const int EchoPin1 = 9;
int dl;
const int TrigPin2 = 10;
const int EchoPin2 = 11;
int dm;
const int TrigPin3 = 12;
const int EchoPin3 = 13;
int dr;

const int ENA = 6;
const int IN1 = 7;
const int IN2 = 5;
const int ENB = 3;
const int IN3 = 4;
const int IN4 = 2;

int history[500];
int k = 0;

int motor_speed = 90; //[0,255]
int motor_speed2 = 100;
int turn_time = 600;
int turn_time2 = 800;
int turn_time3 = 1000;
int turn_time4 = 1200;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode(TrigPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(TrigPin3, OUTPUT);
  pinMode(EchoPin3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TrigPin1, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin1, LOW);
  dl = pulseIn(EchoPin1, HIGH) / 58.0; //将回波时间换算成cm
  delay(50);
   Serial.print("left=");
  Serial.print(dl);
   Serial.print("  ");

  digitalWrite(TrigPin2, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);
  dm = pulseIn(EchoPin2, HIGH) / 58.0; //将回波时间换算成cm
  delay(50);
   Serial.print("middle=");
  Serial.print(dm);
   Serial.print("  ");

  digitalWrite(TrigPin3, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin3, LOW);
  dr = pulseIn(EchoPin3, HIGH) / 58.0; //将回波时间换算成cm
  delay(50);
   Serial.print("right=");
  Serial.println(dr);


  
  int min_dis1 = min(dr,dm);
  int min_dis = min(min_dis1, dl);

digitalWrite(IN1, HIGH);//forwards
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);//forwards
digitalWrite(IN4, LOW);
analogWrite(ENB,motor_speed);
analogWrite(ENA,motor_speed2);

if ((dr<25)&&(dm<35)&&(dl<25))
{
  k = k+1;
  history[k]=1;
   //when meet obstacles, stop a while
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(700);

    digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);//left turn forwards
     digitalWrite(IN4, HIGH);
     analogWrite(ENA,motor_speed2);
     analogWrite(ENB,motor_speed);
     delay(turn_time4);
  
   digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  }
  
 if (min_dis < 45)
{
 k = k +1;
 //when meet obstacles, stop a while
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(700);

  if ( (k>3)&&(history[k-1]==0)&&(history[k-2]==1)&&(history[k-3]==0)&&(history[k-4]==1))
  {
     history[k]=1;
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);//left turn forwards
     digitalWrite(IN4, HIGH);
     analogWrite(ENA,motor_speed2);
     analogWrite(ENB,motor_speed);
     delay(turn_time2);
    }

   if ( (k>3)&&(history[k-1]==1)&&(history[k-2]==0)&&(history[k-3]==1)&&(history[k-4]==0))
 {
   history[k]=0;
    digitalWrite(IN1, LOW);
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);//left turn forwards
     digitalWrite(IN4, LOW);
     analogWrite(ENA,motor_speed2);
     analogWrite(ENB,motor_speed);
     delay(turn_time2);
  
  }
  if (dr == min_dis)
  {
    history[k]=1;
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);//left turn forwards
     digitalWrite(IN4, HIGH);
     analogWrite(ENA,motor_speed2);
     analogWrite(ENB,motor_speed);
     delay(turn_time);
  }


  if (dl == min_dis)
  {
    
    history[k]=0;
    digitalWrite(IN1, LOW);
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);//left turn forwards
     digitalWrite(IN4, LOW);
     analogWrite(ENA,motor_speed2);
     analogWrite(ENB,motor_speed);
     delay(turn_time);
    }

  if (dm == min_dis)
  {
    history[k]=0;
    digitalWrite(IN1, LOW);
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);//left turn forwards
     digitalWrite(IN4, LOW);
     analogWrite(ENA,motor_speed2);
     analogWrite(ENB,motor_speed);
     delay(turn_time2);
    }
  
   digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}// turn end



  
}
