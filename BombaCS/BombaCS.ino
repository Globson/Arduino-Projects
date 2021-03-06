void setup()
{
  // put your setup code here, to run once:
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

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, OUTPUT);
}

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
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
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
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    break;
  case 5:
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    break;
  case 6:
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
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

void loop()
{
  // put your main code here, to run repeatedly:

  while (digitalRead(3) == 0)
  {
    delay(100);
  }
  if (digitalRead(3) == 1)
  {
    digitalWrite(2, HIGH);
    delay(60);
    digitalWrite(2, LOW);
  }

  colocaUmNumero(7);
  ledRGB('R');
  delay(analogRead(A1) * 10);
  colocaUmNumero(3);
  ledRGB('G');
  delay(analogRead(A1) * 10);
  colocaUmNumero(5);
  ledRGB('B');
  delay(analogRead(A1) * 10);
  colocaUmNumero(5);
  ledRGB('R');
  delay(analogRead(A1) * 10);
  colocaUmNumero(6);
  ledRGB('G');
  delay(analogRead(A1) * 10);
  colocaUmNumero(0);
  ledRGB('B');
  delay(analogRead(A1) * 10);
  colocaUmNumero(8);
  ledRGB('R');
  delay(analogRead(A1) * 10);
  ledRGB('S');

  double tempo = 40000; // ms
  double duracaoMinima;
  while (tempo > 1000)
  {
    if (tempo > 9000)
    {
      segmentoAleatorio();
    }
    else
    {
      colocaUmNumero(floor(tempo / 1000));
    }

    double bipTime = bipbip(tempo);
    if (tempo > 4500)
    {
      bipTime = abs(((tempo / 40) - bipTime));
      duracaoMinima = bipTime;
    }
    else
    {
      bipTime = duracaoMinima;
    }
    tempo -= bipTime;
    delay(bipTime);
  }

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

  colocaUmNumero(-1);
  ledRGB('S');
}
