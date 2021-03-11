#include "SSVLongTime.h"

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  delay(100);
  
  
}

void loop() 
{
  Serial.println( SSVLongTime.getUpTimeSec() );
  delay(1000);
}
