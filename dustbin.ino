#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

Servo myservo;  
int pos = 20;  

//this is for gate controll
const int trigPin1 = 5;
const int echoPin1 = 6;


const int led1 = 9;
const int led2 = 10;
const int led3 = 11;

//const int buzzer = 12;

long duration;
float distance;

void setup() 
{
  myservo.attach(12);
//  pinMode(buzzer, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
//  pinMode(trigPin2, OUTPUT);
  //pinMode(echoPin2, INPUT); 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  myservo.write(pos);

 
}

void loop() 
{
  //Serial.begin(9600);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

   

  duration = pulseIn(echoPin1, HIGH);
  distance = 0.034*(duration/2);

  
  if(distance < 15 && distance > 10){
    digitalWrite(led1,HIGH);
  }
  else if(distance < 10 && distance > 5){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
  }else if(distance < 5){
  digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  
  Serial.println("AT+CMGF=1");
    delay(500);
    Serial.println("AT+CMGS=\"+8801790555640\"");//Change the receiver phone number
    delay(500);
    Serial.print("Garbage is full");    //the message you want to send
    delay(500);
    Serial.write(26);
    delay(500);
  }
  else{
  digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  }
  
  delay(300);
}
