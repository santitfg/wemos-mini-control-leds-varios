#include <Arduino.h>
#include <ESP8266WiFi.h>

#define ESTADO_APAGADO 0.0
#define ESTADO_INICIAL 1.0f
#define ESTADO_RAPIDO 5.66f

float ciclosPorSegundo;
bool estadoBtnAnterior = true, estadoBtnActual = false;

int estadoLed = 0;

//la maquina de estados se supone que estaria apagada cuando los ciclos por segundo fueran cero ya que F(t=0) sin(t-PI/2)*0.5+0.5 equivale a 0 
//una onda sinusoidal que se le cambio la fase y se 
float estados[] = {ESTADO_APAGADO, ESTADO_INICIAL, ESTADO_RAPIDO};

int largoMAquinaDeEstados = 0;

void setup()
{
    
    pinMode(D6, OUTPUT);
    pinMode(D4, INPUT);

    largoMAquinaDeEstados = sizeof(estados) / sizeof(estados[0]);
    // estadoBtnActual = false;
    // estadoBtnAnterior = true;
    ciclosPorSegundo=ESTADO_RAPIDO;//ESTADO_APAGADO;
}

void loop()
{
    //estadoBtnActual = digitalRead(D4); //probar btn

    analogWrite(D6, sin(millis() * 0.001f * ciclosPorSegundo - PI/2.0 ) * 127.5f + 127.5f);

    if (estadoBtnActual != estadoBtnAnterior && estadoBtnActual == true)
    {
        estadoLed++;
        if (estadoLed > largoMAquinaDeEstados)
        {
            estadoLed = 0;
        }
        ciclosPorSegundo=estados[estadoLed];
    }
    estadoBtnAnterior = estadoBtnActual;
}