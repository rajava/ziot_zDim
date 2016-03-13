/*
 * *************************************************************
 * zDi Alpha                                                   *
 * **********                                                  *
 * Description: Smart assistance / new dimension for           *
 *              visually challenged people!                    *
 * - Distance sensing                                          *
 * - Trigger camera                                            *
 * - OCR                                                       *
 * - Text to speech                                            *
 * *************************************************************
 * Owner      : Raja Sundaram                                  *
 * Developer  : Diwakar M Annamalai                            *
 * Date       : 13 March 2016                                  *
 * *************************************************************
 */

#define touchPin 2 
#define echoPin 12 
#define trigPin 13

#include <Servo.h>

Servo servo3;
int servoangle;
int repeattouchstate;

void setup() 
{ 
  Serial.begin (9600); 
  Serial1.begin (9600);  
  servo3.attach(3);
  pinMode(touchPin, INPUT);
  pinMode(echoPin, INPUT); 
  pinMode(trigPin, OUTPUT); 
  servoangle=30;
  servo3.write(servoangle);
  digitalWrite(trigPin, LOW); 
  repeattouchstate = 0;
}

void loop() 
{ 
  long duration; 
  int touchstate;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  if (duration < 5000 && duration!=0)
  {
    alert();
  }
  touchstate = digitalRead(touchPin);
  delayMicroseconds(10); 
  if (touchstate == 1 && repeattouchstate != 1)
  {
    repeattouchstate = 1;
    capture();
    //while(!capture());
  }
  else if (touchstate == 0 && repeattouchstate == 1)
  {
    repeattouchstate = 0;
  }
  //Serial.print(duration);
  //Serial.println(" ms");  
  delay(50); 
}

void alert()
{
  if (servoangle == 30)
  {
    servoangle = 120;
  }
  else
  {
    servoangle=30;
  }
  servo3.write(servoangle);
  delay(250);
}

boolean capture()
{
  int currentservoangle=servoangle;
  Serial1.println('C');
  Serial1.flush();
  servo3.write(currentservoangle-10);
  delay(20);
  servo3.write(servoangle+10);
  delay(20);
}

