#include <Thermistor.h>
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, INPUT);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // pinMode(A1,INPUT);
  pinMode(A2, OUTPUT);
}
Thermistor temp(1);
void segmentoAleatorio()
{
  long randNumber = random(7, 14);

  switch (randNumber)
  {
  case 7:
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 8:
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 9:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 10:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 11:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 12:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    break;
  case 13:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    break;
  }
}

long segmentoInfinitoAtual = 7;
void segmentoInfinito()
{
  switch (segmentoInfinitoAtual)
  {
  case 7:
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 8:
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 9:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 10:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    break;
  case 11:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 12:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 13:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    break;
  case 14:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    break;
  }
  if (segmentoInfinitoAtual <= 13)
  {
    segmentoInfinitoAtual++;
  }
  else
  {
    segmentoInfinitoAtual = 7;
  }
}

void colocaUmNumero(int num)
{
  switch (num)
  {
  case 0:
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    break;
  case 1:
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 2:
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH); //
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH); //
    break;
  case 3:
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    break;
  case 4:
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    break;
  case 5:
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    break;
  case 6:
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    break;
  case 7:
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 8:
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    break;
  case 9:
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    break;
  case 10:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    break;
  default:
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  }
}

void ledRGB(char S)
{
  switch (S)
  {
  case 'R':
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    break;
  case 'G':
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    break;
  case 'B':
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    break;
  default:
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    break;
  }
}

double bipbip(double tempo)
{
  analogWrite(A2, 130);
  digitalWrite(2, HIGH);
  double delay1 = 60;
  delay(delay1);
  analogWrite(A2, 0);
  digitalWrite(2, LOW);

  return delay1;
}

void animacao()
{
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
  segmentoInfinito();
  delay(50);
  colocaUmNumero(-1);
  delay(50);
}

void loop()
{
  // put your main code here, to run repeatedly:

  while (digitalRead(3) == 1)
  {
    for (int i = 0; i < 5; i++)
    {
      int temperature = temp.getTemp();
      Serial.print("Temperatura no Sensor eh: ");
      Serial.print(temperature);
      Serial.println("*C");
      if (temperature < 10 && temperature > -10)
      {
        if (temperature >= 0)
        {
          colocaUmNumero(temperature);
          delay(1000);
          animacao();
        }
        else
        {
          colocaUmNumero(10);
          delay(1000);
          colocaUmNumero(-1);
          delay(150);
          colocaUmNumero(temperature * -1);
          delay(1000);
          animacao();
        }
      }
      else if (temperature >= 10 && temperature < 100)
      {
        int primeirodigito = temperature / 10;
        int segundodigito = temperature - primeirodigito * 10;
        colocaUmNumero(primeirodigito);
        delay(1000);
        colocaUmNumero(-1);
        delay(150);
        colocaUmNumero(segundodigito);
        delay(1000);
        animacao();
      }
      colocaUmNumero(-1);
      ledRGB('S');
    }
  }
  if (digitalRead(3) == 0)
  {
    digitalWrite(2, HIGH);
    delay(60);
    digitalWrite(2, LOW);
    Serial.print("Sensor de luz: ");
    Serial.println(analogRead(A1));
  }

  colocaUmNumero(7);
  ledRGB('R');
  delay(300);
  colocaUmNumero(-1);
  delay(150);
  colocaUmNumero(3);
  ledRGB('G');
  delay(300);
  colocaUmNumero(-1);
  delay(150);
  colocaUmNumero(5);
  ledRGB('B');
  delay(300);
  colocaUmNumero(-1);
  delay(150);
  colocaUmNumero(5);
  ledRGB('R');
  delay(300);
  colocaUmNumero(-1);
  delay(150);
  colocaUmNumero(6);
  ledRGB('G');
  delay(300);
  colocaUmNumero(-1);
  delay(150);
  colocaUmNumero(0);
  ledRGB('B');
  delay(300);
  colocaUmNumero(-1);
  delay(150);
  colocaUmNumero(8);
  ledRGB('R');
  delay(300);
  colocaUmNumero(-1);
  delay(150);
  ledRGB('S');

  double tempo = 33500; // ms
  double duracaoMinima;
  while (tempo > 1000 && digitalRead(3) == 0)
  {
    if (tempo > 10000)
    {
      segmentoInfinito();
    }
    else
    {
      colocaUmNumero(floor(tempo / 1000));
    }

    double bipTime = bipbip(tempo);
    double intervalo;
    if (tempo > 3250)
    {
      intervalo = (tempo / 38) - bipTime;
      tempo -= intervalo;
    }
    else
    {
      intervalo = duracaoMinima;
      tempo -= (intervalo + 60);
    }
    Serial.print("Intervalo: ");
    Serial.println(intervalo);
    delay(intervalo);
  }

  if (digitalRead(3) == 0)
  {
    colocaUmNumero(0);

    for (int i = 0; i < 60; i++)
    { // explosao
      if (i % 5 == 0)
      {
        ledRGB('G');
      }
      else if (i % 2 == 0)
      {
        ledRGB('R');
      }
      else
      {
        ledRGB('B');
      }
      delay(70);
    }

    delay(600);
  }

  colocaUmNumero(-1);
  ledRGB('S');
}
