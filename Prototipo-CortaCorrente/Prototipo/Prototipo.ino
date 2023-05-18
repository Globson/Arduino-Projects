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
#include "dht.h" //INCLUSÃO DE BIBLIOTECA

const int pinoDHT11 = A2; //PINO ANALÓGICO UTILIZADO PELO DHT11

dht DHT; //VARIÁVEL DO TIPO DHT

//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2);
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


ThreeWire myWire(6,7,5); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
RtcDateTime now;
RtcDateTime backLightBegin;
RtcDateTime startup;
bool cortado;
bool unlocked;

byte smile[8] = {0b00000,0b00000,0b01010,0b00000,0b10001,0b01110,0b00000,0b00000};
byte seta[8] = {0b00000,0b00000,0b00100,0b00100,0b10101,0b01110,0b00100,0b00000};
byte coracao[8] = {0b00000,0b00000,0b01010,0b10101,0b10001,0b01010,0b00100,0b00000};
byte umid[8] = {0b00000,0b00100,0b01110,0b11111,0b11111,0b11111,0b01110,0b00000};
byte temp[8] = {0b00100,0b01010,0b01011,0b01010,0b10001,0b10001,0b11111,0b01110};
byte clock[8] = {0b00000,0b00000,0b00000,0b01110,0b10101,0b10111,0b10001,0b01110};
byte bateria[8] = {0b11111,0b11011,0b10001,0b11011,0b11111,0b11111,0b10001,0b11111};
byte celsius[8] = {0b00100,0b01010,0b00100,0b00011,0b00100,0b00100,0b00011,0b00000};
//byte lock[8] = {0b01110,0b10001,0b10001,0b11111,0b11011,0b11011,0b11111,0b00000};
byte lock[8] = {0b00000,0b01110,0b10001,0b10001,0b11111,0b11011,0b11011,0b11111};
byte unlock[8] = {0b00000,0b01110,0b10001,0b10000,0b11111,0b11011,0b11011,0b11111};
void setup() 
{
  cortado = false;
  unlocked = false;
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.init();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);


    lcd.setBacklight(HIGH);
    lcd.createChar(1,lock); // creating the first character
    lcd.createChar(2,bateria); 
    lcd.createChar(3,coracao); // creating the third character
    lcd.createChar(4,smile); 
    lcd.createChar(5,umid); 
    lcd.createChar(6,temp); 
    lcd.createChar(7,clock); 
    lcd.createChar(8,celsius); 
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
    startup = Rtc.GetDateTime();
    now = startup;
    backLightBegin = startup;
}

void loop() 
{
  if(now+20 < Rtc.GetDateTime()){
    now = Rtc.GetDateTime();
    printDateTime(now);
    Serial.println();
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.write((byte)7);
    lcd.print(ConvertToDateTime(now));
    lcd.setCursor(0,1);
    //lcd.print("                 ");
    DHT.read11(pinoDHT11); //LÊ AS INFORMAÇÕES DO SENSOR
    Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(DHT.humidity); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
    Serial.print("%"); //ESCREVE O TEXTO EM SEGUIDA
    Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(DHT.temperature, 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
    Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL
    lcd.setCursor(0,1);
    lcd.write((byte)5);
    lcd.print(DHT.humidity, 1); //IMPRIME NO DISPLAY O VALOR DE UMIDADE MEDIDO
    lcd.print("%"); //ESCREVE O TEXTO EM SEGUIDA
    lcd.print("  ");
    lcd.write((byte)1);
    lcd.print(" ");
    lcd.write((byte)6);
    lcd.print(DHT.temperature, 1); //IMPRIME NO DISPLAY O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
    lcd.write((byte)8);
  }
  if(now > backLightBegin + 30){
    lcd.setBacklight(LOW);
  }
  if(!cortado && !unlocked && (now - startup > 45)){
    cortado = true;
    lcd.setBacklight(HIGH);
    backLightBegin = now;
    Serial.println("VEICULO CORTADO!! POSSIVEL TENTATIVA DE FURTO!");
    lcd.clear();
    lcd.print("VEICULO CORTADO!");
    lcd.setCursor(0,1);
    lcd.print("POSSIVEL FURTO!");
    delay(3000);
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
    unlocked = true;
    if(cortado){
          cortado = false;
          lcd.setCursor(0,0);
          lcd.print("VEICULO LIBERADO!");
    }
    Serial.println("Bem vindo!");
    Serial.println();
    //lcd.clear();
    lcd.setBacklight(HIGH);
    backLightBegin = now;
    //lcd.setCursor(0,0);
    //lcd.print(content.substring(1));
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("Fala Samuel!");
    lcd.createChar(1,unlock);
    delay(1500);
  }
  else if (content.substring(1) == "8F 93 1E 29") //change here the UID of the card/cards that you want to give access
  {
    unlocked = true;
    if(cortado){
          cortado = false;
          lcd.setCursor(0,0);
          lcd.print("VEICULO LIBERADO!");
    }
    Serial.println("Bem vindo!");
    Serial.println();
    lcd.setBacklight(HIGH);
    backLightBegin = now;
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print(content.substring(1));
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("Bem Vindo!");
    lcd.createChar(1,unlock);
    delay(1500);
  }
 
 else   {
    unlocked = false;
    startup = now;
    Serial.println("Access denied");
    //lcd.clear();
    lcd.setBacklight(HIGH);
    backLightBegin = now;
    //lcd.setCursor(0,0);
    //lcd.print(content.substring(1));
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("Access denied!");
    lcd.createChar(1,lock);
    delay(1500);
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
    unsigned int ano = dt.Year() - 2000;
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u:%02u  %02u/%02u/%02u"),
            dt.Hour(),
            dt.Minute(),
            dt.Day(),
            dt.Month(),
            ano);
    return datestring;
}