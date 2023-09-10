#include <Arduino_FreeRTOS.h>
const int An = 2;
const int Ap = 3;
const int Bn = 4;
const int Bp = 5;
const int R = 6;
const int C = 7;
const int L = 8;
const int Alert = 13;



void car(){
    Serial.begin(9600);

    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(6,INPUT);
    pinMode(7,INPUT);
    pinMode(8,INPUT);

    while(1){
       if(digitalRead(L) == LOW && digitalRead(R) == LOW && digitalRead(C) == HIGH){
  Serial.write("Center\n");
    //delay(1000);
  digitalWrite(An,LOW);
  digitalWrite(Ap,HIGH);
  digitalWrite(Bn,LOW);
  digitalWrite(Bp,HIGH);
  digitalWrite(Alert,LOW);  
}
if (digitalRead(L) == LOW && digitalRead(C) == HIGH && digitalRead(R) == HIGH){
  Serial.write("Right\n");
    //delay(1000);
  digitalWrite(An,LOW);
  digitalWrite(Ap,LOW);
  digitalWrite(Bn,LOW);
  digitalWrite(Bp,HIGH);
  digitalWrite(Alert,HIGH);

}
if (digitalRead(C) == HIGH && digitalRead(R) == LOW && digitalRead(L) == HIGH){
  Serial.write("Left\n");
    //delay(1000);
  digitalWrite(An,LOW);
  digitalWrite(Ap,HIGH);
  digitalWrite(Bn,LOW);
  digitalWrite(Bp,LOW);
  digitalWrite(Alert,HIGH);

}
    }
}


void setup() {
   xTaskCreate(car,"car",256,NULL,2,NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
