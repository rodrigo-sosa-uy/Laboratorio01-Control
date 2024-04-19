// IMPORTANTE: EL RELAY SE ACTIVA ENVIANDO CERO
#include <DallasTemperature.h>
#include <OneWire.h>

OneWire ourWire(3); // Creación del objeto de tipo 1-Wire.
DallasTemperature temp_sensor(&ourWire); // Creación del objeto para sensor de temperatura.

#define Relay1 8 // Definimos pin para Relay de enfriamiento.
#define Relay2 9 // Definimos pin para Relay de calentamiento.
#define Led_Verde 10 // Led indicador de enfriamiento.
#define Led_Amarillo 11 // Led indicador de calentamiento.

#define T_max 30 // Temperatura máxima establecida.
#define T_min 25 // Temperatura mínima establecida.
#define t_muestreo 5 // Tiempo de muestreo establecido para demostración de funcionamiento.
#define Tend_max 2 // Tendencia máxima establecida.
#define Tend_min -2 // Tendencia mínima establecida.

float temp_actual = 0;
float temp_previa = 0;
char N_tendencia = 0;

void allOFF();
void getTemperature();

void setup() {
  delay(1000);

  Serial.begin(9600);
  Serial.println("Puerto Serial inicializado.");
  temp_sensor.begin();
  Serial.println("Sensor de temperatura inicializado.");

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Led_Verde, OUTPUT);
  pinMode(Led_Amarillo, OUTPUT);

  allOFF();
  Serial.println("Se inicializan todos los indicadores/actuadores apagados.");
}

void loop() {
  delay((t_muestreo*1000));
  
  getTemperature(); // Solicitamos la medición de temperatura.

  if(temp_actual == temp_previa || ((temp_actual > T_min) && (temp_actual < T_max))){
    N_tendencia = 0;
  } else if((temp_actual < temp_previa) && (temp_actual < T_min)){
    N_tendencia--; // La tendencia es bajar.
  } else if((temp_actual > temp_previa) && (temp_actual > T_max)){
    N_tendencia++; // La tendencia es subir.
  }

  if(N_tendencia >= Tend_max){ // Control del relay de enfriamiento. La temperatura sube.
    digitalWrite(Led_Verde, HIGH);
    digitalWrite(Relay1, LOW);
  } else if(N_tendencia <= Tend_min){ // Control del relay de calentamiento. La temperatura baja.
    digitalWrite(Led_Amarillo, HIGH);
    digitalWrite(Relay2, LOW);
  } else{ // Todo apagado.
    allOFF();
  }

  temp_previa = temp_actual;
}

void getTemperature(){
  temp_sensor.requestTemperatures();   //Se envía el comando para leer la temperatura
  temp_actual = temp_sensor.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  Serial.println(temp_actual);
}

void allOFF(){
  digitalWrite(Led_Verde, LOW);
  digitalWrite(Relay1, HIGH);
  digitalWrite(Led_Amarillo, LOW);
  digitalWrite(Relay2, HIGH);
}