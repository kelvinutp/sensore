#include <SoftwareSerial.h>

#define rxPin 0
#define txPin 1

SoftwareSerial connection(rxPin,txPin);

const byte N[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte P[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte K[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];

void setup() {
  // put your setup code here, to run once:
  pinMode(txPin,OUTPUT);
  pinMode(rxPin,INPUT);

  connection.begin(9600);
  Serial.begin(9600);
  Serial.println("Beginning");
  delay(50);
}

void loop() {
  Serial.println("reading");
  // put your main code here, to run repeatedly:
  byte val1,val2,val3;
  delay(250);
  val1=nitrogen();
  delay(250);
  val2=phosphorous();
  delay(250);
  val3=potassium();
  delay(250);

  Serial.print("Nitrogen: ");
  Serial.print(val1);
  Serial.println(" mg/kg");
  Serial.print("Phosphorus: ");
  Serial.print(val2);
  Serial.println(" mg/kg");
  Serial.print("Potassium: ");
  Serial.print(val3);
  Serial.println(" mg/kg");

  delay(2000);
}

byte nitrogen(){
  digitalWrite(txPin,HIGH);
  digitalWrite(rxPin,HIGH);
  delay(10);
  if(connection.write(N,sizeof(N))==8){
    digitalWrite(txPin,LOW);
    digitalWrite(rxPin,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(connection.read(),HEX);
    values[i] = connection.read();
    // Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte phosphorous(){
  digitalWrite(txPin,HIGH);
  digitalWrite(rxPin,HIGH);
  delay(10);
  if(connection.write(P,sizeof(P))==8){
    digitalWrite(txPin,LOW);
    digitalWrite(rxPin,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(connection.read(),HEX);
    values[i] = connection.read();
    // Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte potassium(){
  digitalWrite(txPin,HIGH);
  digitalWrite(rxPin,HIGH);
  delay(10);
  if(connection.write(K,sizeof(K))==8){
    digitalWrite(txPin,LOW);
    digitalWrite(rxPin,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(connection.read(),HEX);
    values[i] = connection.read();
    // Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}