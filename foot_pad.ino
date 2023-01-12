#include <Mouse.h>

// pins for each button
const int FRONT = 5, BACK = 3, LEFT = 2, RIGHT = 4;

void setup() {
  // Initialize the mouse control
  Mouse.begin();
  Serial.begin(9600);
  for (int i=2; i<6; ++i) {
    pinMode(i, INPUT_PULLUP);
  }
}

void scroll_up(int clicks) {
  Mouse.move(0,0,clicks);
}

void scroll_down(int clicks) {
  Mouse.move(0,0,-clicks);
}

bool is_pressed(int button_pin) {
  return digitalRead(button_pin) == LOW;
}

// MOUSE MODE

// read release 10 times before doing it
bool left_down = false, right_down = false;
const int CLICK_COOLDOWN = 10;
int left_cooldown = CLICK_COOLDOWN, right_cooldown = CLICK_COOLDOWN;

// only scroll every Mth time the scroll is read
const int MODULUS = 4000;
int up_counter = 0, down_counter = 0;

void loop() {

  // RIGHT CLICK
  if (is_pressed(FRONT)) {
    right_cooldown = CLICK_COOLDOWN;
    if (!right_down) {
      right_down = true;
      Mouse.press(MOUSE_RIGHT);
    }
  }
  else {
    if (right_cooldown == 1) {
      Mouse.release(MOUSE_RIGHT);
      right_down = false;
    }
    if (right_cooldown > 0)
      right_cooldown--;
  }

  // LEFT CLICK
  if (is_pressed(BACK)) {
    left_cooldown = CLICK_COOLDOWN;
    if (!left_down) {
      left_down = true;
      Mouse.press(MOUSE_LEFT);
    }
  }
  else {
    if (left_cooldown == 1) {
      Mouse.release(MOUSE_LEFT);
      left_down = false;
    }
    if (left_cooldown > 0)
      left_cooldown--;
  }  

  // SCROLL DOWN
  if (is_pressed(RIGHT)) {
    if (down_counter % MODULUS == 0)
      scroll_down(1);
    down_counter++;
  }
  else {
    down_counter = MODULUS/2;
  }

  // SCROLL UP
  if (is_pressed(LEFT)) {
    if (up_counter % MODULUS == 0)
      scroll_up(1);
    up_counter++;
  }
  else {
    up_counter = MODULUS/2;
  }



}
