#pragma once
#include <FastLED.h>
#include "Game.h"
#include "Grid.h"
typedef Position pos;

#define HUE_GAIN 2
#define HUE_OFFSET 5

class Animate_Spectrum: public Game{
  protected:
    Grid* g;
    // Game state
    enum STATE {
      HORIZONTAL = 1,
      VERTICAL = 2,
      SLANTED = 3
    };
    STATE state = HORIZONTAL;
    unsigned long mode_delay = 60000;
    unsigned long mode_timeout = 60000;
    uint8_t hue_offset;
    bool turn();
    void increment_hue();
    void draw_led(CHSV*,int);
  public:
    Animate_Spectrum(int d, Grid* ig);
    ~Animate_Spectrum();
    bool play(unsigned long cur_time);
    void action(int act_id);
};
