#define CN1_SEN 8 // goes high when it wants serial data
#define CN2_SEN 9 // goes high when it wants serial data
#define CN1_PB 10 // PB pin

#define CN2_PB 11 // PB pin
#define CN2_PC 12 // PC pin

#define TUNED43US 33 // how many "delayMicroseconds" to achieve 43uS actual time

boolean cn1_sent = false; // whether we have sent data for this one yet
boolean cn2_sent = false; // whether we have sent data for this one yet

int state; // binary state of pin1 (bit0) and pin2 (bit1)

void setup()  
{
  Serial.begin(9600,SERIAL_7E1);
  digitalWrite(CN1_PB,HIGH);
  digitalWrite(CN2_PB,HIGH);
  digitalWrite(CN2_PC,HIGH);
  pinMode(CN1_PB,OUTPUT);
  pinMode(CN2_PB,OUTPUT);
  pinMode(CN2_PC,OUTPUT);
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
    delayMicroseconds(2470+786);
    digitalWrite(1,HIGH);
    pinMode(1,OUTPUT);
    UCSR0B &= (255 - (1<<TXEN0)); // change USART0 pin to be a GPIO again
    // digitalWrite(CN1_PC,LOW);
    sendIncrementalPulses(1,CN1_PB);
    cn1_sent = true;
    }
  if (!digitalRead(CN1_SEN)) {
    cn1_sent = false;
    digitalWrite(CN1_PB,HIGH);
    //digitalWrite(CN1_PC,HIGH);
  }
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
    delayMicroseconds(2470+786);
    digitalWrite(1,HIGH);
    pinMode(1,OUTPUT);
    UCSR0B &= (255 - (1<<TXEN0)); // change USART0 pin to be a GPIO again
    digitalWrite(CN2_PC,LOW);
    sendIncrementalPulses(1,CN2_PB);
    cn2_sent = true;
    }
  if (!digitalRead(CN2_SEN)) {
    cn2_sent = false;
    digitalWrite(CN2_PB,HIGH);
    digitalWrite(CN2_PC,HIGH);
  }
}

void sendIncrementalPulses(int pin1, int pin2) {
  state = 1; // which pin1 or pin2 to toggle next
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
    if (state == 1) digitalWrite(pin1,!digitalRead(pin1));
    if (state == 2) digitalWrite(pin2,!digitalRead(pin2));
    delayMicroseconds(TUNED43US);
    state = state ^ 3;
  }
  if (state == 1) digitalWrite(pin1,!digitalRead(pin1));
  if (state == 2) digitalWrite(pin2,!digitalRead(pin2));
  delayMicroseconds(TUNED43US);
  delayMicroseconds(TUNED43US+9); // this is a double-length state
  state = state ^ 3;
}
