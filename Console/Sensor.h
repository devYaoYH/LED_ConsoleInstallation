struct Sensor{
  int PIN;
  unsigned long timeout;
  boolean state;
  Sensor(): PIN(3), timeout(0), state(false)
  {}
  Sensor(int pin): PIN(pin), timeout(0), state(false)
  {}
  void update_pin(int p){
    PIN = p;
  }
};
