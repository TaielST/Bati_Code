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
#define TICK_DEBUG_ULTRASONIDO 500

//no tengo idea que vendria a ser
unsigned long currentTimeUltrasound = 0;

//constantes de sensores
float distanciaIzquierda;
float distanciaDerecha;

//variables de velocidad
#define VELOCIDAD_ATAQUE_MAX 255
#define VELOCIDAD_BUSQUEDA 70
#define VELOCIDAD_BUSQUEDA_DER 75
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
    Serial.print("Distancia Derecha"); 
    Serial.print(distanciaDerecha);
    Serial.print("///");
    Serial.print("Distancia Izquierda");
    Serial.print(distanciaIzquierda);
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
  digitalWrite(PIN_DIR_LEFT, HIGH);
  analogWrite(PIN_PWM_RIGHT, VELOCIDAD_BUSQUEDA_DER);
  digitalWrite(PIN_DIR_RIGHT, LOW);
}

void giro_Der(){
  analogWrite(PIN_PWM_LEFT, VELOCIDAD_BUSQUEDA);
  digitalWrite(PIN_DIR_LEFT, LOW);
  analogWrite(PIN_PWM_RIGHT, VELOCIDAD_BUSQUEDA);
  digitalWrite(PIN_DIR_RIGHT, HIGH);
}


enum estrategia{
  SELECT_ESTRATEGIA,
  MONSTER,
  MANTA,
  SETT,
  FULL
};

int estrategia = SELECT_ESTRATEGIA;

enum monster{
  TIEMPO_MONSTER,
  BUSQUEDA_MONSTER,
  GIRO_DER_MONSTER,
  GIRO_IZQ_MONSTER,
  ATAQUE_MONSTER
};

int monster = TIEMPO_MONSTER;

void Monster(){
  switch(monster){
    case TIEMPO_MONSTER:
    {
      quieto();
      delay(5000);
      monster = BUSQUEDA_MONSTER;
      break;
    }
    case BUSQUEDA_MONSTER:
    {
      busqueda();
      if (distanciaDerecha <= RIVAL_MID && distanciaIzquierda > RIVAL_MID)
      monster = GIRO_DER_MONSTER;
      if (distanciaDerecha > RIVAL_MID && distanciaIzquierda <= RIVAL_MID)
      monster = GIRO_IZQ_MONSTER;
      if (distanciaDerecha < RIVAL_MID && distanciaIzquierda < RIVAL_MID)
      monster = ATAQUE_MONSTER;
      break;
    }

    case GIRO_DER_MONSTER:
    {
      giro_Der();
      if (distanciaDerecha > RIVAL_MID && distanciaIzquierda <= RIVAL_MID)
      monster = GIRO_IZQ_MONSTER;
      if (distanciaDerecha < RIVAL_MID && distanciaIzquierda < RIVAL_MID)
      monster = ATAQUE_MONSTER;
      break;
    }

    case GIRO_IZQ_MONSTER:
    {
      giro_Izq();
      if (distanciaDerecha <= RIVAL_MID && distanciaIzquierda > RIVAL_MID)
      monster = GIRO_DER_MONSTER;
      if (distanciaDerecha < RIVAL_MID && distanciaIzquierda < RIVAL_MID)
      monster = ATAQUE_MONSTER;
      break;
    }

    case ATAQUE_MONSTER:
    {
      adelante();
      if(distanciaDerecha > RIVAL_MID && distanciaIzquierda > RIVAL_MID)
      monster = BUSQUEDA_MONSTER;
      if (distanciaDerecha <= RIVAL_MID && distanciaIzquierda > RIVAL_MID)
      monster = GIRO_DER_MONSTER;
      if (distanciaDerecha > RIVAL_MID && distanciaIzquierda <= RIVAL_MID)
      monster = GIRO_IZQ_MONSTER;
      break;
    }
    
  }
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
  Monster();
  //printUltrasonido();
  lecturaSensor();
}