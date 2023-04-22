//librerias
#include <SoftwareSerial.h>

const byte N[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte P[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte K[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];

//pines de lectura del sensor de voltaje y corriente
#define v A1
#define a A2

//pines de lectura de NPK
#define rxPin 0
#define txPin 1
//inicio de libreria
SoftwareSerial connection(rxPin, txPin);


//pin de DHT11
#define le A0

//pines TDS
#define TdsSensorPin A3
#define VREF 5.0              // analog reference voltage(Volt) of the ADC
#define SCOUNT  30            // sum of sample point

int analogBuffer[SCOUNT];     // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
int copyIndex = 0;

float averageVoltage = 0;
float tdsValue = 0;
float temperature = 25;       // current temperature for compensation

void setup() {
  // declaracion de funciones de pines
  
  //sensor de voltaje y corriente
  pinMode(a, INPUT);
  pinMode(v, INPUT);
  
  //sensor NPK
  pinMode(txPin, OUTPUT);
  pinMode(rxPin, INPUT);
  connection.begin(9600);
  
  //sensor DHT11
  pinMode(le, INPUT);
  
  //sensor TDS
  pinMode(TdsSensorPin,INPUT);

  
  //inicio de comunicacion serial
  Serial.begin(9600);
  Serial.println("Inicio de programa");
}

void loop() {
  // lectura de voltaje y corriente
  float vol = voltaje();
  float amp = corriente();

  // lectura de NPK
  byte val1, val2, val3;
  delay(250);
  val1 = nitrogen();
  delay(250);
  val2 = phosphorous();
  delay(250);
  val3 = potassium();
  delay(250);

  //lectura de humedad
  int hu=humedad();
  
  //impresiones en monitor serial

  //voltaje y corriente
  Serial.print("Voltaje en V: ");
  Serial.print(vol, 3);
  Serial.print("Corriente en A: ");
  Serial.println(amp, 3);

  //NPK
  Serial.print("Nitrogen: ");
  Serial.print(val1);
  Serial.println(" mg/kg");
  Serial.print("Phosphorus: ");
  Serial.print(val2);
  Serial.println(" mg/kg");
  Serial.print("Potassium: ");
  Serial.print(val3);
  Serial.println(" mg/kg");

  //humedad
  Serial.print("Humedad = ");
  Serial.print(hu);
  Serial.println("%");

  
  delay(100);


}

float voltaje() {
  float b = (analogRead(v) * 0.025);
  return b;
}

float corriente() {
  float b = (analogRead(a) * 9.5 / 1023);
  return b;
}

byte nitrogen() {
  digitalWrite(txPin, HIGH);
  digitalWrite(rxPin, HIGH);
  delay(10);
  if (connection.write(N, sizeof(N)) == 8) {
    digitalWrite(txPin, LOW);
    digitalWrite(rxPin, LOW);
    for (byte i = 0; i < 7; i++) {
      //Serial.print(connection.read(),HEX);
      values[i] = connection.read();
      // Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte phosphorous() {
  digitalWrite(txPin, HIGH);
  digitalWrite(rxPin, HIGH);
  delay(10);
  if (connection.write(P, sizeof(P)) == 8) {
    digitalWrite(txPin, LOW);
    digitalWrite(rxPin, LOW);
    for (byte i = 0; i < 7; i++) {
      //Serial.print(connection.read(),HEX);
      values[i] = connection.read();
      // Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte potassium() {
  digitalWrite(txPin, HIGH);
  digitalWrite(rxPin, HIGH);
  delay(10);
  if (connection.write(K, sizeof(K)) == 8) {
    digitalWrite(txPin, LOW);
    digitalWrite(rxPin, LOW);
    for (byte i = 0; i < 7; i++) {
      //Serial.print(connection.read(),HEX);
      values[i] = connection.read();
      // Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

int humedad(){
  //valor en porcentaje
  int ac=map(analogRead(le),0,1023,0,100);
  return ac;
}
