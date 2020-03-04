#pragma once
#include "Position.h"
typedef Position pos;
class Grid{
  private:
    int* grid;
    int dims;
    int grid_size;
    int idx(int r, int c);
  public:
    Grid():dims(0),grid(0),grid_size(0){}
    Grid(int d);
    ~Grid();
    int get(pos& p);
    int get(int r, int c);
    void set(pos& p, int val);
    void set(int r, int c, int val);
    void clear();
    void setall(int val);
    void emoji_smile();
    void emoji_frown();
};
