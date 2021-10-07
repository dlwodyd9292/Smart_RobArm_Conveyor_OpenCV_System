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

void RedMotorOn();
void BlueMotorOn();

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
  myservo3.write(90);
  myservo4.write(135);
  myservo5.write(95);
  myservo6.write(90);  

  pinMode(OnPin, INPUT);
  pinMode(OffPin, INPUT);
  pinMode(FinPin, OUTPUT);
}

void loop() 
{  
  if(digitalRead(OnPin) == HIGH && digitalRead(OffPin) == LOW)
  {   
     RedMotorOn();
     delay(1000);
     digitalWrite(FinPin, HIGH);
     delay(1000);
     digitalWrite(FinPin, LOW);  
  }             
  else if(digitalRead(OnPin) == LOW && digitalRead(OffPin) == HIGH)
  {
     BlueMotorOn();
     delay(1000);
     digitalWrite(FinPin, HIGH);
     delay(1000);
     digitalWrite(FinPin, LOW);  
  }   
}

void RedMotorOn()
{ 
  delay(1000);
  myservo4.write(125); // BOX Red
  delay(1000);
  myservo1.write(80);
  delay(1000);
  myservo4.write(135);
  delay(1000);
  myservo6.write(30);
  delay(1000);
  
   //return
  myservo1.write(0);
  delay(1000);
  myservo4.write(135);
  delay(1000);
  myservo6.write(90);
  delay(1000);
}

void BlueMotorOn()
{ 
  delay(1000);
  myservo4.write(125); // BOX Blue
  delay(1000);
  myservo1.write(80);
  delay(1000);
  myservo4.write(135);
  delay(1000);
  myservo6.write(0);
  delay(1000);
  
   //return
  myservo1.write(0);
  delay(1000);
  myservo4.write(135);
  delay(1000);
  myservo6.write(90);
  delay(1000);
}

