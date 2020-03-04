#pragma once
#include <FastLED.h>
#include "Position.h"
typedef Position pos;
// Properly defines the hardware
// button configurations
#define DOWN 8
#define UP 9
#define LEFT 11
#define RIGHT 10

class Game{
  protected:
    bool has_action = false;
    unsigned long lose_delay = 2000;
    unsigned long win_delay = 2000;
    unsigned long turn_delay = 500;
    unsigned long time_counter = 0;
    unsigned long win_timeout = 0;
    unsigned long lose_timeout = 0;
    unsigned long turn_timeout = 0;
    bool win_init = true;
    bool lose_init = true;
    int dims;
    pos ADJ[4] = {pos(0, 1), pos(1, 0), pos(0, -1), pos(-1, 0)};
  public:
  	Game(int d):dims(d){}
  	virtual ~Game(){}
    virtual bool play(unsigned long) = 0;
    virtual void action(int) = 0;
    virtual void draw_led(CHSV*,int) = 0;
};
