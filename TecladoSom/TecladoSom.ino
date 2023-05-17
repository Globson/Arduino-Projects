void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  if(analogRead(0) > 0){
    Serial.print("A leitura em A0 é:");
    Serial.println(analogRead(0));
    while(analogRead(0)>0){

    }
  }
   
  if(analogRead(1) > 0){
    Serial.print("A leitura em A1 é:");
    Serial.println(analogRead(1));
    while(analogRead(1)>0){
      
    }
  }
    
}
