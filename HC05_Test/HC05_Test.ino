#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3); // SoftwareSerial(RX, TX) on arduino board

uint8_t c = ' ';
bool NL = true;

void setup()
{
  Serial.begin(115200);
  BTserial.begin(38400);

  Serial.print("Sketch:   ");
  Serial.println(__FILE__);
  Serial.print("Uploaded: ");
  Serial.println(__DATE__);
  Serial.println("");
}

void loop()
{
  if (BTserial.available())
  {
    c = BTserial.read();
    Serial.write(c);
  }

  if (Serial.available())
  {
    // for example, "at" will be read 4 times: 
    // 97 -> 116 -> 13 -> 10 (a -> t -> CR -> NL in ASCII)
    c = Serial.read();
    BTserial.write(c); 

    // to hold up the first character in an inputted message
    if (NL)
    {
      Serial.print(">>> ");
      NL = false;
    }

    Serial.write(c);

    // if meeting the end of the inputted message, print >>> next time
    if (c == 10)
    {
      NL = true;
    }
  }
}