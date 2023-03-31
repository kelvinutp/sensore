int v = A1;
int a = A2;
float V;
float A;
void setup() {
  //definimos el sensor como entrada
  pinMode(v, INPUT);
  // definimos la cantidad de baudios para la lecuta del mismo
  Serial.begin(9600);
  // put your setup code here, to run once:
}
void loop() {
  V = (analogRead(v)*0.025);
  //A = (analogRead(a)*9.6);
  Serial.println(V);
  //Serial.println(A);
  delay(1000);
  // put your main code here, to run repeatedly:

}
