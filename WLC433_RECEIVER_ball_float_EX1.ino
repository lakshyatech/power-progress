// Water level control receiver software


#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int motorpin = 5;
int motorstate = 0;
int tankpin = 3;
int tankstate = 1;
int tankled = 4;
unsigned long period = 40000;
unsigned long time_now = 0;
unsigned long text = 0;
unsigned long tanktimer = 0;
unsigned long tankperiod = 15000;


void setup() { 
  Serial.begin(9600);
  mySwitch.enableReceive(0);
  pinMode(motorpin, OUTPUT);
  digitalWrite(motorpin, motorstate);
  pinMode(tankpin, INPUT);
  pinMode(tankled, OUTPUT);
  digitalWrite(tankled, !tankstate); 

  tanktimer = millis();
  Serial.println("start ok");
}
  
void loop(){ 
  
  if (mySwitch.available()) {
      //Serial.println("got message");
      text = mySwitch.getReceivedValue();
      Serial.println(text);
      mySwitch.resetAvailable();
      
   }
  
   if ((text == 15348721 && tankstate == 1) || text == 1613224){

        digitalWrite(tankled, 1);
        
    if (motorstate == 0){
        motorstate = 1;
        digitalWrite(motorpin,motorstate);
        }
        //Serial.println("resetting timer");
        time_now = millis();
        text = 0;
        digitalWrite(tankled, 0);
      }   
     
      
     if ( millis() >= tanktimer + tankperiod ) {
        //Serial.println("checking tank water");
        tankstate = digitalRead(tankpin);
        digitalWrite(tankled, !tankstate);
        tanktimer = millis();
    }
       if ((((millis() >= time_now + period) || (tankstate == 0)) && motorstate == 1) || text == 1613220) {
          motorstate = 0;
          digitalWrite(motorpin,motorstate);
      }   
   }
