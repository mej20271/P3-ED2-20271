//Proyecto 3 - ESP324
//20271 - Angeles Mejía
//Comunicacion I2C-LM75-NEOPIXEL

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

// Neopixel
const int pinLed = 23;
const int numLeds = 16;
Adafruit_NeoPixel tiraLeds(numLeds, pinLed, NEO_GRB + NEO_KHZ800);
const int lm75Address = 0x48;

float tempsensor;
bool boton1pres = false;

void leerTemperatura()
{
  Wire.beginTransmission(lm75Address);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(lm75Address, 2);
  while (Wire.available() < 2)
    ;

  int tempRaw = Wire.read() << 8 | Wire.read();
  tempsensor = tempRaw / 256.0;

  Serial.print("Temperatura: ");
  Serial2.print(tempsensor);
  Serial.println(tempsensor);
}

void configurarNeopixel()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  Wire.begin();
  tiraLeds.begin();
  tiraLeds.show();
  for (int i = 0; i < numLeds; i++)
  {
    tiraLeds.setPixelColor(i, tiraLeds.Color(255, 0, 0)); // Rojo
  }
  tiraLeds.show();
  delay(1000);
  tiraLeds.clear();
  tiraLeds.show();
}

void setup()
{
  configurarNeopixel();
}

void loop()
{
  while (Serial2.available() > 0)
  {
    char datoSensor = Serial2.read();
    if (datoSensor == 't')
    {
      leerTemperatura();
    }
    if (datoSensor == '1')
    {
      boton1pres = true;
    }
  }

  if (boton1pres)
  {
    
    for (int i = 0; i < numLeds; i++)
    {
      tiraLeds.setPixelColor(i, tiraLeds.Color(0, 255, 0)); // Verde
      tiraLeds.show();
      delay(100);
    }
    tiraLeds.clear(); 
    tiraLeds.show();
    boton1pres = false;
  }
}
