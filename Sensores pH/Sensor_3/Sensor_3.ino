#include <Arduino.h>

int pHSense = A0;
int samples = 10;
float adc_resolution = 1024.0;

void setup()
{
    Serial.begin(9600);
    delay(100);
    Serial.println("cimpleo pH Sense");
}

float ph (float voltage) {
    return (-5.5642)*(voltage)+20.91;;
}

void loop()
{
    int measurings=0;

    for (int i = 0; i < samples; i++)
    {
        measurings += analogRead(pHSense);
        delay(10);

    }

    float voltage = 5 / adc_resolution * measurings/samples;
    Serial.print(("Voltage= "));
    Serial.print((voltage));
    Serial.print(("   "));
    Serial.print("pH= ");
    Serial.println(ph(voltage));
    delay(3000);
}
