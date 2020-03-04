// Properly defines the hardware
// button configurations
#define DOWN 8
#define UP 9
#define LEFT 11
#define RIGHT 10
class Game{
  protected:
    bool has_action = false;
    unsigned long lose_delay = 2000;
    unsigned long win_delay = 2000;
    unsigned long turn_delay = 500;
    unsigned long time_counter = 0;
    unsigned long win_timeout = 0;
    unsigned long lose_timeout = 0;
    unsigned long turn_timeout = 0;
    bool win_init = true;
    bool lose_init = true;
  public:
    virtual bool play() = 0;
    virtual bool play(unsigned long) = 0;
    virtual void action(int) = 0;
};
