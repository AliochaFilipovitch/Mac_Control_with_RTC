/*
  Mac Control with a RTC Module

  For the Arduino Leonardo and Micro.

  Open&Close mac session, sends a text string when it's the time on TextEdit

  The circuit:
  i2C

  created 8 Feb 2018
  by Aliocha Filipovitch

  https://github.com/AliochaFilipovitch/Computer-control-Arduino-project
*/
#include <Wire.h>
#include <ds3231.h>
#include "Keyboard.h"
#include "Mouse.h"
#include "MouseTo.h"

struct ts t;
const int hourControl = 14;
const int minControlFirst = 0;
const int secControl = 0;

void setup() {
  // initialize time:
  Wire.begin();
  DS3231_init(DS3231_INTCN);
  // initialize control over the keyboard and mouse:
  Keyboard.begin();
  Mouse.begin();
  MouseTo.setCorrectionFactor(1);
}

void loop() {
  DS3231_get(&t);
  if ((t.hour == hourControl)
      && (t.min == minControlFirst)
      && (t.sec == secControl)) {
    // -----1 OPEN SESSION-----
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.releaseAll();
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    // Your password :
    Keyboard.print("Hello");
    delay(1000);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(10000);
    // -------------------------
    // -----2 OPEN TextEdit-----
    // CMD-SHIFT-a
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('q');
    delay(1000);
    Keyboard.releaseAll();
    for (int x = 0; x < 42; x ++) { // 42nd position in my repository
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.releaseAll();
    }
    delay(1000);
    Keyboard.write(32); //SPACE
    Keyboard.releaseAll();
    delay(1000);
    MouseTo.setTarget(2020, 500); // (x,y) = (gauche->droite ; haut->bas)
    while (MouseTo.move() == false) {}
    delay(5000);
    Mouse.click(MOUSE_LEFT);
    delay(2000);
    // --------------------------
    // -------3 WRITE on TE------
    Keyboard.println("Hello");
    delay(1000);
    // CMD-q : CLOSE APP
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('a');
    delay(1000); // 1s
    Keyboard.releaseAll();
    // CMD-s : SAVE TEXT
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('s');
    delay(1000);
    Keyboard.releaseAll();
    // --------------------------
    // ------4 CLOSE SESSION-----
    // CMD-SHIFT-q
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('a');
    delay(1000);
    Keyboard.releaseAll();
    Keyboard.write(KEY_RETURN);
    // -----------------
  }

  delay(1000); //1s
}
