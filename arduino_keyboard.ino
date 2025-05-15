#include "Keyboard.h"

typedef struct {
  int pin;
  bool state;
  char letter;
  unsigned long last_press;
} button_t;

#define MAX_BUTTONS 11
#define FIRST_PIN 2
#define MINIMUM_PRESS_MS 5

button_t buttons[MAX_BUTTONS];

void setup() {
  for (int i = 0; i < MAX_BUTTONS; i += 1) {
    buttons[i] = {
      .pin = i + FIRST_PIN,
      .state = false,
      .letter = 'a' + i,
      .last_press = 0
    };
    pinMode(i + FIRST_PIN, INPUT_PULLUP);
  }
  Keyboard.begin();
}

void loop() {
  unsigned long time = millis();

  for (int i = 0; i < MAX_BUTTONS; i += 1) {
    if (
      digitalRead(buttons[i].pin) == LOW
      && !buttons[i].state
      && (time - buttons[i].last_press) > MINIMUM_PRESS_MS
    ) {
      Keyboard.press(buttons[i].letter);
      buttons[i].state = true;
      buttons[i].last_press = time;
    }
    if (
      digitalRead(buttons[i].pin) == HIGH
      && buttons[i].state
      && (time - buttons[i].last_press) > MINIMUM_PRESS_MS
    ) {
      Keyboard.release(buttons[i].letter);
      buttons[i].state = false;
      buttons[i].last_press = time;
    }
  }
}
