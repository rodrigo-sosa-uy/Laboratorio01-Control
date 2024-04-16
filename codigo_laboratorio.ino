// IMPORTANTE: EL RELAY SE ACTIVA MANDANDO CERO
#include <DallasTemperature.h>
#include <OneWire.h>

OneWire ourWire(2);
DallasTemperature temp_sensor(&ourWire);

#define Relay1 8
#define Relay2 9
#define Led_Verde 10
#define Led_Amarillo 11

#define T_max 30 // Sujeto a cambios
#define T_min 25 // Sujeto a cambios
#define t_muestreo 120 // Sujeto a cambios
#define Tend_max 2 // Sujeto a cambios
#define Tend_min -2 // Sujeto a cambios

float temp_actual = 0;
float temp_previa = 0;
char N_tendencia = 0;

void setup() {
  delay(1000);

  Serial.begin(9600);
  temp_sensor.begin();

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Led_Verde, OUTPUT);
  pinMode(Led_Amarillo, OUTPUT);
}

void loop() {
  delay((t_muestreo*1000));
  
  getTemperature();

  if(temp_actual == temp_previa || ((temp_actual > T_min) && (temp_actual < T_max))){
    N_tendencia = 0;
  } else if((temp_actual < temp_previa) && (temp_actual < T_min)){
    N_tendencia--; // La tendencia es bajar.
  } else if((temp_actual > temp_previa) && (temp_actual > T_max)){
    N_tendencia++; // La tendencia es subir.
  }

  if(N_tendencia >= Tend_max){
    digitalWrite(Led_Verde, HIGH);
    digitalWrite(Relay1, LOW);
  } else if(N_tendencia <= Tend_min){
    digitalWrite(Led_Amarillo, HIGH);
    digitalWrite(Relay2, LOW);
  } else{
    digitalWrite(Led_Amarillo, LOW);
    digitalWrite(Relay2, HIGH);
    digitalWrite(Led_Verde, LOW);
    digitalWrite(Relay1, HIGH);
  }

  temp_previa = temp_actual;
}

void getTemperature(){
  temp_sensor.requestTemperatures();   //Se envía el comando para leer la temperatura
  temp_actual = temp_sensor.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  Serial.println(temp_actual);
}