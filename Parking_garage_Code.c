/*Automated Parking Garage by Ashraf Minhaj. www.youtube.com/c/fusebatti
* for any query please mail me at ashraf_minhaj@yahoo.com*/

#include<Servo.h>   //adding Servo library
Servo gate;        //you may open or close gate using a Servo motor
int slot1 = 5;   //Connect IR sensor on digital pin5 for sLOT 1
int slot2 = 4;   //sLot2 pin on digital 4 
int gateSensor = 3; //IR sensor on gate to arduino pin 3
int slot1_l = 13;
int slot2_l = 12;
int gate_grn = 11;
int gate_red = 10;


void setup() 
{
gate.attach(7);     //connecting the gate servo on pin 5
pinMode(slot1,INPUT);  //setting slot pins  & gate IR sensor as input to arduino
pinMode(slot2,INPUT);
pinMode(gateSensor,INPUT);
 pinMode(slot1_l,OUTPUT);
 pinMode(slot2_l,OUTPUT);
 pinMode(gate_grn,OUTPUT);
 pinMode(gate_red,OUTPUT);
 Serial.begin(9600);       //initialzing Serial monitor

}

void loop() 
{
 //the car arrives and sensor goes LOW

if(   !(digitalRead(gateSensor)) && digitalRead(slot1) && digitalRead(slot2))   //slot1 & slot2 empty
 {
  Serial.println("Welcome, Available: sLOT1, sLOT2");  //print slot1 and slo2 available
  digitalWrite(slot1_l,HIGH);
  digitalWrite(slot2_l,HIGH);
  delay(1000);
  digitalWrite(gate_grn,HIGH);
  gate.write(75); //gate will open after the dealy of 1 second
 }

 if( !(digitalRead(gateSensor)) && !(digitalRead(slot1)) && digitalRead(slot2))  //car on slot1,slot2 free
  {
      Serial.println("Welcome, Available: sLOT2");  // slo2 available
      digitalWrite(slot1_l,LOW);
      digitalWrite(slot2_l,HIGH);
      delay(1000);
      digitalWrite(gate_grn,HIGH);
     gate.write(75); //gate will open after the dealy of 1 second
  }
  
   if( !(digitalRead(gateSensor)) && digitalRead(slot1) && !(digitalRead(slot2)))     //car on slot2,slot1 free
   {
     Serial.println("Welcome, Available: sLOT1");  // slo1 available
      digitalWrite(slot1_l,HIGH);
      digitalWrite(slot2_l,LOW);
      delay(1000);
     digitalWrite(gate_grn,HIGH);
     gate.write(75); 
      delay(100);                //gate will open after the dealy of 1 second
   }
  

    if( !(digitalRead(gateSensor)) && !(digitalRead(slot1)) && !(digitalRead(slot2)))
     {
       Serial.println("Welcome, Parking Full");// No slot available
        digitalWrite(slot1_l,LOW);
        digitalWrite(slot2_l,LOW);
        delay(1000);
        digitalWrite(gate_red,HIGH);
        delay(100);
        digitalWrite(gate_red,LOW);
        delay(100);
        digitalWrite(gate_red,HIGH);
        delay(100);
        digitalWrite(gate_red,LOW);
        
        
     }
        
if( digitalRead(gateSensor))  //no input detected
    { Serial.println("Welcome");  
      gate.write(5);       //gate close
     digitalWrite(slot1_l,LOW);
     digitalWrite(slot2_l,LOW);
     digitalWrite(gate_red,LOW);
     digitalWrite(gate_grn,HIGH);  //yellow/green light will blink from here
     delay(100);
     digitalWrite(gate_grn,LOW);
     delay(100);
     
    
    }

	}
