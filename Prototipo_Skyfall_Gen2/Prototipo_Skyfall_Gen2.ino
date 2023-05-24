#include <SPI.h>
#include <MFRC522.h>
#include <SPI.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "dht.h"
#include <IRremote.h>  //INCLUSÃO DE BIBLIOTECA

#define countof(a) (sizeof(a) / sizeof(a[0]))

//DHT11
const int pinoDHT11 = A2;  //PINO ANALÓGICO UTILIZADO PELO DHT11
dht DHT;                   //VARIÁVEL DO TIPO DHT

//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

//RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

//RTC
ThreeWire myWire(6, 7, 5);  // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);


RtcDateTime now;
RtcDateTime backLightBegin;
RtcDateTime startup;
bool cortado;
bool unlocked;

//Caracteres Personalizados
byte smile[8] = { 0b00000, 0b00000, 0b01010, 0b00000, 0b10001, 0b01110, 0b00000, 0b00000 };
byte seta[8] = { 0b00000, 0b00000, 0b00100, 0b00100, 0b10101, 0b01110, 0b00100, 0b00000 };
byte coracao[8] = { 0b00000, 0b00000, 0b01010, 0b10101, 0b10001, 0b01010, 0b00100, 0b00000 };
byte umid[8] = { 0b00000, 0b00100, 0b01110, 0b11111, 0b11111, 0b11111, 0b01110, 0b00000 };
byte temp[8] = { 0b00100, 0b01010, 0b01011, 0b01010, 0b10001, 0b10001, 0b11111, 0b01110 };
byte clock[8] = { 0b00000, 0b01110, 0b10101, 0b10111, 0b10001, 0b01110, 0b00000, 0b00000 };
byte bateria[8] = { 0b11111, 0b11011, 0b10001, 0b11011, 0b11111, 0b11111, 0b10001, 0b11111 };
byte celsius[8] = { 0b00100, 0b01010, 0b00100, 0b00011, 0b00100, 0b00100, 0b00011, 0b00000 };
byte lock[8] = { 0b01110, 0b10001, 0b10001, 0b11111, 0b11011, 0b11011, 0b11111, 0b00000 };
byte unlock[8] = { 0b01110, 0b10001, 0b10000, 0b11111, 0b11011, 0b11011, 0b11111, 0b00000 };
byte date[8] = { 0b10101, 0b11111, 0b11011, 0b10011, 0b11011, 0b10001, 0b11111, 0b00000 };

//Controle IR
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results leituraControle;

//Controle Mapeado
const unsigned long tecla0 = 16738455;
const unsigned long tecla1 = 16724175;
const unsigned long tecla2 = 16718055;
const unsigned long tecla3 = 16743045;
const unsigned long tecla4 = 16716015;
const unsigned long tecla5 = 16726215;
const unsigned long tecla6 = 16734885;
const unsigned long tecla7 = 16728765;
const unsigned long tecla8 = 16730805;
const unsigned long tecla9 = 16732845;
const unsigned long tecla100 = 16750695;
const unsigned long tecla200 = 16756815;
const unsigned long teclaLess = 16769055;
const unsigned long teclaPlus = 16754775;
const unsigned long teclaEQ = 16748655;
const unsigned long teclaPrev = 16720605;
const unsigned long teclaNext = 16712445;
const unsigned long teclaPP = 16761405;
const unsigned long teclaCHL = 16753245;
const unsigned long teclaCH = 16736925;
const unsigned long teclaCHP = 16769565;


void setup() {
  cortado = false;
  unlocked = false;

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  Rtc.Begin();

  Serial.println("Aproxime o cartão para leitura...");
  Serial.print("Compilado em:  ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  //printDateTime(compiled);
  //Serial.println();

  if (Rtc.GetIsWriteProtected()) {
    Serial.println("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning()) {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  } else if (now > compiled) {
    Serial.println("RTC is newer than compile time. (this is expected)");
  } else if (now == compiled) {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }

  startup = Rtc.GetDateTime();
  now = startup;
  backLightBegin = startup;

  lcd.setBacklight(HIGH);
  lcd.createChar(1, lock);
  lcd.createChar(2, bateria);
  lcd.createChar(3, date);
  lcd.createChar(4, smile);
  lcd.createChar(5, umid);
  lcd.createChar(6, temp);
  lcd.createChar(7, clock);
  lcd.createChar(8, celsius);

  irrecv.enableIRIn();
}

void loop() {

  if (now + 20 < Rtc.GetDateTime()) {
    now = Rtc.GetDateTime();


    lcd.setCursor(0, 0);
    lcd.write((byte)7);
    String timeDate = ConvertToDateTime(now);
    lcd.print(timeDate.substring(0, 7));
    lcd.write((byte)3);
    lcd.print(timeDate.substring(7, 13));
    lcd.write((byte)1);
    DHT.read11(pinoDHT11);  //LÊ AS INFORMAÇÕES DO SENSOR


    lcd.setCursor(0, 1);
    lcd.write((byte)5);
    lcd.print(DHT.humidity, 0);  //IMPRIME NO DISPLAY O VALOR DE UMIDADE MEDIDO
    lcd.print("%");              //ESCREVE O TEXTO EM SEGUIDA
    lcd.print("        ");
    lcd.write((byte)6);
    lcd.print(DHT.temperature, 0);  //IMPRIME NO DISPLAY O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
    lcd.write((byte)8);

    printDateTime(now);
    Serial.println();

    Serial.print("Umidade: ");
    Serial.print(DHT.humidity);  //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
    Serial.print("%");
    Serial.print(" / Temperatura: ");
    Serial.print(DHT.temperature, 0);  //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
    Serial.println("*C");
  }

  if (now > backLightBegin + 30) {
    lcd.setBacklight(LOW);
  }

  if (irrecv.decode(&leituraControle)) {
    Serial.println(leituraControle.value);
    if (leituraControle.value == teclaCHL) {
      lcd.setBacklight(LOW);
    } else if (leituraControle.value == teclaCHP) {
      now = Rtc.GetDateTime();
      backLightBegin = now;
      lcd.setBacklight(HIGH);
    } else if (leituraControle.value == teclaEQ && cortado) {
      now = Rtc.GetDateTime();
      backLightBegin = now;
      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 1);
      lcd.print("                 ");
      lcd.setCursor(0, 1);
      lcd.print("Code: ");
      String senha = "";
      for (int i = 0; i < 4; i++) {
        String Tec = LeEsperaTecla(true);
        Serial.println(Tec);
        lcd.print(Tec);
        senha += Tec;
      }
      if (senha == "0802") {
        unlocked = true;
        if (cortado) {
          cortado = false;
          lcd.setCursor(0, 0);
          lcd.print("VEICULO LIBERADO!");
        }
        lcd.setBacklight(HIGH);
        backLightBegin = now;
        lcd.setCursor(0, 1);
        lcd.print("                 ");
        lcd.setCursor(0, 1);
        lcd.print("Bem Vindo!");
        lcd.createChar(1, unlock);
        Serial.println("Bem vindo!");
        delay(3000);
        now = now - 20;
      } else {
        lcd.setCursor(0, 1);
        lcd.print("                 ");
        lcd.setCursor(0, 1);
        lcd.print("Code incorreto!");
        delay(3000);
        now = now - 20;
      }
    } else if (leituraControle.value == teclaPP && unlocked) {
      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 1);
      lcd.print("                 ");
      lcd.setCursor(0, 1);
      lcd.print("Hora: ");
      String hora = "";
      for (int i = 0; i < 5; i++) {
        if (i == 2) {
          lcd.print(":");
          hora += ":";
        } else {
          String Tec = LeEsperaTecla(true);
          //Serial.println(Tec);
          lcd.print(Tec);
          hora += Tec;
        }
      }
      hora += ":00";
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.print("                 ");
      lcd.setCursor(0, 1);
      lcd.print("Data: ");
      String data = "";
      for (int i = 0; i < 8; i++) {
        if (i == 2 || i == 5) {
          lcd.print("/");
          data += "/";
        } else {
          String Tec = LeEsperaTecla(true);
          //Serial.println(Tec);
          lcd.print(Tec);
          data += Tec;
        }
      }
      Serial.println(hora);
      Serial.println(data);
      RtcDateTime ajuste = RtcDateTime(data, hora, true);
      printDateTime(ajuste);
      Rtc.SetDateTime(ajuste);
      now = Rtc.GetDateTime();
      backLightBegin = now;
      now -= 20;
      delay(300);
    }
    irrecv.resume();  //AGUARDA O RECEBIMENTO DE UM NOVO SINAL IR
  }

  if (!unlocked && !cortado && (Rtc.GetDateTime() - startup > 10)) {
    cortado = true;
    lcd.setBacklight(HIGH);
    backLightBegin = now;
    Serial.println("VEICULO CORTADO!! POSSIVEL TENTATIVA DE FURTO!");
    lcd.clear();
    lcd.print("VEICULO CORTADO!");
    lcd.setCursor(0, 1);
    lcd.print("POSSIVEL FURTO!");
    delay(3000);
  }



  //delay(10000); // ten seconds
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "A3 13 C4 A6")  //change here the UID of the card/cards that you want to give access
  {
    unlocked = true;
    if (cortado) {
      cortado = false;
      lcd.setCursor(0, 0);
      lcd.print("VEICULO LIBERADO!");
    }
    lcd.setBacklight(HIGH);
    backLightBegin = now;
    //lcd.setCursor(0,0);
    //lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("Fala Samuel!");
    lcd.createChar(1, unlock);

    Serial.println("Bem vindo!");
    delay(3000);
    now = now - 20;
  } else if (content.substring(1) == "8F 93 1E 29")  //change here the UID of the card/cards that you want to give access
  {
    unlocked = true;
    if (cortado) {
      cortado = false;
      lcd.setCursor(0, 0);
      lcd.print("VEICULO LIBERADO!");
    }
    lcd.setBacklight(HIGH);
    backLightBegin = now;
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("Bem Vindo!");
    lcd.createChar(1, unlock);

    Serial.println("Bem vindo!");
    delay(3000);
    now = now - 20;
  }

  else {
    unlocked = false;
    startup = now;
    Serial.println("Access denied");
    lcd.setBacklight(HIGH);
    backLightBegin = now;
    //lcd.setCursor(0,0);
    //lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("Access denied!");
    lcd.createChar(1, lock);
    delay(3000);
    now = now - 20;
  }
}

String LeEsperaTecla(bool numerico) {
  irrecv.resume();
  while (!irrecv.decode(&leituraControle)) {}
  if (leituraControle.value == tecla0) {
    return "0";
  } else if (leituraControle.value == tecla1) {
    return "1";
  } else if (leituraControle.value == tecla2) {
    return "2";
  } else if (leituraControle.value == tecla3) {
    return "3";
  } else if (leituraControle.value == tecla4) {
    return "4";
  } else if (leituraControle.value == tecla5) {
    return "5";
  } else if (leituraControle.value == tecla6) {
    return "6";
  } else if (leituraControle.value == tecla7) {
    return "7";
  } else if (leituraControle.value == tecla8) {
    return "8";
  } else if (leituraControle.value == tecla9) {
    return "9";
  } else if (leituraControle.value == tecla100 && !numerico) {
    return "100+";
  } else if (leituraControle.value == tecla200 && !numerico) {
    return "200+";
  } else if (leituraControle.value == teclaLess && !numerico) {
    return "-";
  } else if (leituraControle.value == teclaPlus && !numerico) {
    return "+";
  } else if (leituraControle.value == teclaEQ && !numerico) {
    return "EQ";
  } else if (leituraControle.value == teclaPrev && !numerico) {
    return "Prev";
  } else if (leituraControle.value == teclaNext && !numerico) {
    return "Next";
  } else if (leituraControle.value == teclaPP && !numerico) {
    return "PP";
  } else if (leituraControle.value == teclaCHL && !numerico) {
    return "CH-";
  } else if (leituraControle.value == teclaCH && !numerico) {
    return "CH";
  } else if (leituraControle.value == teclaCHP && !numerico) {
    return "CH+";
  } else {
    return LeEsperaTecla(numerico);
  }
}


void printDateTime(const RtcDateTime& dt) {
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second());
  Serial.println(datestring);
}
String ConvertToDateTime(const RtcDateTime& dt) {
  char datestring[20];
  unsigned int ano = dt.Year() - 2000;
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u:%02u  %02u/%02u "),
             dt.Hour(),
             dt.Minute(),
             dt.Day(),
             dt.Month());
  return datestring;
}