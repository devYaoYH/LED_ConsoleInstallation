#pragma once
#include <FastLED.h>
#include <math.h>
#include "Game.h"
#include "Grid.h"
#include "Position.h"
// Defining possible actions
// Win condition (max snake length)
#define MAX_LEN 10
#define START_TIME 800

typedef Position pos;

class Snakes: public Game{
  protected:
    // Grid object for us to interact with main LED display
    Grid* g;
    // Possible grid logical values for this game
    enum VALS {
      ERR = -1,
      EMPTY = 0,
      FOOD = 1,
      SNAKE = 2,
      RANDOM = 3
    };
    // Game state
    enum STATE {
      LOSE = -1,
      PLAY = 0,
      WIN = 1
    };
    // Internal variables for game logic
    STATE state = PLAY;
    pos snake_locs[MAX_LEN];
    pos food_loc;
    int snake_len, cur_snake_idx;
    int last_dir,next_dir;
    int lose_counter;
    bool interrupt;
    // Helper functions
    void move(int dir);
    bool turn();
    void reset();
    void generate_food();
    
  public:
    // Importantly, the only constructor we need/should declare
    // is the following (int,Grid*) type - Inheritance handles the rest
    Snakes(int d, Grid* ig);

    // Do nothing destructor (do not call delete on g)
    // open issue, need to migrate to some form of shared_ptr design
    virtual ~Snakes();

    // Main play function called by Console.ino on every loop
    // passes the current time for game to keep track of and use
    bool play(unsigned long cur_time);

    // Function is called from Console.ino whenever a button has been
    // pressed. Passes the button pin as argument, see #define in Game.h
    // where we have pre-defined UP/DOWN/LEFT/RIGHT buttons to correspond
    // correctly with hardware.
    void action(int act_id);

    // Callback from Grid object to request for a customizable color value
    // for each logical value stored in grid's 2D int array
    void draw_led(CHSV* led, int val);
};
