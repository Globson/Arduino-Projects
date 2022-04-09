void setup() {
  // put your setup code here, to run once:
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);

  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void colocaUmNumero(int num){
  switch (num){
    case 0:
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);
      digitalWrite(13,LOW);
      break;
     case 1:
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      break;
     case 2:
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);//
      digitalWrite(11,HIGH);
      digitalWrite(12,LOW);
      digitalWrite(13,HIGH);//
      break;
     case 3:
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(12,LOW);
      digitalWrite(13,HIGH);
      break;
     case 4:
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);
      digitalWrite(13,HIGH);
      break;
     case 5:
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);
      digitalWrite(12,HIGH);
      digitalWrite(13,HIGH);
      break;
     case 6:
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);
      digitalWrite(12,HIGH);
      digitalWrite(13,HIGH);
      break;
     case 7:
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      break;
     case 8:
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);
      digitalWrite(13,HIGH);
      break;
     case 9:
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);
      digitalWrite(13,HIGH);
      break;
     default:
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      break;
    }
}

void ledRGB(char S){
  switch (S){
    case 'R':
        digitalWrite(6,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(4,LOW);
        break;
    case 'G':
        digitalWrite(6,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(4,LOW);
        break;
    case 'B':
        digitalWrite(6,LOW);
        digitalWrite(5,LOW);
        digitalWrite(4,HIGH);
        break;
    default:
        digitalWrite(6,LOW);
        digitalWrite(5,LOW);
        digitalWrite(4,LOW);
        break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
    for(int i=0;i<10;i++){
      digitalWrite(1,LOW);
      digitalWrite(2,LOW);
      colocaUmNumero(i);
      if(i%5==0){
        ledRGB('G');
      }
      else if(i%2==0){
        ledRGB('R');
      }
      else{
        ledRGB('B');
      }
      while(digitalRead(3)==0 && analogRead(A0)>=300){
        delay(100);
      }
      if(digitalRead(3)==1){
        digitalWrite(1,HIGH);
        delay(70);
        digitalWrite(1,LOW);
      }
      delay(analogRead(A1)*4);
    }

    
  
}
