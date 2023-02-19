#include <Arduino.h>
#include <Adafruit_NeoPixel.h> // libreria pixel led

// #define PIN_PIXEL_LED 6 // pin donde conecto luces
#define CANTIDAD_LEDS 21 // cantidad de pixel leds

#define ESTADO_APAGADO 0.0
#define ESTADO_INICIAL 1.0f
#define ESTADO_RAPIDO 5.66f

Adafruit_NeoPixel strip = Adafruit_NeoPixel(CANTIDAD_LEDS, D6, NEO_GRB + NEO_KHZ800); // cant pixels
float estados[] = {ESTADO_APAGADO, ESTADO_INICIAL, ESTADO_RAPIDO};
float ciclosPorSegundo;
int largoMAquinaDeEstados = 0;
int estadoLed = 0, brillo = 0;
;

float sum_lectura = 0;
float f = .95f;

void setup()
{
  pinMode(D6, OUTPUT);

  // put your setup code here, to run once:
  strip.begin(); // inicio strip
  strip.show();  // Inicio pixels en off
  largoMAquinaDeEstados = sizeof(estados) / sizeof(estados[0]);

  ciclosPorSegundo = ESTADO_APAGADO; // ESTADO_APAGADO;
}

void loop()
{

  int lectura = analogRead(A0);
  sum_lectura = lectura * (1 - f) + sum_lectura * f;

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
  else if (sum_lectura < 900)
  {
    ciclosPorSegundo = map(sum_lectura, 201.f, 899.99f, ESTADO_INICIAL, 35.f);
  }
  else
  {
    brillo = 255;
  }
  // if (sum_lectura < 120)
  // {
  //   // estadoLed = 0;
  //   ciclosPorSegundo = ESTADO_APAGADO;
  // }
  // else if (sum_lectura < 800)
  // {
  //   ciclosPorSegundo = ESTADO_INICIAL;
  // }
  // else
  // {
  //   ciclosPorSegundo = ESTADO_RAPIDO;
  // }

  // ciclosPorSegundo=estados[estadoLed];

  // strip.ColorHSV();
  strip.fill(strip.Color(brillo, brillo, brillo));
  strip.show(); // actualizo la tira de leds
}