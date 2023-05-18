/*
 * 
 * All the resources for this project: https://randomnerdtutorials.com/
 * Modified by Rui Santos
 * 
 * Created by FILIPEFLOP
 * 
 */
#include <SPI.h>
#include <MFRC522.h>
#include <SPI.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2);
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


ThreeWire myWire(6,7,5); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
RtcDateTime now;
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.init();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);


    lcd.setBacklight(HIGH);
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
    now = Rtc.GetDateTime();
}

void loop() 
{
  if(now+20 < Rtc.GetDateTime()){
    now = Rtc.GetDateTime();
    printDateTime(now);
    Serial.println();
    lcd.setCursor(0,0);
    lcd.print(ConvertToDateTime(now));
    lcd.setCursor(0,1);
    lcd.print("                 ");
  }


    //delay(10000); // ten seconds
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
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "A3 13 C4 A6") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Bem vindo!");
    Serial.println();
    //lcd.clear();
    lcd.setBacklight(HIGH);
    //lcd.setCursor(0,0);
    //lcd.print(content.substring(1));
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("Fala Samuel!");
    delay(3000);
  }
  else if (content.substring(1) == "8F 93 1E 29") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Bem vindo!");
    Serial.println();
    lcd.setBacklight(HIGH);
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print(content.substring(1));
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("Bem Vindo!");
    delay(3000);
  }
 
 else   {
    Serial.println("Access denied");
    //lcd.clear();
    lcd.setBacklight(HIGH);
    //lcd.setCursor(0,0);
    //lcd.print(content.substring(1));
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("Access denied!");
    delay(3000);
  }
} 

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
String ConvertToDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    return datestring;
}