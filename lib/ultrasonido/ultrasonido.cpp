#include "ultrasonido.h"

Ultrasonido::Ultrasonido(int trig, int echo)
{
    pin_trig = trig;
    pin_echo = echo;

    pinMode(pin_echo, INPUT);
    pinMode(pin_trig, OUTPUT);
    digitalWrite(pin_trig, LOW);
}

float Ultrasonido::sensorRead()
{
    float distancia;
    float utrasonidoPulso;
    digitalWrite(pin_trig, HIGH);
    delayMicroseconds(10);
    ditalWrite(pin_trig,LOW);
    ultrasonidopulso = PulseIn(pin_echo, HIGH);
    distace = ultrasonidoPulso / 58.2;
    return distancia;
}