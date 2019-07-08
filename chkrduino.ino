

//Servo myservo;  
int pos = 20;  

//this is for gate controll
const int trigPin1 = 5;
const int echoPin1 = 6;




long duration;
float distance;

void setup() 
{
 
//  pinMode(buzzer, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
//  pinMode(trigPin2, OUTPUT);
  //pinMode(echoPin2, INPUT); 
  
 
}

void loop() 
{
  Serial.begin(9600);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

   

  duration = pulseIn(echoPin1, HIGH);
  distance = 0.034*(duration/2);

  Serial.println(distance);
  
  
  delay(300);
}
