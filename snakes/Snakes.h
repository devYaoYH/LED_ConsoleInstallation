#pragma once
#include "Game.h"
#include "Grid.h"
#include "Position.h"
// Defining possible actions
#define DOWN 8
#define UP 9
#define LEFT 10
#define RIGHT 11
// Win condition (max snake length)
#define MAX_LEN 10

typedef Position pos;
class Snakes: public Game{
  private:
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
    pos ADJ[4] = {pos(0, 1), pos(1, 0), pos(0, -1), pos(-1, 0)};
    pos snake_locs[MAX_LEN];
    pos food_loc;
    int snake_len, cur_snake_idx;
    int dims,last_dir;
    Grid* g;
    void move(int dir);
    bool turn();
    void reset();
    void generate_food();
  public:
    Snakes():snake_len(1),cur_snake_idx(0),dims(0),last_dir(0),g(new Grid()){
      reset();
    }
    Snakes(int d):snake_len(1),cur_snake_idx(0),dims(d),last_dir(0),g(new Grid(d)){
      reset();
    }
    bool play();
    bool play(unsigned long cur_time);
    void action(int act_id);
    int get(int r, int c);
};
