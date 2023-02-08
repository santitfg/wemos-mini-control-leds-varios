#include <Arduino.h>
#include <SimplexNoise.h>
// #define PIN_PIXEL_LED 6 // pin donde conecto luces
#define CANTIDAD_LEDS 7 // cantidad de pixel leds

#define ESTADO_APAGADO 0.0
#define ESTADO_INICIAL 1.0f
#define ESTADO_RAPIDO 5.66f

SimplexNoise sn;

unsigned long previousMillis = 0;
const long interval = 20;

double n;
float increase = 0.005;
float x = 0.0;
float y = 0.0;

float ciclosPorSegundo;
int brillo = 0;
;

float sum_lectura = 0;
float f = .95f;

void setup()
{
  pinMode(D6, OUTPUT);

  ciclosPorSegundo = ESTADO_APAGADO;
}

void loop()
{
  unsigned long currentMillis = millis();

  int lectura = analogRead(A0);
  sum_lectura = lectura * (1 - f) + sum_lectura * f;

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    n = sn.noise(x, y);
    x += increase;

  }

  // n = sn.noise(x, y);
  // x += increase;

  brillo = sin(millis() * 0.001f * ciclosPorSegundo - PI / 2.0) * 127.5f + 127.5f;

  if (sum_lectura < 120)
  {
    // estadoLed = 0;
    ciclosPorSegundo = ESTADO_APAGADO;
  }
  else if (sum_lectura < 200)
  {
    ciclosPorSegundo = ESTADO_INICIAL;
  }
  else if (sum_lectura < 750)
  {
    ciclosPorSegundo = map(sum_lectura, 201.f, 749.99f, ESTADO_INICIAL, 35.f);
  }
  else if (sum_lectura < 850)
  {
    brillo = (int)(n  * 127.5 + 127.5);
  }
  else if (sum_lectura < 950)
  {
    brillo=random(0,256);
  }
  else
  {
    brillo = 255;
  }

  analogWrite(D6, brillo);
}