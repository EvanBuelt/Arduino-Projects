#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include "Song.h"
#include "HappyBirthday.h"
#include "Tetris.h"
#include "Mario.h"

const int BUZZER_PIN = 6;

const int DB7 = 5;
const int DB6 = 4;
const int DB5 = 3;
const int DB4 = 2;

const int RS_PIN = 9;
const int ENABLE_PIN = 8;

LiquidCrystal lcd(RS_PIN, ENABLE_PIN, DB7, DB6, DB5, DB4);

String SerialBuffer = "";

template <typename T> void PROGMEM_readAnything (const T * sce, T& dest) {
  memcpy_P (&dest, sce, sizeof (T));
}

template <typename T> T PROGMEM_getAnything (const T * sce) {
  static T temp;
  memcpy_P (&temp, sce, sizeof (T));
  return temp;
}

// number of items in an array
template< typename T, size_t N > size_t ArraySize (T (&) [N]){ return N; }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  
  while(Serial.available() > 0) {
    SerialBuffer = Serial.readString();

    if(SerialBuffer.startsWith("Happy Birthday", 0)) {
      lcd.clear();
      lcd.print("Happy Birthday");
      for(int i = 0;i < ArraySize(HappyBirthday);i++) {
        Note note;
        PROGMEM_readAnything(&HappyBirthday[i], note);
        playNote(BUZZER_PIN, note, 90, 80);
      }
    } else if(SerialBuffer.startsWith("Tetris", 0)) {
      lcd.clear();
      lcd.print("Tetris Theme");
      for(int i = 0;i < ArraySize(Tetris);i++) {
        Note note;
        PROGMEM_readAnything(&Tetris[i], note);
        playNote(BUZZER_PIN, note, 144, 80);
      }
    } else if(SerialBuffer.startsWith("Mario", 0)) {
      lcd.clear();
      lcd.print("Mario Theme");
      for(int i = 0;i < ArraySize(Mario);i++) {
        Note note;
        PROGMEM_readAnything(&Mario[i], note);
        playNote(BUZZER_PIN, note, 130, 80);
      }
    }
  }
}

