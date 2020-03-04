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
    Grid* g;
    // Possible grid values for this game
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
    STATE state = PLAY;
    pos snake_locs[MAX_LEN];
    pos food_loc;
    int snake_len, cur_snake_idx;
    int last_dir,next_dir;
    int lose_counter;
    bool interrupt;
    void move(int dir);
    bool turn();
    void reset();
    void generate_food();
    void draw_led(CHSV* led, int val);
  public:
    Snakes(int d, Grid* ig);
    virtual ~Snakes();
    bool play(unsigned long cur_time);
    void action(int act_id);
};
