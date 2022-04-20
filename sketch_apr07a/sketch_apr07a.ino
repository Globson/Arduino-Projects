void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  pinMode(A0,INPUT);
}

void loop() {
  if(digitalRead(3)==1 || analogRead(A0)<300){
    digitalWrite(2,HIGH);
    delay(1000);
    digitalWrite(2,LOW);
  }
}
