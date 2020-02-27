#include <FastLED.h>
#include "Sensor.h"
#include "Snakes.h"
#include "Position.h"
#define DIMS 7
#define NUM_LEDS 50
#define DATA_PIN 5
#define LEFT_BTN 8
#define RIGHT_BTN 9
#define REFRESH_RATE 30

typedef Sensor sensor;
typedef Position pos;

// Global Control Vars
int cur_idx = 0;
unsigned long btn_timeout = 100;
unsigned long screen_refresh = 0;

// LED data array
CRGB leds[NUM_LEDS];

// Sensors array
sensor* SENSOR[4] = {new sensor(), new sensor(), new sensor(), new sensor()};

// 2D coord to 
int grid[DIMS][DIMS] = 
  {{1,2,3,4,5,6,7},
  {14,13,12,11,10,9,8},
  {15,16,17,18,19,20,21},
  {28,27,26,25,24,23,22},
  {29,30,31,32,33,34,35},
  {42,41,40,39,38,37,36},
  {43,44,45,46,47,48,49}};

// Game Actual
Game* cur_game;

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  // Setup
  randomSeed(0);
  for (int i=0;i<NUM_LEDS;++i){
    leds[i] = CRGB::Black;
  }
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.show();
  for (int i=0;i<4;++i){
    SENSOR[i]->update_pin(i+8);
    pinMode(i+8, INPUT_PULLUP);
  }
  // Create a Game
  cur_game = new Snakes(DIMS);
  // DEBUG
  Serial.begin(9600);
}

void btn_pressed(int btn_pin){
  switch(btn_pin){
    case LEFT_BTN:
      cur_idx--;
      cur_idx = (cur_idx + NUM_LEDS)%NUM_LEDS;
      cur_game->action(LEFT_BTN);
      break;
    case RIGHT_BTN:
      cur_idx++;
      cur_idx = cur_idx%NUM_LEDS;
      cur_game->action(RIGHT_BTN);
      break;
    default:
      return;
  }
}

CRGB game_enum_to_col(int e){
  switch(e){
    case (0):
      return CRGB::Black;
    case (1):
      return CRGB::Aquamarine;
    case (2):
      return CRGB::RosyBrown;
    case (3):
      long rnd_col = random((1<<24)-1);
      uint8_t r = rnd_col >> 16;
      uint8_t g = rnd_col >> 8;
      uint8_t b = rnd_col;
      return CRGB(r, g, b);
    default:
      return CRGB::Black;
  }
}

void loop() {
  bool is_update = false;
  unsigned long cur_time = millis();

  // Handle input to buttons
  for (sensor* s: SENSOR){
    if (digitalRead(s->PIN) == HIGH) s->state = false;
    if (cur_time > s->timeout && digitalRead(s->PIN) == LOW && !s->state){
      btn_pressed(s->PIN);
      s->timeout = cur_time + btn_timeout;
      s->state = true;
      is_update = true;
    }
  }

  // Call game update
  is_update = cur_game->play(); //Tracks whether there is an UI update to be applied

  // If we have an update this turn, sync visuals
  if (is_update){
    // Cycle through to sync with new grid
    for (int x=0;x<DIMS;++x){
      for (int y=0;y<DIMS;++y){
        leds[grid[x][y]] = game_enum_to_col(cur_game->get(y,x));
      }
    }
  }

  // Refreshes display every few milliseconds rather than every loop
  if (cur_time > screen_refresh){
    FastLED.show();
    screen_refresh = cur_time + REFRESH_RATE;
  }
}
