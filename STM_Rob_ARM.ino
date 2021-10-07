#include <Servo.h>

#define OnPin 8
#define OffPin 9
#define FinPin 10

Servo myservo1; 
Servo myservo2; 
Servo myservo3; 
Servo myservo4; 
Servo myservo5; 
Servo myservo6; 

void MotorOn(int del, int Angle1, int Angle2, int Angle3,
int Angle4, int Angle5, int Angle6);

void BeltStart();

void setup()
{ 
  myservo1.attach(A0);  
  myservo2.attach(A1);
  myservo3.attach(A2);
  myservo4.attach(A3);
  myservo5.attach(A4);
  myservo6.attach(A5);

  myservo1.write(0);
  myservo2.write(0);
  myservo3.write(0);
  myservo4.write(0);
  myservo5.write(0);
  myservo6.write(0);  

  pinMode(OnPin, INPUT);
  pinMode(OffPin, INPUT);
  pinMode(FinPin, OUTPUT);
}

void loop() 
{  
  if(digitalRead(OnPin) == HIGH && digitalRead(OffPin) == LOW)
  {   
     MotorOn(500, 30, 60, 90, 120, 150, 180);
     BeltStart_Red();
  }             
  else if(digitalRead(OnPin) == LOW && digitalRead(OffPin) == HIGH)
  {
     MotorOn(500, 180, 150, 120, 90, 60, 30);
     BeltStart_Blue();
  }   
}

void BeltStart_Red()
{
  digitalWrite(FinPin, HIGH);
  delay(1000);
  digitalWrite(FinPin, LOW);    
}

void BeltStart_Blue()
{
  digitalWrite(FinPin, HIGH);
  delay(1000);
  digitalWrite(FinPin, LOW);    
}

void MotorOn(int del, int Angle1, int Angle2, int Angle3, int Angle4, int Angle5, int Angle6)
{
     myservo1.write(Angle1);
     delay(del);
     myservo2.write(Angle2);
     delay(del);
     myservo3.write(Angle3);
     delay(del);
     myservo4.write(Angle4);
     delay(del);
     myservo5.write(Angle5);
     delay(del);
     myservo6.write(Angle5);
     delay(del);    
}
