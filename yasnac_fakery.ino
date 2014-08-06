#define CN1_SEN 2 // goes high when it wants serial data
#define CN1_PA 18 // this is the same as Serial1 TX pin (must be 18)
#define CN1_PB  3 // PB pin

#define CN2_SEN 4 // goes high when it wants serial data
#define CN2_PA 16 // this is the same as Serial2 TX pin (must be 16)
#define CN2_PB  5 // PB pin

#define TUNED43US 38 // how many "delayMicroseconds" to achieve 43uS actual time

boolean cn1_sent = false; // whether we have sent data for this one yet
boolean cn2_sent = false; // whether we have sent data for this one yet

int state; // binary state of pin1 (bit0) and pin2 (bit1)

void setup()  
{
  Serial.begin(9600); // ,SERIAL_7E1);
  Serial.println("i lie to YASNACs");
  digitalWrite(CN1_PB,HIGH);
  digitalWrite(CN2_PB,HIGH);
  pinMode(CN1_PB,OUTPUT);
  pinMode(CN2_PB,OUTPUT);
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
    delayMicroseconds(2470+693);
    UCSR1B &= (255 - (1<<TXEN1)); // change USART1 pin to be a GPIO again
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
    delayMicroseconds(2470+693);
    UCSR2B &= (255 - (1<<TXEN2)); // change USART2 pin to be a GPIO again
    sendIncrementalPulses(CN2_PA,CN2_PB);
    cn2_sent = true;
    }
  if (!digitalRead(CN2_SEN)) cn2_sent = false;
}

void sendIncrementalPulses(int pin1, int pin2) {
  state = 2; // binary state of pin1 (bit0) and pin2 (bit1)
  pulseSeq(30,pin1,pin2); // first
  pulseSeq(30,pin1,pin2); // second
  pulseSeq(30,pin1,pin2); // third
  pulseSeq(62,pin1,pin2); // fourth
  pulseSeq(30,pin1,pin2); // fifth
  pulseSeq(30,pin1,pin2); // sixth
  pulseSeq(62,pin1,pin2); // seventh
  pulseSeq(30,pin1,pin2); // eighth
  pulseSeq(20,pin1,pin2); // last time
} // the above numbers were based on spreadsheet analysys of realencoder-notes.ods and logicdata

void pulseSeq(int count, int pin1, int pin2) {
  for (int i = 0; i < count; i++) {
    digitalWrite(pin1,state & 1);
    digitalWrite(pin2,state & 2);
    delayMicroseconds(TUNED43US);
    state += 1;
  }
  digitalWrite(pin1,state & 1);
  digitalWrite(pin2,state & 2);
  delayMicroseconds(TUNED43US);
  delayMicroseconds(TUNED43US); // this is a double-length state
  state += 1;
}
