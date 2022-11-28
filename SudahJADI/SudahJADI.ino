 /*
This is code for LCD1602 Display with I2C module
 * watch the video for this code https://youtu.be/q9YC_GVHy5A
 
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * This library is based on work done by DFROBOT (www.dfrobot.com).
 */
/*
 *  This code has been modefied from the Arduino library
 *  Updated by Ahmad Nejrabi on Jan 20, 2018 at 11:09
 *  in Ajax, Ontario, Canada
 *  for Robojax.com
 *  
 *  This is code for LCD1602 Display with I2C module
 *  which can display text on the screen.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 12;
const int echoPin = 14;
const int jarakAwal = 73;
float duration, distance;

void setup()
{
  pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT); 
   Serial.begin(9600);
  // Robojax code for LCD with I2C
  // initialize the LCD, 
  lcd.begin();
 
  // Turn on the blacklight and print a message.
  lcd.backlight();
  // Robojax code for LCD with I2C


}

void loop()
{

  digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 
   digitalWrite(trigPin, HIGH); 
   delayMicroseconds(10); 
   digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distance = (duration*.0343)/2;
  
  //start of loop Robojax code for LCD with I2C
  lcd.clear();
  lcd.print("Nama : DEDI KONTOL");
  lcd.setCursor (0,1); // go to start of 2nd line
  lcd.print("Jarak : ");
  lcd.print(distance);

  //lcd.print(millis() / 1000);
  delay(500);
 //end of loopcode Robojax code for LCD with I2C
}
