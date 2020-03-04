#pragma once
#include <FastLED.h>
#include "Game.h"
#include "Grid.h"
typedef Position pos;

#define HUE_GAIN 2
#define HUE_OFFSET 5

class Animate_Spectrum: public Game{
  protected:
    // Grid object for us to interact with main LED display
    Grid* g;
    // Game state
    enum STATE {
      HORIZONTAL = 1,
      VERTICAL = 2,
      SLANTED = 3
    };
    // Internal variables
    STATE state = HORIZONTAL;
    unsigned long mode_delay = 60000;
    unsigned long mode_timeout = 60000;
    uint8_t hue_offset;
    // Helper functions
    bool turn();
    void increment_hue();

  public:
    // Similar to Snakes.h, only declare and define this constructor
    Animate_Spectrum(int d, Grid* ig);

    // Do not delete g (or set its value to 0 first)
    ~Animate_Spectrum();

    // Called every loop by Console.ino, mainly just used to defer logic
    // to some internal function and keep track of time
    bool play(unsigned long cur_time);

    // Stub function, requires definition but does nothing
    void action(int act_id);

    // Similar stub function, does not need to do anything
    void draw_led(CHSV*,int);
};
