//definimos variable de enrada le(lectura) para el pin A0 entrada del arduino
int le = A0;
// definimos hu(humedad)valor de humedad como %
int hu;
// Defino un valor donde se guardara los datos recolectaods para convertilso a porcentajes 
int acu;
void setup() {
  //definimos el sensor como entrada
  pinMode(le, INPUT);
  // definimos la cantidad de baudios para la lecuta del mismo
  Serial.begin(9600);
}

void loop() {
  //guardamos los datos en la bariable y usando el comando map lo traslapamos de 0 a 100
  acu = analogRead(le);
  hu = map(acu, 0, 1023, 0, 100);
  // imprimimos los datos especificando el porcentaje 
  Serial.print("Humedad = ");
  Serial.print(hu);
  Serial.println("%");
  delay(1000);
}
