#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
 
void setup() 
{
  Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Place items close to the reader..."));

  pinMode(2, OUTPUT);

// set up the lcd 
  lcd.init();                      
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Welcome to");
  lcd.setCursor(3,1);
  lcd.print("KIDSATANG!");
}
void loop(){
   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  // Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "D3 BD E5 FA") //change here the UID of the card/cards that you want to give access
  {
    // Serial.println("Authorized access");
    Serial.println("Cornflake: 49 Baht");
    digitalWrite(2, HIGH); 
    delay(500);
    digitalWrite(2, LOW); 
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Cornflake");
    lcd.setCursor(0,1);
    lcd.print("49 Baht");
    // Serial.println();
    
  }
  else if (content.substring(1) == "53 04 DF FA")
  {
    Serial.println("Cookie: 79 Baht");  
    digitalWrite(2, HIGH); 
    delay(500);
    digitalWrite(2, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cookie");
    lcd.setCursor(0,1);
    lcd.print("79 Baht");
  }
  else if (content.substring(1) == "43 90 E9 FA")
  {
    Serial.println("Cupcake: 59 Baht");  
    digitalWrite(2, HIGH); 
    delay(500);
    digitalWrite(2, LOW); 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cupcake");
    lcd.setCursor(0,1);
    lcd.print("59 Baht");
  }
  else if (content.substring(1) == "EC EA 3C 02")
  {
    Serial.println("Croissant: 89 Baht");  
    digitalWrite(2, HIGH); 
    delay(500);
    digitalWrite(2, LOW); 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Croissant");
    lcd.setCursor(0,1);
    lcd.print("89 Baht");
  }
  else if (content.substring(1) == "53 D5 30 FB")
  {
    Serial.println("Coco Crunch: 1,999 Baht");  
    digitalWrite(2, HIGH); 
    delay(500);
    digitalWrite(2, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Coco Crunch");
    lcd.setCursor(0,1);
    lcd.print("1,999 Baht");
  }
  else
  {
    Serial.println("No item found");  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No item found");
  }
  delay(2000);
}