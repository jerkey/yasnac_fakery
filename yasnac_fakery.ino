/*
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 by jerquee based on a snippet by Tom Igoe
 based on Mikal Hart's example
 This example code is in the public domain.
 */
#include <SoftwareSerial.h>

#define CN1_SEN 9 // send out the serial after this goes high
#define CN2_SEN 8

boolean cn1_sent = false;
boolean cn2_sent = false;

SoftwareSerial cn1(10, 11); // RX, TX
SoftwareSerial cn2(13, 12); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
//  Serial.begin(57600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }

  // set the data rate for the SoftwareSerial port
  cn1.begin(9600);
  cn2.begin(9600);
}

void loop() // run over and over
{
  if (digitalRead(CN1_SEN) && !cn1_sent) {
    cn1.write("P+00000\r");
    cn1_sent = true;
    }
  if (digitalRead(CN2_SEN) && !cn2_sent) {
    cn2.write("P+00000\r");
    cn2_sent = true;
    }
}

