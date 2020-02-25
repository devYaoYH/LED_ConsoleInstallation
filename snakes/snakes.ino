#include <FastLED.h>
#define NUM_LEDS 50
#define DATA_PIN 5
#define LEFT_BTN 2
#define RIGHT_BTN 3
#define REFRESH_RATE 30

int cur_idx = 0;
unsigned long btn_timeout = 100;
unsigned long left_btn_timeout = 0;
unsigned long right_btn_timeout = 0;
bool left_btn_down = false;
bool right_btn_down = false;

unsigned long screen_refresh = 0;

CRGB leds[NUM_LEDS];

typedef struct Position{
  int x, y;
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
  String str(){
    return "(" + String(x) + "," + String(y) + ")";
  }
} pos;

pos ADJ[4] = {pos(0, 1), pos(1, 0), pos(0, -1), pos(-1, 0)};

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  for (int i=0;i<NUM_LEDS;++i){
    leds[i] = CRGB::Black;
  }
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.show();
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  // DEBUG
  Serial.begin(9600);
}

void btn_pressed(int btn_pin){
  switch(btn_pin){
    case LEFT_BTN:
      cur_idx--;
      cur_idx = (cur_idx + NUM_LEDS)%NUM_LEDS;
      break;
    case RIGHT_BTN:
      cur_idx++;
      cur_idx = cur_idx%NUM_LEDS;
      break;
    default:
      return;
  }
}

void loop() {
  bool is_update = false;
  unsigned long cur_time = millis();

  if (digitalRead(LEFT_BTN) == HIGH) left_btn_down = false;
  if (digitalRead(RIGHT_BTN) == HIGH) right_btn_down = false;
  
  if (cur_time > left_btn_timeout && digitalRead(LEFT_BTN) == LOW && !left_btn_down){
    btn_pressed(LEFT_BTN);
    left_btn_timeout = cur_time + btn_timeout;
    left_btn_down = true;
    is_update = true;
  }
  
  if (cur_time > right_btn_timeout && digitalRead(RIGHT_BTN) == LOW && !right_btn_down){
    btn_pressed(RIGHT_BTN);
    right_btn_timeout = cur_time + btn_timeout;
    right_btn_down = true;
    is_update = true;
  }

  if (is_update){
    for(int i=0;i<NUM_LEDS;++i){
      leds[i] = CRGB::Black;
    }
    Serial.println(cur_idx);
    Serial.println(ADJ[cur_idx%4].str());
    leds[cur_idx] = CRGB::Green;
  }

  if (cur_time > screen_refresh){
    FastLED.show();
    screen_refresh = cur_time + REFRESH_RATE;
  }
}
