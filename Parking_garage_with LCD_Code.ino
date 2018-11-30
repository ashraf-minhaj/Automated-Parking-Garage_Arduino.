/* Automated Parking Garage Version2
 * by Ashraf Minhaj. www.youtube.com/c/fusebatti
 * for any query please mail me at ashraf_minhaj@yahoo.com
 *
 * Modified code to use with I2C LCD Display on 2nd November 2018
 * Display: 20x4 I2C lcd display
 * you can use with 16x2 lcd too with or without I2C [I2C is recommended for less pins]
 */

/*
 * connect LCD SDA to arduino analogIn 4
 * LCD SCL to arduino analogIn 5
 * VCC to 5V source, GND to ground.
 */

#include <LiquidCrystal_I2C.h>  //I2C display library
#include<Servo.h>   //adding Servo library

LiquidCrystal_I2C lcd(0x27,20,4); //declare lcd display with I2C address for 20x4 lcd

Servo gate;        //servo name

int slot1 = 5;     //Connect IR sensor on digital pin5 for sLOT 1
int slot2 = 4;     //sLot2 pin on digital 4 
int gateSensor = 3; //IR sensor on gate to arduino pin 3


void setup() 
{
 gate.attach(7);       //connecting the gate servo on pin 5
 pinMode(slot1,INPUT);  //setting slot pins  & gate IR sensor as input to arduino
 pinMode(slot2,INPUT);
 pinMode(gateSensor,INPUT);
      
 lcd.init();     //initialize lcd 
 lcd.backlight(); //lcd background light

}

void loop() 
{
     //the car arrives and sensor goes LOW

   if( !(digitalRead(gateSensor)) && digitalRead(slot1) && digitalRead(slot2))   //slot1 & slot2 empty
     {
      lcd.setCursor(0,1);   //first column second row
      lcd.print("Available: sLOT1, sLOT2");  //show slot1 and slo2 available
      
      delay(1000);
      gate.write(75); //gate will open after the dealy of 1 second
      delay(100);   //little delay for the servo to move there
     }

   if( !(digitalRead(gateSensor)) && !(digitalRead(slot1)) && digitalRead(slot2))  //car on slot1,slot2 free
      {
         lcd.setCursor(0,1);   //first column second row
         lcd.print("Available: sLOT2");  // slo2 available
         
         delay(1000);
         gate.write(75); //gate will open after the dealy of 1 second
         delay(100); 
      }
      
   if( !(digitalRead(gateSensor)) && digitalRead(slot1) && !(digitalRead(slot2)))     //car on slot2,slot1 free
       {
         lcd.setCursor(0,1);   //first column second row
         lcd.print("Available: sLOT1");  // slo1 available

         delay(1000);
         gate.write(75);  //gate will open after the dealy of 1 second
         delay(100);                
       }
      

  if( !(digitalRead(gateSensor)) && !(digitalRead(slot1)) && !(digitalRead(slot2)))
        
        {
          lcd.clear();    //clear lcd
          lcd.setCursor(0, 2);  //first column 3rd row
          /*show message at the middle of the display*/
          lcd.print("Sorry,Parking Full");// No slot available
        }
             
  if( digitalRead(gateSensor))    // nothing on gate
        { 
          lcd.clear();    //clear lcd
          lcd.setCursor(0, 0);   //first column first row
          lcd.print("*Park Car Here*"); //show welcome message
          gate.write(5);       //gate close
        }
  
}
