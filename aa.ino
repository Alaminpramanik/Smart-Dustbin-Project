#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define PIN_TX    10    /* rx of Arduino (connect tx of gprs to this pin) */
#define PIN_RX    11   /* tx of Arduino (connect rx of gprs to this pin) */
#define BAUDRATE  9600
#define PHONE_NUMBER "01813180300"
#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH]; /* buffer for storing message */
char phone[11];         /* buffer for storing phone number */
char datetime[24];        /* buffer for storing phone number */
int8_t messageIndex = 0;

/* Create an object named Sim900_test of the class GPRS */
GPRS Sim900_test(PIN_TX,PIN_RX,BAUDRATE); 

//const int8_t lm35_pin = A1;
const int trigPin1 = 5;
const int echoPin1 = 6;


void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  //pinMode(4, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);     
  while(!Sim900_test.init())  /* Sim card and signal check, also check if module connected */ 
  {
      delay(1000);
      Serial.println("SIM900 initialization error");
  }  
  Serial.println("SIM900 initialization success");
  memset(message, 0, 160);
}

void loop() {
  long duration;
  float distance;

  //temp_adc_val = analogRead(lm35_pin);  /* Read temperature from LM35 */
  //temp_val = (temp_adc_val * 4.88);
  //temp_val = (temp_val/10);
  duration = pulseIn(echoPin1, HIGH);
  distance = 0.034*(duration/2);
  Serial.print("Temperature = ");
  Serial.print(distance);
  Serial.print(" Degree Celsius\n");
    if(distance<27)
    {
        Serial.println("Need to cool down");
        Serial.println("Calling to inform");
        Sim900_test.callUp(PHONE_NUMBER); /* Call */
        delay(25000);
        Sim900_test.hangup(); /* Hang up the call */
        int8_t count = 0;
        messageIndex = Sim900_test.isSMSunread(); /* Check if new message available */
              while( (messageIndex < 1) && !strstr( message,"Cool down") )  /* No new unread message */
              {
                  if(count == 5)
                  {
                      messageIndex = Sim900_test.isSMSunread();
                      break;
                  }
                  count++;
                  delay(5000);
                  messageIndex = Sim900_test.isSMSunread();
              }
              while(messageIndex > 0 )  /* New unread message available */
              {
                  Sim900_test.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);  /* Read message */
                    if(strstr( message,"Cool down"))
                    {
                        Serial.println("Turning fan ON");
                        digitalWrite(4, HIGH);
                        memset(message, 0, 160);
                    }
                  messageIndex = Sim900_test.isSMSunread();
              }         
        delay(10000);
    }
    else
    {
        Serial.println("Everything is fine");
      //  digitalWrite(4, LOW); 
    }
  delay(3000);
}
