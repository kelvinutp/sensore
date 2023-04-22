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
  pinMode(TdsSensorPin, INPUT);


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
  int hu = humedad();

  //TDS
  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 40U) { //every 40 milliseconds,read the analog value from the ADC
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT) {
      analogBufferIndex = 0;
    }
  }

  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 800U) {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++) {
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];

      // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 4096.0;

      //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
      float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
      //temperature compensation
      float compensationVoltage = averageVoltage / compensationCoefficient;

      //convert voltage value to tds value
      tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;
    }
  }

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

  //TDS
  Serial.print("voltage:");
  Serial.print(averageVoltage, 2);
  Serial.print("V   ");
  Serial.print("TDS Value:");
  Serial.print(tdsValue, 0);
  Serial.println("ppm");
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

int humedad() {
  //valor en porcentaje
  int ac = map(analogRead(le), 0, 1023, 0, 100);
  return ac;
}

int getMedianNum(int bArray[], int iFilterLen){
  int bTab[iFilterLen];
  for (byte i = 0; i<iFilterLen; i++)
  bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0){
    bTemp = bTab[(iFilterLen - 1) / 2];
  }
  else {
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  }
  return bTemp;
}
