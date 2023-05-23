char myChar;
void setup()  
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Conexión exitosa");
}

void loop() 
{
  while (Serial1.available())
  {
    myChar = Serial1.read();
    Serial.print(myChar);
  }

  while (Serial.available())
  {
    myChar = Serial.read();
    Serial1.print(myChar);
  }
}
