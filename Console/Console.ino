#pragma once
#include <FastLED.h>
#include "Sensor.h"
#include "Grid.h"
#include "Position.h"
#include "Snakes.h"
#include "AutoSnakes.h"
#include "Animate.h"
#define DIMS 7
#define NUM_LEDS 50
#define DATA_PIN 5
#define LEFT_BTN 11
#define RIGHT_BTN 10
#define UP_BTN 8
#define DOWN_BTN 9

#define REFRESH_RATE 30

#define NUM_COLORS 4

// Game Types
#define NUM_MODES 2 //IMPT! Need to prevent overflow of cycling
#define SPECTRUM 0
#define SNAKE 1
#define ACM 2
// Additional Type definitions

typedef Sensor sensor;
typedef Position pos;

// Global Control Vars
int cur_idx = 0;
unsigned long btn_timeout = 100;
unsigned long screen_refresh = 0;

// Cycling between Games
unsigned long gameMode_delay = 180000;
unsigned long gameMode_timeout = 0;

// LED data array
CRGB leds[NUM_LEDS];
CRGB colors[NUM_COLORS] = {
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
      disp_grid->update_game(cur_game);
      break;
    //TODO: Implement Spectrum cycling with HSV
    case SPECTRUM:
      delete cur_game;
      disp_grid->clear();
      cur_game = new Animate_Spectrum(DIMS,disp_grid);
      disp_grid->update_game(cur_game);
      break;
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

void update_screen(){
//  Serial.println("Has Update");
  for(int r=0;r<DIMS;++r){
    for(int c=0;c<DIMS;++c){
      hsv2rgb_rainbow(*disp_grid->get_col(r,c),leds[grid[c][r]]);
//      Serial.print(disp_grid->get(r,c));
    }
//    Serial.println("");
  }
}

void setup() {
  // DEBUG
  Serial.begin(9600);
  Serial.println("Wake");
  delay(50);
  // Setup
  randomSeed(0);
  for (int i=0;i<NUM_LEDS;++i){
    leds[i] = CRGB::Black;
  }
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  // Create a Game
  disp_grid = new Grid(DIMS,0);
  Serial.println("Init Grid");
  cur_game = new Animate_Spectrum(DIMS,disp_grid);
  Serial.println("Init Game");
  disp_grid->update_game(cur_game);
  update_screen();
  Serial.println("Draw Screen");
  // Create Sensor objects
  for (int i=0;i<4;++i){
    SENSOR[i]->update_pin(i+8);
    pinMode(i+8, INPUT_PULLUP);
  }
  Serial.println("Init Success!");
}

void loop() {
  bool is_update = false;
  unsigned long cur_time = millis();

  // Handle input to buttons
  for (sensor* s: SENSOR){
    if (digitalRead(s->PIN) == HIGH) s->state = false;
    if (cur_time > s->timeout && digitalRead(s->PIN) == LOW && !s->state){
      // Reset IDLE timer
      gameMode_timeout = cur_time + gameMode_delay;
      btn_pressed(s->PIN);
      cur_game->action(s->PIN);
      s->timeout = cur_time + btn_timeout;
      s->state = true;
      is_update = true;
    }
  }

  // Run our own Control Loop
  if (cur_time > gameMode_timeout){
    gameMode_timeout = cur_time + gameMode_delay;
    btn_pressed(DOWN_BTN);
  }

  // Call game update
  is_update = cur_game->play(cur_time); //Tracks whether there is an UI update to be applied

  // If we have an update this turn, sync visuals
  if (is_update){
    update_screen();
  }

  // Refreshes display every few milliseconds rather than every loop
  cur_time = millis();
  if (cur_time > screen_refresh){
    FastLED.show();
    screen_refresh = cur_time + REFRESH_RATE;
  }
}
