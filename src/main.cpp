#include <AnalogWrite.h>
#include <ultrasonido.h>
//variables para los pines de los motores
#define PIN_DIR_LEFT 23 
#define PIN_PWM_LEFT 22 
#define PIN_DIR_RIGHT 18
#define PIN_PWM_RIGHT 19  
//variables para los pines de los ultrasonido
#define PIN_ECHO_IZQ 27
#define PIN_TRIG_IZQ 14
#define PIN_ECHO_DER 25
#define PIN_TRIG_DER 33
//#define DEBUG_ULTRASONIDO 0
#define TICK_DEBUG_ULTRASONIDO 50

//no tengo idea que vendria a ser
unsigned long currentTimeUltrasound = 0;

//constantes de sensores
float distanciaIzquierda;
float distanciaDerecha;

//variables de velocidad
#define VELOCIDAD_ATAQUE_MAX 255
#define VELOCIDAD_BUSQUEDA 80
#define VELOCIDAD_BUSQUEDA_DER 85
#define VELOCIDAD_ATAQUE_MIN 135
#define VELOCIDAD_ATAQUE_MID 190
#define STOP 0

//variables de distancia
#define RIVAL_MIN 10
#define RIVAL_MID 40
#define RIVAL_MAX 50


//instacia de objetos
Ultrasonido *ultrasonidoDerecho = new Ultrasonido(PIN_TRIG_DER, PIN_ECHO_DER);
Ultrasonido *ultrasonidoIzquierdo = new Ultrasonido(PIN_TRIG_IZQ, PIN_ECHO_IZQ);

//imprime en pantalla la lectura de los sensores
void printUltrasonido(){
  if (millis()>currentTimeUltrasound + TICK_DEBUG_ULTRASONIDO)
  {
    currentTimeUltrasound = millis();
    Serial.println("Distancia Derecha"); 
    Serial.println(distanciaDerecha);
    Serial.print("///");
    Serial.println("Distancia Izquierda");
    Serial.println(distanciaIzquierda);
  }
}

//lee los sensores
void lecturaSensor(){
  distanciaDerecha = ultrasonidoDerecho->sensorRead();
  distanciaIzquierda = ultrasonidoIzquierdo->sensorRead();
}

void quieto(){
  analogWrite(PIN_PWM_LEFT, STOP);
  digitalWrite(PIN_DIR_LEFT, HIGH);
  analogWrite(PIN_PWM_RIGHT, STOP);
  digitalWrite(PIN_DIR_RIGHT, HIGH);
}

void adelante(){
  analogWrite(PIN_PWM_LEFT, VELOCIDAD_ATAQUE_MID);
  digitalWrite(PIN_DIR_LEFT, LOW);
  analogWrite(PIN_PWM_RIGHT, VELOCIDAD_ATAQUE_MID);
  digitalWrite(PIN_DIR_RIGHT, LOW);
}

void busqueda(){
  analogWrite(PIN_PWM_LEFT, VELOCIDAD_BUSQUEDA);
  digitalWrite(PIN_DIR_LEFT, LOW);
  analogWrite(PIN_PWM_RIGHT, VELOCIDAD_BUSQUEDA_DER);
  digitalWrite(PIN_DIR_RIGHT, HIGH);
}

void giro_Izq(){
  analogWrite(PIN_PWM_LEFT, VELOCIDAD_BUSQUEDA);
  digitalWrite(PIN_DIR_LEFT, LOW);
  analogWrite(PIN_PWM_RIGHT, VELOCIDAD_BUSQUEDA_DER);
  digitalWrite(PIN_DIR_RIGHT, HIGH);
}

void setup() {
  pinMode(PIN_DIR_RIGHT, OUTPUT);
  pinMode(PIN_PWM_RIGHT, OUTPUT);
  pinMode(PIN_DIR_LEFT, OUTPUT);
  pinMode(PIN_PWM_LEFT, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //delay(5000);
  //busqueda();
  monster();
  //printUltrasonido();
  lecturaSensor();
}
