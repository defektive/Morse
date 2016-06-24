/**
 * Simple Morse Library
 * @author defektive
 */

#include "Morse.h"
#include "Arduino.h"

Morse::Morse(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
  _timeUnit = 100;
}

void Morse::emit(bool dash) {
  int timeDelay = _timeUnit;
  if (dash) {
    timeDelay = _timeUnit * 3;
  }

  digitalWrite(_pin, HIGH);
  if (_tonePin) {
    tone(_tonePin, _toneFrequency);
  }

  delay(timeDelay);

  digitalWrite(_pin, LOW);
  if (_tonePin) {
    noTone(_tonePin);
  }

  delay(_timeUnit);
}

void Morse::dot() { emit(false); }
void Morse::dash() { emit(true); }

void Morse::setupTone(int tonePin, int toneFrequency) {
  pinMode(tonePin, OUTPUT);
  _tonePin = tonePin;
  _toneFrequency = toneFrequency;
}

void Morse::setTimeUnit(int timeUnit) { _timeUnit = timeUnit; }

String textKey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
String morseKey[] = {
    ".-",    // A
    "-...",  // B
    "-.-.",  // C
    "-..",   // D
    ".",     // E
    "..-.",  // F
    "--.",   // G
    "....",  // H
    "..",    // I
    ".---",  // J
    "-.-",   // K
    ".-..",  // L
    "--",    // M
    "-.",    // N
    "---",   // O
    ".--.",  // P
    "--.-",  // Q
    ".-.",   // R
    "...",   // S
    "-",     // T
    "..-",   // U
    "...-",  // V
    ".--",   // W
    "-..-",  // X
    "-.--",  // Y
    "--..",  // Z
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----."  // 9
    "-----", // 0
};

String textToMorse(char c) {
  int index = textKey.indexOf(c);
  if (index != -1)
    return morseKey[index];
  else
    return "";
}

void Morse::emitWord(String word) {
  int len = word.length();
  int i, ci;
  for (i = 0; i < len; i++) {

    String code = textToMorse(word.charAt(i));
    int codeLen = code.length();
    for (ci = 0; ci < codeLen; ci++) {

      if (code[ci] == '.') {
        dot();
      } else {
        dash();
      }
    }

    // morse code states there should be a 3 time unit pause between
    // characters
    // 2 here and one at the end of dot/dash
    delay(_timeUnit * 2);
  }
  // morse code states there should be a 7 time unit pause between words
  // 4 here and 3 above
  delay(_timeUnit * 4);
}
