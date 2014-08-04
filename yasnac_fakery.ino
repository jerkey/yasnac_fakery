#define CN1_SEN 2 // goes high when it wants serial data
#define CN1_PA 18 // this is the same as Serial1 TX pin (must be 18)
#define CN1_PB  3 // PB pin

#define CN2_SEN 4 // goes high when it wants serial data
#define CN2_PA 16 // this is the same as Serial2 TX pin (must be 16)
#define CN2_PB  5 // PB pin

boolean cn1_sent = false; // whether we have sent data for this one yet
boolean cn2_sent = false; // whether we have sent data for this one yet

void setup()  
{
  Serial.begin(9600); // ,SERIAL_7E1);
  Serial.println("i lie to YASNACs");
  delay(1000);
}

void loop()
{
  if (digitalRead(CN1_SEN) && !cn1_sent) {
    Serial1.begin(9600,SERIAL_7E1);
    delay(185);
    Serial1.print("P");
    delay(2);
    Serial1.print("+");
    delay(2);
    Serial1.print("0");
    delay(2);
    Serial1.print("0");
    delay(2);
    Serial1.print("0");
    delay(2);
    Serial1.print("0");
    delay(2);
    Serial1.print("0");
    delay(2);
    Serial1.print("\r");
    delayMicroseconds(2470);
    sendIncrementalPulses(CN1_PA,CN1_PB);
    cn1_sent = true;
    }
  if (!digitalRead(CN1_SEN)) cn1_sent = false;
  if (digitalRead(CN2_SEN) && !cn2_sent) {
    Serial2.begin(9600,SERIAL_7E1);
    delay(185);
    Serial2.print("P");
    delay(2);
    Serial2.print("+");
    delay(2);
    Serial2.print("0");
    delay(2);
    Serial2.print("0");
    delay(2);
    Serial2.print("0");
    delay(2);
    Serial2.print("0");
    delay(2);
    Serial2.print("0");
    delay(2);
    Serial2.print("\r");
    delayMicroseconds(2470);
    sendIncrementalPulses(CN2_PA,CN2_PB);
    cn2_sent = true;
    }
  if (!digitalRead(CN2_SEN)) cn2_sent = false;
}

void sendIncrementalPulses(int pin1, int pin2) {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  for (int i = 0; i < 10; i++) {
    digitalWrite(pin1,HIGH);
    delayMicroseconds(500);
    digitalWrite(pin2,HIGH);
    delayMicroseconds(500);
    digitalWrite(pin1,LOW);
    delayMicroseconds(500);
    digitalWrite(pin2,LOW);
    delayMicroseconds(500);
  }
}
