#pragma once
#include <WString.h>
#include <math.h>
struct Position{
  int x, y;
  Position():x(0),y(0){}
  Position(int ix, int iy): x(ix), y(iy){}
  Position add(Position &o){
    return Position(x + o.x, y + o.y);
  }
  Position sub(Position &o){
    return Position(x - o.x, y - o.y);
  }
  Position mult(int c){
    return Position(c*x, c*y);
  }
  void update(int ix, int iy){
    x = ix; y = iy;
  }
  void update(Position &p){
    x = p.x; y = p.y;
  }
  int dist(Position &p){
    return abs(x-p.x) + abs(y-p.y);
  }
  String str(){
    return "(" + String(x) + "," + String(y) + ")";
  }
};
