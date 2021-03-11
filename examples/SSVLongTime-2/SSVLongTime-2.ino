#include "SSVLongTime.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET   16 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <SSVTimer.h>
SSVTimer Tmr1;

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  delay(100);

  //ssd1306 display init
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { Serial.println(F("SSD1306 allocation failed")); }
  display.clearDisplay();  
  display.setTextSize(1);  
  display.setCursor(0,0);  
  display.setTextColor(SSD1306_WHITE); 
  display.display();

  Tmr1.SetInterval(1000);
  Tmr1.SetEnabled(true);
  Tmr1.SetOnTimer(Tmr1Func);
}

void loop() 
{
 Tmr1.RefreshIt();
}

void Tmr1Func()
{

  display.clearDisplay(); 
  display.setCursor(0,0); 
  display.print("N:");  display.println(SSVLongTime.getUpTimeSec()); 
  display.print("O:");  display.println(Tmr1.GetCounter());
    
  Serial.print("New: "); Serial.print( SSVLongTime.getUpTimeSec() );
  Serial.print("  \tOld: "); Serial.print(Tmr1.GetCounter());

  Serial.print("  \tAge Str: "); Serial.println( Sec_To_Age_Str( SSVLongTime.getUpTimeSec() ) );
  display.print( Sec_To_Age_Str( SSVLongTime.getUpTimeSec() ) );

  display.display();
  //delay(1250);
}
