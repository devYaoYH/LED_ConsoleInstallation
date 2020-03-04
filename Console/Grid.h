#pragma once
#include <FastLED.h>
#include "Game.h"
#include "Position.h"
typedef Position pos;

class Grid{
  private:
    // Object pointers for required interaction
    Game* game;
    int* grid;
    CHSV** grid_col;

    // Out-Of-Bounds tracking
    int dims;
    int grid_size;

    // Helper function to serialize grid coordinates
    int idx(int r, int c);

  public:
    // Keeps track of Game object to use the draw_led(CHSV*,int) function
    Grid(int d, Game* ig);

    // Properly frees up heap usage
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
    void update_game(Game* g);  // Called within Console.ino to reuse Grid objects
    // Convenient Drawings
    void emoji_smile();
    void emoji_frown();
};
