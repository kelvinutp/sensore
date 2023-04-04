// definimos los pines a usar
int v = A1;
int a = A2;
// definimos variables de contexion de cada lectura
float V;
float A;

void setup() {
  // definimos el tipo de lectura de los pins
  pinMode(a, INPUT);
  pinMode(v, INPUT);
  // definimos la cantidad de baudios para la lecuta del mismo
  Serial.begin(9600);
  // put your setup code here, to run once:
}
void loop() {
  //lectura de los pins y calibracion de cada uno
  V = (analogRead(v)*0.025);
  A = analogRead(a);
  float current = (A * 9.5) /1023;
  // impre los datos 
  Serial.print("Voltaje V: ");
  Serial.print(V, 3);
  Serial.print(" Corriente A:");
  Serial.println(current, 4);
  delay(1000);
  // put your main code here, to run repeatedly:

}
