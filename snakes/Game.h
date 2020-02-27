class Game{
  protected:
    bool has_action = false;
  public:
    Game(){}
    virtual bool play() = 0;
    virtual void action(int) = 0;
    virtual int get(int,int) = 0;
};
