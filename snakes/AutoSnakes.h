#pragma once
#include "Snakes.h"
#include "Grid.h"
#include "Position.h"

typedef Position pos;

class AutoSnakes: public Snakes{
  private:
    void ai_move();
    float score_loc(pos& p);
  public:
    AutoSnakes(int d, Grid* ig);
    virtual ~AutoSnakes();
    bool play(unsigned long cur_time);
};
