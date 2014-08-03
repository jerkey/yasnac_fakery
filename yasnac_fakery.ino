#define CN1_SEN 8 // goes high when it wants serial data
#define CN2_SEN 9 // goes high when it wants serial data

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
    delay(185);
    Serial.print("P");
    delayMicroseconds(1000);
    Serial.print("+");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("\r");
    cn1_sent = true;
    }
  if (!digitalRead(CN1_SEN)) cn1_sent = false;
  if (digitalRead(CN2_SEN) && !cn2_sent) {
    delay(185);
    Serial.print("P");
    delayMicroseconds(1000);
    Serial.print("+");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("0");
    delayMicroseconds(1000);
    Serial.print("\r");
    cn2_sent = true;
    }
  if (!digitalRead(CN2_SEN)) cn2_sent = false;
}

