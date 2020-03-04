#include "Grid.h"
Grid::Grid(int d):dims(d),grid_size(d*d){
  // Grab some space on heap
  grid = malloc(sizeof(int)*grid_size+1);
  for (int i=0;i<grid_size;++i) grid[i] = 0;
}

Grid::idx(int r, int c){
  int i = r*dims + c;
  if (r < 0 || r >= dims || c < 0 || c >= dims) return grid_size+1;
  else return i;
}

int Grid::get(pos &p){
  return get(p.y,p.x);
}

int Grid::get(int r, int c){
  int i = idx(r,c);
  if (i == grid_size+1) return -1;
  else return grid[idx(r,c)];
}

void Grid::set(pos &p, int val){
  set(p.y,p.x,val);
}

void Grid::set(int r, int c, int val){
  grid[idx(r,c)] = val;
}

void Grid::clear(){
  for (int i=0;i<grid_size+1;++i){
    grid[i] = 0;
  }
}

void Grid::setall(int val){
  for (int i=0;i<grid_size;++i){
    grid[i] = val;
  }
}

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

Grid::~Grid(){
  delete grid;
}
