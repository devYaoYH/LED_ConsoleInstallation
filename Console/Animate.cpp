#include "Animate.h"
typedef Position pos;
Animate_Spectrum::Animate_Spectrum(int d, Grid* ig):Game(d),g(ig){
  turn_delay = 50;  // Change to a fine-grained timestep
  // Setup initial stripes
  for (int r=0;r<dims;++r){
    for (int c=0;c<dims;++c){
      CHSV* cell = g->get_col(r,c);
      if (cell != 0){
        cell->setHSV(HUE_OFFSET*c,255,120);
      }
    }
  }
}

Animate_Spectrum::~Animate_Spectrum(){}

void Animate_Spectrum::draw_led(CHSV* led, int val){
  // Don't need to do anything, just define
}

void Animate_Spectrum::increment_hue(){
  // Compute breathing pattern
  int intensity = (exp(sin((float)time_counter/2000)) - 0.367879)*50 + 50;
  // Propagate changes
  for (int r=0;r<dims;++r){
    for (int c=0;c<dims;++c){
      // Overflow is wrapped around?
      CHSV* cell = g->get_col(r,c);
      if (cell != 0){ // Something is very wrong otherwise
        cell->setHSV(cell->h+HUE_GAIN,255,intensity);
      }
    }
  }
}

bool Animate_Spectrum::turn(){
  switch(state){
    case HORIZONTAL:
      if (time_counter > mode_timeout){
        // Progress to VERTICAL mode
        g->clear();
        for (int r=0;r<dims;++r){
          for (int c=0;c<dims;++c){
            CHSV* cell = g->get_col(r,c);
            if (cell != 0){
              cell->setHSV(HUE_OFFSET*r,255,120);
            }
          }
        }
        state = VERTICAL;
        mode_timeout = time_counter + mode_delay;
      }
      else if (time_counter > turn_timeout){
        turn_timeout = time_counter + turn_delay;
        increment_hue();
        return true;
      }
      break;
    case VERTICAL:
      if (time_counter > mode_timeout){
        // Progress to VERTICAL mode
        g->clear();
        for (int r=0;r<dims;++r){
          for (int c=0;c<dims;++c){
            CHSV* cell = g->get_col(r,c);
            if (cell != 0){
              cell->setHSV(HUE_OFFSET*c,255,120);
            }
          }
        }
        state = HORIZONTAL;
        mode_timeout = time_counter + mode_delay;
      }
      else if (time_counter > turn_timeout){
        turn_timeout = time_counter + turn_delay;
        increment_hue();
        return true;
      }
      break;
    default:
      break;
  }
  return false;
}

bool Animate_Spectrum::play(unsigned long cur_time){
  // Update time counter
  time_counter = cur_time;
  // Start making colors!
  return turn();
}

void Animate_Spectrum::action(int act_id){
  // No actions are taken for this game
}
