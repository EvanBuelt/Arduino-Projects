#include <avr/pgmspace.h>
#include <LiquidCrystal.h>

const int BUZZER_PIN = 6;

const int DB7 = 5;
const int DB6 = 4;
const int DB5 = 3;
const int DB4 = 2;

const int RS_PIN = 9;
const int ENABLE_PIN = 8;

LiquidCrystal lcd(RS_PIN, ENABLE_PIN, DB7, DB6, DB5, DB4);

enum Frequency {
  None     = 0,
  c3       = 130,
  c3_Sharp = 139,
  d3_Flat  = 139,
  d3       = 147,
  d3_Sharp = 156,
  e3_Flat  = 156,
  e3       = 165,
  f3       = 175,
  f3_Sharp = 185,
  g3_Flat  = 185,
  g3       = 196,
  g3_Sharp = 208,
  a3_Flat  = 208,
  a3       = 220,
  a3_Shart = 233,
  b3_Flat  = 233,
  b3       = 247,

  c4       = 261,
  c4_Sharp = 277,
  d4_Flat  = 277,
  d4       = 294,
  d4_Sharp = 311,
  e4_Flat  = 311,
  e4       = 330,
  f4       = 349,
  f4_Sharp = 370,
  g4_Flat  = 370,
  g4       = 392,
  g4_Sharp = 415,
  a4_Flat  = 415,
  a4       = 440,
  a4_Shart = 466,
  b4_Flat  = 466,
  b4       = 494,

  c5       = 523,
  c5_Sharp = 554,
  d5_Flat  = 554,
  d5       = 587,
  d5_Sharp = 622,
  e5_Flat  = 622,
  e5       = 659,
  f5       = 698,
  f5_Sharp = 740,
  g5_Flat  = 740,
  g5       = 784,
  g5_Sharp = 830,
  a5_Flat  = 830,
  a5       = 880,
  a5_Shart = 932,
  b5_Flat  = 932,
  b5       = 988,

  c6       = 1046,
  c6_Sharp = 1109,
  d6_Flat  = 1109,
  d6       = 1175,
  d6_Sharp = 1245,
  e6_Flat  = 1245,
  e6       = 1319,
  f6       = 1397,
  f6_Sharp = 1480,
  g6_Flat  = 1480,
  g6       = 1568,
  g6_Sharp = 1661,
  a6_Flat  = 1661,
  a        = 1760,
  a6_Shart = 1865,
  b6_Flat  = 1865,
  b6       = 1976,
};

enum Duration {
  Eight       = 2,
  EightPlus   = 3,
  Quarter     = 4,
  QuarterPlus = 6,
  Half        = 8,
  HalfPlus    = 12,
  Whole       = 16,
  WholePlus   = 24
};

struct Note {
  Frequency frequency; // Use frequency table above.
  Duration duration; // In ms
};

const Note HappyBirthday[25] PROGMEM = {
  {Frequency::d4, Duration::Eight  }, 
  {Frequency::d4, Duration::Eight  },
  {Frequency::e4, Duration::Quarter},
  {Frequency::d4, Duration::Quarter},
  {Frequency::g4, Duration::Quarter},
  {Frequency::f4, Duration::Half   },
  
  {Frequency::d4, Duration::Eight  }, 
  {Frequency::d4, Duration::Eight  },
  {Frequency::e4, Duration::Quarter},
  {Frequency::d4, Duration::Quarter},
  {Frequency::a4, Duration::Quarter},
  {Frequency::g4, Duration::Half   },

  {Frequency::d4, Duration::Eight  }, 
  {Frequency::d4, Duration::Eight  },
  {Frequency::d5, Duration::Quarter},
  {Frequency::b4, Duration::Quarter},
  {Frequency::g4, Duration::Quarter},
  {Frequency::f4, Duration::Quarter},
  {Frequency::e4, Duration::Quarter},

  {Frequency::c5, Duration::Eight  }, 
  {Frequency::c5, Duration::Eight  },
  {Frequency::b4, Duration::Quarter},
  {Frequency::g4, Duration::Quarter},
  {Frequency::a4, Duration::Quarter},
  {Frequency::g4, Duration::Quarter}
};

const Note Tetris[59] PROGMEM = {
  // Measure 1
  {Frequency::e5      , Duration::Quarter    }, // 0
  {Frequency::b4      , Duration::Eight      }, // 1
  {Frequency::c5      , Duration::Eight      }, // 2
  {Frequency::d5      , Duration::Quarter    }, // 3
  {Frequency::c5      , Duration::Eight      }, // 4
  {Frequency::b4      , Duration::Eight      }, // 5
  
  // Measure 2
  {Frequency::a4      , Duration::Quarter    }, // 6
  {Frequency::a4      , Duration::Eight      }, // 7
  {Frequency::c5      , Duration::Eight      }, // 8
  {Frequency::e5      , Duration::Quarter    }, // 9
  {Frequency::d5      , Duration::Eight      }, // 10
  {Frequency::c5      , Duration::Eight      }, // 11
  
  // Measure 3
  {Frequency::b4      , Duration::QuarterPlus}, // 12
  {Frequency::c5      , Duration::Eight      }, // 13
  {Frequency::d5      , Duration::Quarter    }, // 14
  {Frequency::e5      , Duration::Quarter    }, // 15
  
  // Measure 4
  {Frequency::c5      , Duration::Quarter    }, // 16
  {Frequency::a4      , Duration::Quarter    }, // 17
  {Frequency::a4      , Duration::Quarter    }, // 18
  {Frequency::b4      , Duration::Eight      }, // 19
  {Frequency::c5      , Duration::Eight      }, // 20
  
  // Measure 5
  {Frequency::d5      , Duration::QuarterPlus}, // 22
  {Frequency::f5      , Duration::Eight      }, // 23
  {Frequency::a5      , Duration::Quarter    }, // 24
  {Frequency::g5      , Duration::Eight      }, // 25
  {Frequency::f5      , Duration::Eight      }, // 26
  
  // Measure 6
  {Frequency::e5      , Duration::QuarterPlus}, // 27
  {Frequency::c5      , Duration::Eight      }, // 28
  {Frequency::e5      , Duration::Quarter    }, // 29
  {Frequency::d5      , Duration::Eight      }, // 30
  {Frequency::c5      , Duration::Eight      }, // 31
  
  // Measure 7
  {Frequency::b4      , Duration::Quarter    }, // 32
  {Frequency::b4      , Duration::Eight      }, // 33
  {Frequency::c5      , Duration::Eight      }, // 34
  {Frequency::d5      , Duration::Quarter    }, // 35
  {Frequency::e5      , Duration::Quarter    }, // 36
  
  // Measure 8
  {Frequency::c5      , Duration::Quarter    }, // 37
  {Frequency::a4      , Duration::Quarter    }, // 38
  {Frequency::a4      , Duration::Quarter    }, // 39
  {Frequency::None    , Duration::Quarter    }, // 40
  
  // Measure 9
  {Frequency::e5      , Duration::Half       }, // 41
  {Frequency::c5      , Duration::Half       }, // 42
  
  // Measure 10
  {Frequency::d5      , Duration::Half       }, // 43
  {Frequency::b4      , Duration::Half       }, // 44
  
  // Measure 11
  {Frequency::c5      , Duration::Half       }, // 45
  {Frequency::a4      , Duration::Half       }, // 46
  
  // Measure 12
  {Frequency::g4_Sharp, Duration::Half       }, // 47
  {Frequency::b4      , Duration::Quarter    }, // 48
  {Frequency::None    , Duration::Quarter    }, // 49
  
  // Measure 13
  {Frequency::e5      , Duration::Half       }, // 50
  {Frequency::c5      , Duration::Half       }, // 51
  
  // Measure 14
  {Frequency::d5      , Duration::Half       }, // 52
  {Frequency::b4      , Duration::Half       }, // 53
  
  // Measure 15
  {Frequency::c5      , Duration::Quarter    }, // 54
  {Frequency::e5      , Duration::Quarter    }, // 55
  {Frequency::g5      , Duration::Half       }, // 56
  
  // Measure 16
  {Frequency::f5_Sharp, Duration::Half       }, // 57
  {Frequency::None    , Duration::Half       }, // 58
};

const Note Mario[] PROGMEM = {
  // Measure 1
  {Frequency::e5      , Duration::Eight      },
  {Frequency::e5      , Duration::Eight      },
  {Frequency::None    , Duration::Eight      },
  {Frequency::e5      , Duration::Eight      },
  {Frequency::None    , Duration::Eight      },
  {Frequency::c5      , Duration::Eight      },
  {Frequency::e5      , Duration::Quarter    },

  // Measure 2
  {Frequency::g5      , Duration::Quarter    },
  {Frequency::None    , Duration::Quarter    },
  {Frequency::g4      , Duration::Quarter    },
  {Frequency::None    , Duration::Quarter    },

  // Measure 3
  {Frequency::c5      , Duration::QuarterPlus},
  {Frequency::g4      , Duration::Eight      },
  {Frequency::None    , Duration::Quarter    },
  {Frequency::e4      , Duration::QuarterPlus},

  // Measure 4
  {Frequency::a4      , Duration::Quarter    },
  {Frequency::b4      , Duration::Eight      },
  {Frequency::b4      , Duration::Eight      },
  {Frequency::b4_Flat , Duration::Eight      },
  {Frequency::a4      , Duration::Quarter    },

  // Measure 5
  {Frequency::g4      , Duration::Quarter    },
  {Frequency::e5      , Duration::Quarter    },
  {Frequency::g5      , Duration::Quarter    },
  {Frequency::a5      , Duration::Quarter    },
  {Frequency::f5      , Duration::Eight      },
  {Frequency::g5      , Duration::Eight      },
  
  // Measure 6
  {Frequency::None    , Duration::Quarter    },
  {Frequency::e5      , Duration::Quarter    },
  {Frequency::c5      , Duration::Eight      },
  {Frequency::d5      , Duration::Eight      },
  {Frequency::b4      , Duration::Quarter    },
  {Frequency::None    , Duration::Eight      },
  
  // Measure 7
  {Frequency::c5      , Duration::QuarterPlus},
  {Frequency::g4      , Duration::Eight      },
  {Frequency::None    , Duration::Quarter    },
  {Frequency::e4      , Duration::QuarterPlus},
  
  // Measure 8
  {Frequency::a4      , Duration::Quarter    },
  {Frequency::b4      , Duration::Quarter    },
  {Frequency::b4_Flat , Duration::Eight      },
  {Frequency::a4      , Duration::Quarter    },
  
  // Measure 9
  {Frequency::g4      , Duration::Quarter    },
  {Frequency::e5      , Duration::Quarter    },
  {Frequency::g5      , Duration::Quarter    },
  {Frequency::a5      , Duration::Quarter    },
  {Frequency::f5      , Duration::Eight      },
  {Frequency::g5      , Duration::Eight      },
  
  // Measure 10
  {Frequency::None    , Duration::Eight      },
  {Frequency::e5      , Duration::Quarter    },
  {Frequency::c5      , Duration::Eight      },
  {Frequency::d5      , Duration::Eight      },
  {Frequency::b5      , Duration::Quarter    },
  {Frequency::None    , Duration::Eight      },
  
  // Measure 11
  {Frequency::None    , Duration::Quarter    },
  {Frequency::g5      , Duration::Eight      },
  {Frequency::g5_Flat , Duration::Eight      },
  {Frequency::f5      , Duration::Eight      },
  {Frequency::d5_Sharp, Duration::Quarter    },
  {Frequency::e5      , Duration::Eight      },
  
  // Measure 12
  {Frequency::None    , Duration::Eight      },
  {Frequency::g4_Sharp, Duration::Eight      },
  {Frequency::a4      , Duration::Eight      },
  {Frequency::c5      , Duration::Eight      },
  {Frequency::None    , Duration::Eight      },
  {Frequency::a4      , Duration::Eight      },
  {Frequency::c5      , Duration::Eight      },
  {Frequency::d5      , Duration::Eight      },
  
  // Measure 13
  {Frequency::None    , Duration::Quarter    },
  {Frequency::g5      , Duration::Eight      },
  {Frequency::g5_Flat , Duration::Eight      },
  {Frequency::f5      , Duration::Eight      },
  {Frequency::d5_Sharp, Duration::Quarter    },
  {Frequency::e5      , Duration::Eight      },
  
  // Measure 14
  {Frequency::None    , Duration::Eight      },
  {Frequency::c6      , Duration::Eight      },
  {Frequency::None    , Duration::Eight      },
  {Frequency::c6      , Duration::Eight      },
  {Frequency::c6      , Duration::Half       },
  
  // Measure 15
  {Frequency::None    , Duration::Quarter    },
  {Frequency::g5      , Duration::Eight      },
  {Frequency::g5_Flat , Duration::Eight      },
  {Frequency::f5      , Duration::Eight      },
  {Frequency::d5_Sharp, Duration::Quarter    },
  {Frequency::e5      , Duration::Eight      },
  
  // Measure 16
  {Frequency::None    , Duration::Eight      },
  {Frequency::g4_Sharp, Duration::Eight      },
  {Frequency::a4      , Duration::Eight      },
  {Frequency::c5      , Duration::Eight      },
  {Frequency::None    , Duration::Eight      },
  {Frequency::a4      , Duration::Eight      },
  {Frequency::c5      , Duration::Eight      },
  {Frequency::d5      , Duration::Eight      },
};

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
        playNote(note, 90, 80);
      }
    } else if(SerialBuffer.startsWith("Tetris", 0)) {
      lcd.clear();
      lcd.print("Tetris Theme");
      for(int i = 0;i < ArraySize(Tetris);i++) {
        Note note;
        PROGMEM_readAnything(&Tetris[i], note);
        playNote(note, 144, 80);
      }
    } else if(SerialBuffer.startsWith("Mario", 0)) {
      lcd.clear();
      lcd.print("Mario Theme");
      for(int i = 0;i < ArraySize(Mario);i++) {
        Note note;
        PROGMEM_readAnything(&Mario[i], note);
        playNote(note, 130, 80);
      }
    }
  }
}

void playNote(Note note, int beatsPerMinute, int onTime) {

  long int duration = (note.duration * 60000 / Duration::Quarter) / beatsPerMinute;
  int frequency = Frequency(note.frequency);

  if(frequency == 0) {
    noTone(BUZZER_PIN);
  } else {
    tone(BUZZER_PIN, frequency);
  }
  delay((duration / 100) * onTime);
  noTone(BUZZER_PIN);
  delay((duration / 100) * (100 - onTime));

  return;
}

