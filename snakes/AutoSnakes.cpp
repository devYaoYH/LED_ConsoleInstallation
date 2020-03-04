#include "AutoSnakes.h"
AutoSnakes::AutoSnakes(int d, Grid* ig):Snakes(d,ig){}

AutoSnakes::~AutoSnakes(){}

float AutoSnakes::score_loc(pos& p){
  if (g->get(p) == ERR || g->get(p) == SNAKE) return -1;
  int dist_to_food = p.dist(food_loc);
  if (dist_to_food == 0) return 100;
  float score = (float)1/p.dist(food_loc);
  return score;
}

void AutoSnakes::ai_move(){
  // Look at where we will end up next
  // and pick next action
  int new_idx = (cur_snake_idx + 1)%MAX_LEN;
  // Only make permissible moves (-1, 0 1) to last_dir
  int max_dir = 0;
  float max_score = -1;
  for (int i=-1;i<=1;++i){
    int dir = (last_dir + i + 4) % 4;
    pos new_p = snake_locs[cur_snake_idx].add(ADJ[dir]); // Move snake by 1 position
    float cur_score = score_loc(new_p);
    if (cur_score > max_score){
      max_dir = dir;
      max_score = cur_score;
    }
  }
  next_dir = max_dir;
}

bool AutoSnakes::play(unsigned long cur_time){
  // Defer actual logic to Snakes
  bool has_moved = Snakes::play(cur_time);
  // Only run this 'expensive' ai_move once
  // per valid turn
  // Further check if player has interrupted
  // with an action -> player takes over
  if (has_moved && !interrupt){
    // Have the ai play our Snakes game by
    // simulating calls to action
    ai_move();
  }
  return has_moved;
}
