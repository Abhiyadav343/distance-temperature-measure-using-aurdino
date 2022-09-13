#include <LiquidCrystal.h>//Load Liquid Crystal Library
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 6 // Data wire is plugged into pin 6 on the Arduino 

OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire);   // Pass our oneWire reference to Dallas Temperature.

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);  //Create Liquid Crystal Object called LCD

int trigPin = 9; //Sensor Trip pin connected to Arduino pin 9
int echoPin = 7; //Sensor Echo pin connected to Arduino pin 7
int myCounter = 0; //declare your variable myCounter and set to 0

float pingTime;  //time for ping to travel from the sensor to the target and return
float targetDistance; //Distance to Target in Centimeters
float speedOfSound = 776.5; //Speed of sound in miles per hour



void setup() {

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  LCD.begin(16, 2); //Tell Arduino to start your 16x2 LCD
  LCD.setCursor(0, 0); //Set LCD cursor to upper left corner, column 0, row 0
  LCD.print("Distance:");  //Print Message on First Row

  sensors.begin();   // Start up the library

  pinMode(8, OUTPUT);  //pin  8, 10, 13 output pins
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
}
void loop() {


  digitalWrite(trigPin, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(15); //Delay in high state
  digitalWrite(trigPin, LOW); //ping has now been sent
  delayMicroseconds(10); //Delay in high state

  pingTime = pulseIn(echoPin, HIGH);  //pingTime in microceconds
  pingTime = pingTime / 1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime = pingTime / 3600; //convert pingtime to hours by dividing by 3600 (seconds in an hour)
  targetDistance = speedOfSound * pingTime; //This will be in miles, since we declared the speed of sound as kilometers per hour; although we're going to convert it back to centimeters
  targetDistance = targetDistance / 2; //Remember ping travels to the target and back from the target, so you must divide by 2 for actual target distance.
  targetDistance = targetDistance * 160934.4; //Convert miles to centimeters by multipling by 160934,4
  sensors.requestTemperatures(); // Send the command to get temperature readings


  LCD.setCursor(10, 0); //Set the cursor to the tenth column of the first row
  LCD.print("                "); //Print blanks to clear the row
  LCD.setCursor(10, 0);  //Set Cursor again to the tenth column of the first row
  LCD.print((int) (targetDistance + 0.5)); //Print measured distance
  LCD.print("cm ");  //Print your units
  LCD.setCursor(0, 1); //Set the cursor to the first column of the second row
  LCD.print("                "); //Print blanks to clear the row
  LCD.setCursor(0, 1);  //Set Cursor again to the first column of the second row


  if (targetDistance > 40) {
    LCD.print("LEV LOW  ");
    LCD.print(sensors.getTempCByIndex(0));
    LCD.print((char)223);
    LCD.print ("C");
  }
  else if (targetDistance < 40 && targetDistance > 20) {
    LCD.print("LEV MED  ");
    LCD.print(sensors.getTempCByIndex(0));
    LCD.print((char)223);
    LCD.print ("C");
    
  }
  else (targetDistance < 20); {
    LCD.print ("LEV HIGH ");
    LCD.print(sensors.getTempCByIndex(0));
    LCD.print((char)223);
    LCD.print ("C");
  }

  delay(2000);


  if (targetDistance > 40) {
    digitalWrite (13, HIGH);  //Green LED ON
  }
  else {
    digitalWrite(13, LOW);   //Green LED OFF
  }

  if (targetDistance < 40 && targetDistance > 20) {
    digitalWrite (8, HIGH);   //Yellow LED ON
  }
  else {
    digitalWrite(8, LOW);    //Yellow LED OFF
  }

  if (targetDistance < 20) {
    digitalWrite(10, HIGH);   //Red LED ON
    delay(2000);
    digitalWrite(10, LOW);   //Red LED OFF
  }

  else {
    digitalWrite(10, LOW);   //Red LED OFF
  }


 }


