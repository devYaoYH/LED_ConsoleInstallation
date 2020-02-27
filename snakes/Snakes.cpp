#include "Snakes.h"
void Snakes::generate_food(){
  int rc = time_counter % dims;
  int rr = (time_counter >> 10) % dims;
  g->set(food_loc,EMPTY);
  food_loc.update(rc,rr);
  g->set(food_loc,FOOD);
}

void Snakes::reset(){
  turn_delay = 1000;
  cur_snake_idx = 0;
  snake_len = 1;
  snake_locs[cur_snake_idx].update(dims/2,dims/2);
  g->set(snake_locs[cur_snake_idx],SNAKE);
  generate_food();
}

bool Snakes::turn(){
  switch(state){
    case PLAY:
      lose_init = true;
      win_init = true;
      if (has_action){
        has_action = false;
        // Render our snake again to g obj
        int last_pos = (cur_snake_idx - snake_len + MAX_LEN) % MAX_LEN;
        g->set(snake_locs[last_pos],EMPTY);
        g->set(snake_locs[cur_snake_idx],SNAKE);
        return true;
      }
      else if (time_counter > turn_timeout){
        turn_timeout = time_counter + turn_delay;
        move(last_dir);
        return turn();
      }
      break;
    case LOSE:
      if (lose_init){
        lose_timeout = time_counter + lose_delay;
        g->setall(FOOD);
        lose_init = false;
        return true;
      }
      if (time_counter > lose_timeout){
        state = PLAY;
        g->clear();
        reset();
        return true;
      }
    case WIN:
      if (win_init){
        win_timeout = time_counter + win_delay;
        g->setall(SNAKE);
        win_init = false;
        return true;
      }
      if (time_counter > win_timeout){
        state = PLAY;
        g->clear();
        reset();
        return true;
      }
    default:
      return false;
  }
  return false;
}

bool Snakes::play(){
  return turn();
}

bool Snakes::play(unsigned long cur_time){
  time_counter = cur_time;
  return turn();
}

void Snakes::action(int act_id){
  switch(act_id){
    case RIGHT:
      last_dir = (last_dir + 1) % 4;
      break;
    case LEFT:
      last_dir = (last_dir + 3) % 4;
      break;
    default:
      return; // Do Nothing
  }
}

void Snakes::move(int dir){
  int new_idx = (cur_snake_idx + 1)%MAX_LEN;
  pos new_p = snake_locs[cur_snake_idx].add(ADJ[dir]); // Move snake by 1 position
  // Check if we have collided with the borders (no update)
  int g_contents = g->get(new_p);
  if (g_contents == (int)ERR || g_contents == (int)SNAKE){ // Error, out-of-bounds
    state = LOSE;
    lose_init = true;
    return;
  }
  else if (g_contents == (int)FOOD){ // Grow snake!
    snake_len++;
    generate_food();
    if (snake_len == MAX_LEN){
      state = WIN;
      win_init = true;
      return;
    }
  }
  snake_locs[new_idx].update(new_p);
  cur_snake_idx = new_idx;
  has_action = true;
}

int Snakes::get(int r, int c){
  if (g == 0) return ERR;
  return g->get(r,c);
}
