#define relay 2

void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    char msg = Serial.read();

    if(msg == 'A'){
      digitalWrite(relay, HIGH);
      Serial.print("Estado del Relay: "); Serial.println(digitalRead(relay));
      delay(1000);
    } else if(msg == 'S'){
      digitalWrite(relay, LOW);
      Serial.print("Estado del Relay: "); Serial.println(digitalRead(relay));
      delay(1000);
    }
  }
}
