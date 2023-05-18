//Programa: Display LCD 16x2 e modulo I2C
//Autor: Arduino e Cia

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2);
 
void setup()
{
  lcd.init();
  lcd.setBacklight(HIGH);
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}
 
void loop()
{
  
  if(analogRead(0) > 0){
    Serial.print("A leitura em A0 é:");
    Serial.println(analogRead(0));
    lcd.setCursor(0,0);
    lcd.print("Leitura A0: ");
    lcd.print(analogRead(0));
    while(analogRead(0)>0){

    }
  }
   
  if(analogRead(1) > 0){
    Serial.print("A leitura em A1 é:");
    Serial.println(analogRead(1));
    lcd.setCursor(0,1);
    lcd.print("Leitura A1: ");
    lcd.print(analogRead(1));
    while(analogRead(1)>0){
      
    }
  }
  

}