#include < dht.h >//Import DHt11 library
#include <LiquidCrystal.h> //import LCD libray 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// Initilize LCD library with 4bit ode
#define dht_apin A0 // sensor is connected to Analog Pin
dht DHT;// DHT variable to handle sensor functions
void setup()
{
  lcd.begin(16, 2); // LCD character display
}
void loop() {
  delay(2000); //wait a sec (recommended for DHT11)
  DHT.read11(dht_apin);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);// Print DHT11 reading for Humidity
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);// Print DHT11 reading for Temperature
  lcd.setCursor(12, 1);
  lcd.print( (char)223); // displaying degree symbol (Â°).
  lcd.print("C")
}
