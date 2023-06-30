#include <AnalogWrite.h>
#include <ultrasonido.h>

#define PIN_DIR_LEFT 23 // DIR
#define PIN_PWM_LEFT 22 // PWM
#define PIN_DIR_RIGHT 18 // DIR
#define PIN_PWM_RIGHT 19  // PWM
#define PIN_ECHO_IZQ 25
#define PIN_TRIG_IZQ 33
#define PIN_ECHO_DER 27
#define PIN_TRIG_DER 14

#define DEBUG_ULTRASONIDO 500

unsigned long currentTimeUltrasound = 0;

float distaciaIzquierda;
float distaciaDerecha;

#define VELOCIDAD_ATAQUE_MAX 255
#define VELOCIDAD_BUSQUEDA 80
#define VELOCIDAD_ATAQUE_MIN 135
#define VELOCIDAD_ATAQUE_MID 190

Ultrasonido *ultrasonidoDerecho = new Ultrasonido(PIN_TRIG_DER, PIN_ECHO_DER);
Ultrasonido *ultrsonidoIzquierdo = new Ultrasonido(PIN_TRIG_IZQ, PIN_ECHO_IZQ);


void printUltra(){
  if(millis() > currentTimeUltrasound + DEBUG_ULTRASONIDO){
    
  }
}

void adelante(){
  analogWrite(PIN_PWM_LEFT, VELOCIDAD_ATAQUE_MIN);
  digitalWrite(PIN_DIR_LEFT, LOW);
  analogWrite(PIN_PWM_RIGHT, VELOCIDAD_ATAQUE_MIN);
  digitalWrite(PIN_DIR_RIGHT, LOW);
}

void busqueda(){
  analogWrite(PIN_PWM_LEFT, VELOCIDAD_BUSQUEDA);
  digitalWrite(PIN_DIR_LEFT, LOW);
  analogWrite(PIN_PWM_RIGHT, VELOCIDAD_BUSQUEDA);
  digitalWrite(PIN_DIR_RIGHT, HIGH);
}


void setup() {
  pinMode(PIN_DIR_RIGHT, OUTPUT);
  pinMode(PIN_PWM_RIGHT, OUTPUT);
  pinMode(PIN_DIR_LEFT, OUTPUT);
  pinMode(PIN_PWM_LEFT, OUTPUT);
}

void loop() {
  delay(3000);
  busqueda();
}
