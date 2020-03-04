#pragma once
#include <FastLED.h>
#include "Sensor.h"
#include "Grid.h"
#include "Position.h"
#include "Snakes.h"
#include "AutoSnakes.h"
#define DIMS 7
#define NUM_LEDS 50
#define DATA_PIN 5
#define LEFT_BTN 11
#define RIGHT_BTN 10
#define UP_BTN 8
#define DOWN_BTN 9

#define REFRESH_RATE 30

#define NUM_STATES 4

// Game Types
#define NUM_MODES 1 //IMPT! Need to prevent overflow of cycling
#define SNAKE 0
#define SPECTRUM 1
#define ACM 2
// Additional Type definitions

typedef Sensor sensor;
typedef Position pos;

// Global Control Vars
int cur_idx = 0;
unsigned long btn_timeout = 100;
unsigned long screen_refresh = 0;

// LED data array
CRGB leds[NUM_LEDS];
CRGB colors[NUM_STATES] = {
  CRGB::Black,
  CRGB::Aquamarine,
  CRGB::RosyBrown,
  CRGB::Green
};

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
Grid* disp_grid;

void spawn_game(int GAME){
  switch(GAME){
    // Snake game with auto player
    case SNAKE:
      // First, destroy our current game
      delete cur_game;
      // Clear the grid
      disp_grid->clear();
      // Create new instance of our game
      cur_game = new AutoSnakes(DIMS,disp_grid);
      break;
    //TODO: Implement Spectrum cycling with HSV
//    case SPECTRUM:
//      delete cur_game;
//      cur_game = new Animate_Spectrum(DIMS);
//      break;
    //TODO: Implement a system to print characters
//    case ACM:
//      delete cur_game;
//      cur_game = new Animate_ACM(DIMS);
//      break;
    default:
      break;
  }
}

void btn_pressed(int btn_pin){
  switch(btn_pin){
    // Left Right are used for games
    // and not tracked by OS
    case LEFT_BTN:
      break;
    case RIGHT_BTN:
      break;
    // Up Down buttons to switch modes
    case UP_BTN:
      cur_idx = (cur_idx - 1 + NUM_MODES) % NUM_MODES;
      Serial.print("UP: ");
      Serial.println(cur_idx);
      spawn_game(cur_idx);
      break;
    case DOWN_BTN:
      cur_idx = (cur_idx + 1) % NUM_MODES;
      Serial.print("DOWN: ");
      Serial.println(cur_idx);
      spawn_game(cur_idx);
      break;
    default:
      return;
  }
}

int game_enum_to_col(int e){
  switch(e){
    case (0):
      return 0;
    case (1):
      return 1;
    case (2):
      return 2;
    case (3):
      return -1;
    default:
      return 0;
  }
}

void update_screen(){
  Serial.println("Has Update");
  // Cycle through to sync with new grid
  for (int x=0;x<DIMS;++x){
    for (int y=0;y<DIMS;++y){
      int state = game_enum_to_col(disp_grid->get(y,x));
      if (state != -1 && state < NUM_STATES){
        leds[grid[x][y]] = colors[state];
      }
      else{
        long rnd_col = random((1<<24)-1);
        uint8_t r = rnd_col >> 16;
        uint8_t g = rnd_col >> 8;
        uint8_t b = rnd_col;
        leds[grid[x][y]] = CRGB(r, g, b);
      }
      Serial.print(state);
    }
    Serial.println("");
  }
}

void setup() {
  delay(50);
  // Setup
  randomSeed(0);
  for (int i=0;i<NUM_LEDS;++i){
    leds[i] = CRGB::Black;
  }
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  // Create a Game
  disp_grid = new Grid(DIMS);
  cur_game = new AutoSnakes(DIMS,disp_grid);
  update_screen();
  // Create Sensor objects
  for (int i=0;i<4;++i){
    SENSOR[i]->update_pin(i+8);
    pinMode(i+8, INPUT_PULLUP);
  }
  // DEBUG
  Serial.begin(9600);
}

void loop() {
  bool is_update = false;
  unsigned long cur_time = millis();

  // Handle input to buttons
  for (sensor* s: SENSOR){
    if (digitalRead(s->PIN) == HIGH) s->state = false;
    if (cur_time > s->timeout && digitalRead(s->PIN) == LOW && !s->state){
      btn_pressed(s->PIN);
      cur_game->action(s->PIN);
      s->timeout = cur_time + btn_timeout;
      s->state = true;
      is_update = true;
    }
  }

  // Call game update
  is_update = cur_game->play(cur_time); //Tracks whether there is an UI update to be applied

  // If we have an update this turn, sync visuals
  if (is_update){
    update_screen();
  }

  // Refreshes display every few milliseconds rather than every loop
  if (cur_time > screen_refresh){
    FastLED.show();
    screen_refresh = cur_time + REFRESH_RATE;
  }
}
