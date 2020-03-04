#pragma once
#include <FastLED.h>
#include "Game.h"
#include "Position.h"
typedef Position pos;

class Grid{
  private:
    Game* game;
    int* grid;
    CHSV** grid_col;
    int dims;
    int grid_size;
    int idx(int r, int c);
  public:
    Grid(int d, Game* ig);
    ~Grid();
    // Logical manipulation
    int get(pos& p);
    int get(int r, int c);
    void set(pos& p, int val);
    void set(int r, int c, int val);
    // Display manipulation
    CHSV* get_col(pos& p);
    CHSV* get_col(int r, int c);
    void set_col(pos& p, CHSV& col);
    void set_col(int r, int c, CHSV& col);
    // Board Utils
    void clear();
    void setall(int val);
    void setall_col(CHSV& col);
    void update_game(Game* g);
    // Convenient Drawings
    void emoji_smile();
    void emoji_frown();
};
