
/*
 AvoidaceBot Version 1.9
 
 Written by: Pason Tanpaiboon
 March 2016
 
 This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 
 */

#include "SRF05.h"
SRF05 Sensor(3, 4, 200, 500);

int distance ;
int lastdistance ;

//Motor A
const int enableA = 5;
const int MotorA1 = 6;
const int MotorA2 = 7;

//Motor B
const int enableB = 8;
const int MotorB1 = 9;
const int MotorB2 = 10;


void setup() {

  Serial.begin(57600); // begin serial communitication  

  Sensor.Unlock = true; // SR04 timeout problem correction
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);  

  pinMode (enableB, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT);  
  pinMode(13, OUTPUT);//Red LED
  pinMode(2, OUTPUT);//Green LED

  digitalWrite (enableA, HIGH);
  digitalWrite (enableB, HIGH);
  delay (30);

}

void loop() {
  /////////////SRF05 liblary reading////////////////
  delay(30);
  if ( Sensor.Read() > -1 ) {
    // New distance reading!
    if ( Sensor.Distance == 0 ) {
      digitalWrite(13, LOW);
      delay(15);
      digitalWrite(2, LOW);
      delay(15);
      Serial.println("----------error----------"); 
    } 
    else {
      distance = Sensor.Distance;
    }
  }
  Serial.print("distance---");
  Serial.println(distance);

  /*****************Clear long path*********************************************************************/
  if ( distance >= 54  ) {
    digitalWrite(13, LOW);
    delay(15);
    digitalWrite(2, HIGH);
    delay(15);
    Serial.println("----Clear long path----");

    Straight();
    delay(200);

    Forward();
    delay(150);

    Stop();
    delay(200);

  }

  /*****************Clear short path*********************************************************************/
  if ( distance < 54 && distance > 32 ) {
    digitalWrite(13, LOW);
    delay(15);
    digitalWrite(2, HIGH);
    delay(15);
    Serial.println("----Clear short path----");

    Turnright();//ready to change direction
    delay(180);

    Forward();

    Turnright();
    delay(180);


    Stop();
    delay(300);

    Straight();
    delay(200);

  }

  /*****************Avoidance zone*********************************************************************/
  if ( 10 < distance && distance <= 32 ) {  
    digitalWrite(13, HIGH);
    delay(15);
    digitalWrite(2, HIGH);
    delay(15);
    Serial.println("----Avoidance zone----");

    Stop();
    delay(30);

    Turnleft();
    delay(210);

    Backward();//return1
    Serial.println (" return  ");

    Turnleft();
    delay(210);

    Stop();
    delay(30);

    Straight();
    delay(200);
  }

  /*****************Avoidance close zone*********************************************************************/
  if ( 0 < distance && distance <= 10 ) {  
    digitalWrite(13, HIGH);
    delay(15);
    digitalWrite(2, LOW);
    delay(15);
    Serial.println("----Avoidance close zone----");

    Stop();
    delay(30);

    Straight();
    delay(100);

    Turnleft();
    delay(320);

    Backward();//return

    Turnleft();
    delay(320);

    Stop();
    delay(30);

    Forward();//brake
    delay(30);

    Stop();
    delay(30);

    Straight();
    delay(100);

  }

}//loop end
/*****************Steering motor Right*********************************************************************/
void Turnright() {

  digitalWrite (enableA,HIGH);
  analogWrite(enableA, 150);
  digitalWrite (MotorA1,HIGH);
  digitalWrite (MotorA2,LOW);  
  Serial.println (" Turnright ");
}

/*****************Steering motor Left*********************************************************************/
void Turnleft() {

  digitalWrite (enableA,HIGH);
  analogWrite(enableA, 200);
  digitalWrite (MotorA1,LOW);
  digitalWrite (MotorA2,HIGH);  
  Serial.println (" Turnleft ");
}
/*****************Steering motor nutral*********************************************************************/
void Straight()  
{
  digitalWrite (enableA,LOW);
  analogWrite(enableA, 150);
  digitalWrite (MotorA1,LOW);
  digitalWrite (MotorA2,LOW);
  Serial.println (" Straight ");
}
/*****************Driving motor Forward*********************************************************************/
void Forward() {

  analogWrite(enableB, 100);// 
  digitalWrite (enableB,HIGH);
  digitalWrite (MotorB1,HIGH);
  digitalWrite (MotorB2,LOW);  
  Serial.println (" Forward "); 
}

/*****************Driving motor Backward*********************************************************************/
void Backward() {

  analogWrite(enableB, 100);
  digitalWrite (enableB,HIGH);
  digitalWrite (MotorB1,LOW);
  digitalWrite (MotorB2,HIGH);  
  Serial.println (" Backward ");
}
/*****************Driving motor stop*********************************************************************/
void Stop(){

  digitalWrite (enableB,LOW);
  digitalWrite (MotorB1,LOW);
  digitalWrite (MotorB2,LOW);  
  Serial.println (" Stop ");
}




























