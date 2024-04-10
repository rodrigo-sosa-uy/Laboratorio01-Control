#include <DallasTemperature.h>
#include <OneWire.h>

OneWire ourWire(2); //Se establece el pin 2  como bus OneWire
 
DallasTemperature sensor(&ourWire); //Se declara una variable u objeto para nuestro sensor

byte addr[8];

void setup(){
  delay(1000);
  Serial.begin(9600);
  sensor.begin();   //Se inicia el sensor

  pinMode(3, OUTPUT);
}
 
void loop() {
  sensor.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp = sensor.getTempCByIndex(0); //Se obtiene la temperatura en ºC

  Serial.print("Temperatura = ");
  Serial.print(temp);
  Serial.println(" C");
  delay(1000);

  if(temp >= 30.0){
    digitalWrite(3, HIGH);
  } else{
    digitalWrite(3, LOW);
  }
}