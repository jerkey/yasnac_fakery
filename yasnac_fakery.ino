#define CN1_SEN 8 // goes high when it wants serial data
#define CN2_SEN 9 // goes high when it wants serial data
#define CN1_PB 10 // PB pin
#define CN2_PB 11 // PB pin

boolean cn1_sent = false; // whether we have sent data for this one yet
boolean cn2_sent = false; // whether we have sent data for this one yet

void setup()  
{
  Serial.begin(9600,SERIAL_7E1);
  delay(1000);
}

void loop()
{
  if (digitalRead(CN1_SEN) && !cn1_sent) {
    Serial.begin(9600,SERIAL_7E1);
    delay(185);
    Serial.print("P");
    delay(2);
    Serial.print("+");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("\r");
    delayMicroseconds(2470);
    sendIncrementalPulses(1,CN1_PB);
    cn1_sent = true;
    }
  if (!digitalRead(CN1_SEN)) cn1_sent = false;
  if (digitalRead(CN2_SEN) && !cn2_sent) {
    Serial.begin(9600,SERIAL_7E1);
    delay(185);
    Serial.print("P");
    delay(2);
    Serial.print("+");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("0");
    delay(2);
    Serial.print("\r");
    delayMicroseconds(2470);
    sendIncrementalPulses(1,CN2_PB);
    cn2_sent = true;
    }
  if (!digitalRead(CN2_SEN)) cn2_sent = false;
}

void sendIncrementalPulses(int pin1, int pin2) {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  for (int i = 0; i < 89; i++) {
    UCSR0B &= (255 - (1<<TXEN0));
    digitalWrite(pin1,HIGH);
    delayMicroseconds(43);
    digitalWrite(pin2,HIGH);
    delayMicroseconds(43);
    digitalWrite(pin1,LOW);
    delayMicroseconds(43);
    digitalWrite(pin2,LOW);
    delayMicroseconds(43);
  }
}
