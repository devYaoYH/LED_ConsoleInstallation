#include <FastLED.h>
#define NUM_LEDS 50
#define DATA_PIN 5

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  for (int i=0;i<NUM_LEDS;++i){
    leds[i] = CRGB::Black;
  }
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<NUM_LEDS;++i){
    leds[i] = CRGB::Blue;
    FastLED.show();
    leds[i] = CRGB::Black;
    delay(50);
  }
  leds[NUM_LEDS-1] = CRGB::Red;
  FastLED.show();
  leds[NUM_LEDS-1] = CRGB::Black;
  delay(1000);
}
