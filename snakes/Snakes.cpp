#include "Snakes.h"
bool Snakes::play(){
  switch(state){
    case PLAY:
      if (has_action){
        has_action = false;
        // Render our snake again to g obj
        int last_pos = (cur_snake_idx - snake_len + MAX_LEN) % MAX_LEN;
        g->set(snake_locs[last_pos],EMPTY);
        g->set(snake_locs[cur_snake_idx],SNAKE);
        return true;
      }
      else{
        return false;
      }
      break;
    default:
      return false;
  }
}

void Snakes::action(int act_id){
  int dir = 0;
  switch(act_id){
    case UP:
      dir = 0;
      break;
    case RIGHT:
      dir = 1;
      break;
    case DOWN:
      dir = 2;
      break;
    case LEFT:
      dir = 3;
      break;
    default:
      return; // Do Nothing
  }
  int new_idx = (cur_snake_idx + 1)%MAX_LEN;
  pos new_p = snake_locs[cur_snake_idx].add(ADJ[dir]); // Move snake by 1 position
  // Check if we have collided with the borders (no update)
  int g_contents = g->get(new_p);
  if (g_contents == (int)ERR){ // Error, out-of-bounds
    state = LOSE;
    return;
  }
  else if (g_contents == (int)FOOD){ // Grow snake!
    snake_len++;
    //TODO: Change food position
  }
  snake_locs[new_idx].update(new_p);
  cur_snake_idx = new_idx;
}

int Snakes::get(int r, int c){
  if (g == 0) return ERR;
  return g->get(r,c);
}
