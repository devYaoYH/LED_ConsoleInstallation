#pragma once
#include "Game.h"
#include "Grid.h"
#include "Position.h"
// Defining possible actions
#define UP 8
#define RIGHT 9
#define DOWN 10
#define LEFT 11
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
      SNAKE = 2
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
    int snake_len, cur_snake_idx;
    int dims;
    Grid* g;
  public:
    Snakes():dims(0),g(new Grid()),snake_len(1),cur_snake_idx(0){
      snake_locs[0].update(0,0);
    }
    Snakes(int d):dims(d),g(new Grid(d)),snake_len(1),cur_snake_idx(0){
      snake_locs[cur_snake_idx].update(d/2,d/2);
    }
    bool play();
    void action(int act_id);
    int get(int r, int c);
};
