#define RELAY1  8      // Relay to start the first heater
#define RELAY2  9      // Relay to start the second heater
#define RELAY3  10     //Relay to start the humidifier
#define RELAY4  11     //Relay to start air pump

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(RELAY1, HIGH);
delay(300); //Pause between readings.
digitalWrite(RELAY1, LOW);

digitalWrite(RELAY2, HIGH);
delay(300); //Pause between readings.
digitalWrite(RELAY2, LOW);

digitalWrite(RELAY3, HIGH);
delay(300); //Pause between readings.
digitalWrite(RELAY3, LOW);

digitalWrite(RELAY4, HIGH);
delay(300); //Pause between readings.
digitalWrite(RELAY4, LOW);
}
