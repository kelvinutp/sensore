int pH_Value; 
float Voltage;
float pH; 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(pH_Value, INPUT); 
} 
 
void loop() 
{ 
  pH_Value = analogRead(A0); 
  Voltage = pH_Value * (5.0 / 1023.0); 
  pH = 2.8*Voltage;
  Serial.print("Voltaje: "); 
  Serial.print(Voltage); 
  Serial.print("    PH: ");
  Serial.println(pH);
  
  delay(500); 
}
