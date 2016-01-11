#include "audio.h"
#include "key.h"

#include <Adafruit_NeoPixel.h>
#define PIN A0
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

//#include <SoftwareSerial.h>

uint32_t color[9] =
{
  strip.Color(0, 0, 0), strip.Color(255, 0, 0), strip.Color(248, 141, 30), strip.Color(255, 255, 0), strip.Color(0, 255, 0), strip.Color(0, 127, 255), strip.Color(0, 0, 255), strip.Color(139, 0, 255), strip.Color(255, 255, 255)
};

#define body_pin 4
#define body_pin2 6
int i = 1;
int music_vol = 28; //初始音量0~30

boolean play_pause;
boolean play_stop;
boolean FLAG_1 = 0;
boolean FLAG_2 = 0;
void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(body_pin, INPUT);
  pinMode(body_pin2, INPUT);
//  key_init();

  audio_init(DEVICE_Flash, MODE_One_END, music_vol);

  strip.begin();	//初始化LED
  strip.show(); // Initialize all pixels to 'off'

  for (int i = 0; i < 9; i++)
  {
    colorWipe(color[i]);
    delay(300);
  }
  colorWipe(color[0]);
}

void loop() {
  judge();
  if (!digitalRead(body_pin)&&!digitalRead(body_pin2))
   {
    colorWipe(color[0]);
    FLAG_1 = 0;
    FLAG_2 = 0;
   }
}

void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
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


