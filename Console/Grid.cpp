#pragma once
#include "Grid.h"
Grid::Grid(int d, Game* ig):game(ig),dims(d),grid_size(d*d){
  // Grab some space on heap
  grid = malloc(sizeof(int)*grid_size+1);
  grid_col = malloc(sizeof(CHSV*)*grid_size+1);
  for (int i=0;i<grid_size;++i){
    grid[i] = 0;
    grid_col[i] = new CHSV(0,0,0);
  }
}

Grid::~Grid(){
  delete grid;
  delete[] grid_col;
}

Grid::idx(int r, int c){
  int i = r*dims + c;
  if (r < 0 || r >= dims || c < 0 || c >= dims) return grid_size+1;
  else return i;
}

// Logical Manipulation
int Grid::get(pos& p){
  return get(p.y,p.x);
}

int Grid::get(int r, int c){
  int i = idx(r,c);
  if (i == grid_size+1) return -1;
  else return grid[i];
}

void Grid::set(pos& p, int val){
  set(p.y,p.x,val);
}

void Grid::set(int r, int c, int val){
  int i = idx(r,c);
  grid[i] = val;
  // Grab color as defined in game
  game->draw_led(grid_col[i],val);
}

// Visual Manipulation
CHSV* Grid::get_col(pos& p){
  return get_col(p.y,p.x);
}

CHSV* Grid::get_col(int r, int c){
  int i = idx(r,c);
  if (i == grid_size+1) return 0;
  else return grid_col[i];
}

void Grid::set_col(pos& p, CHSV& col){
  set_col(p.x,p.y,col);
}

void Grid::set_col(int r, int c, CHSV& col){
  *grid_col[idx(r,c)] = col;
}

// Block-based settings
void Grid::clear(){
  for (int i=0;i<grid_size+1;++i){
    grid[i] = 0;
    grid_col[i]->setHSV(0, 0, 0);
  }
}

void Grid::setall(int val){
  for (int i=0;i<grid_size;++i){
    grid[i] = val;
  }
}

void Grid::setall_col(CHSV& col){
  for (int i=0;i<grid_size+1;++i){
    grid_col[i]->setHSV(0, 0, 0);
  }
}

void Grid::update_game(Game* g){
  game = g;
}

// Convenience Emoji-Drawing Functions
void Grid::emoji_frown(){
  clear();
  int mr = dims/2; int mc = dims/2;
  // Frown
  set(mc+2,mr+2,1);
  set(mc-2,mr+2,1);
  set(mc+3,mr+3,1);
  set(mc-3,mr+3,1);
  for(int i=mc-1;i<=mc+1;++i) set(i,mr+1,1);
  // Eyes
  set(mc+1,mr-1,1);
  set(mc-1,mr-1,1);
  set(mc+1,mr-2,1);
  set(mc-1,mr-2,1);
}

void Grid::emoji_smile(){
  clear();
  int mr = dims/2; int mc = dims/2;
  // Smile
  set(mc+3,mr,1);
  set(mc-3,mr,1);
  set(mc+2,mr+1,1);
  set(mc-2,mr+1,1);
  for(int i=mc-1;i<=mc+1;++i) set(i,mr+2,1);
  // Eyes
  set(mc+1,mr-1,1);
  set(mc-1,mr-1,1);
  set(mc+1,mr-2,1);
  set(mc-1,mr-2,1);
}
