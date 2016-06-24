/*
  Morse.h - Simple Morse Library
  @author: defektive
  with help from: https://www.arduino.cc/en/Hacking/LibraryTutorial
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse {
public:
  Morse(int pin);
  void emit(bool dash);
  void dot();
  void dash();
  // void emitWord(String word);
  void emitWord(String word);
  void setupTone(int tonePin, int toneFrequency);
  void setTimeUnit(int timeUnit);

private:
  int _pin;
  int _timeUnit;
  int _tonePin;
  int _toneFrequency;
};

#endif
