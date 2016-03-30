#include <Adafruit_NeoPixel.h>
#include "audio.h"
#define body_pin 4
#define body_pin2 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

boolean FLAG_1 = 0;
boolean FLAG_2 = 0;

void judge()
{
  if((digitalRead(body_pin)==1)&&(digitalRead(body_pin2)==0))
  {
    FLAG_1 = 1;
    delay(200);
  }
  if((digitalRead(body_pin)==1)&&(digitalRead(body_pin2)==1)&&(FLAG_1 == 1))
  {

    colorWipe(color[random(1, 10)]);
    audio_choose(1);
    Serial.println("COMING IN");
    FLAG_1 = 0;
    delay(1300);    //1300
  }
  
 if((digitalRead(body_pin)==0)&&(digitalRead(body_pin2)==1))
  {
    FLAG_2 = 1;
    delay(200);    //2000
  }
  if((digitalRead(body_pin)==1)&&(digitalRead(body_pin2)==1)&&(FLAG_2 == 1))
  {
    colorWipe(color[random(1, 10)]);
    audio_choose(2);
    Serial.println("GOING OUT");
    FLAG_2 = 0;
    delay(1300);   //2000
  }
}

void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
