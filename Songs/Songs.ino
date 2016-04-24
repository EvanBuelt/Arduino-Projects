const int BUZZER_PIN = 6;

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

Note HappyBirthday[25] = {
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

Note Tetris[59] = {
  // Measure 1
  {Frequency::e5, Duration::Quarter}, // 0
  {Frequency::b4, Duration::Eight  }, // 1
  {Frequency::c5, Duration::Eight  }, // 2
  {Frequency::d5, Duration::Quarter}, // 3
  {Frequency::c5, Duration::Eight  }, // 4
  {Frequency::b4, Duration::Eight  }, // 5
  
  // Measure 2
  {Frequency::a4, Duration::Quarter}, // 6
  {Frequency::a4, Duration::Eight  }, // 7
  {Frequency::c5, Duration::Eight  }, // 8
  {Frequency::e5, Duration::Quarter}, // 9
  {Frequency::d5, Duration::Eight  }, // 10
  {Frequency::c5, Duration::Eight  }, // 11
  
  // Measure 3
  {Frequency::b4, Duration::QuarterPlus}, // 12
  {Frequency::c5, Duration::Eight  }, // 13
  {Frequency::d5, Duration::Quarter}, // 14
  {Frequency::e5, Duration::Quarter}, // 15
  
  // Measure 4
  {Frequency::c5, Duration::Quarter}, // 16
  {Frequency::a4, Duration::Quarter}, // 17
  {Frequency::a4, Duration::Quarter}, // 18
  {Frequency::b4, Duration::Eight  }, // 19
  {Frequency::c5, Duration::Eight  }, // 20
  
  // Measure 5
  {Frequency::d5, Duration::QuarterPlus}, // 22
  {Frequency::f5, Duration::Eight  },
  {Frequency::a5, Duration::Quarter},
  {Frequency::g5, Duration::Eight  },
  {Frequency::f5, Duration::Eight  },
  
  // Measure 6
  {Frequency::e5, Duration::QuarterPlus},
  {Frequency::c5, Duration::Eight  },
  {Frequency::e5, Duration::Quarter},
  {Frequency::d5, Duration::Eight  },
  {Frequency::c5, Duration::Eight  },
  
  // Measure 7
  {Frequency::b4, Duration::Quarter},
  {Frequency::b4, Duration::Eight  },
  {Frequency::c5, Duration::Eight  },
  {Frequency::d5, Duration::Quarter},
  {Frequency::e5, Duration::Quarter},
  
  // Measure 8
  {Frequency::c5, Duration::Quarter},
  {Frequency::a4, Duration::Quarter},
  {Frequency::a4, Duration::Quarter},
  {Frequency::None, Duration::Quarter},
  
  // Measure 9
  {Frequency::e5, Duration::Half},
  {Frequency::c5, Duration::Half},
  
  // Measure 10
  {Frequency::d5, Duration::Half},
  {Frequency::b4, Duration::Half},
  
  // Measure 11
  {Frequency::c5, Duration::Half},
  {Frequency::a4, Duration::Half},
  
  // Measure 12
  {Frequency::g4_Sharp, Duration::Half},
  {Frequency::b4, Duration::Quarter},
  {Frequency::None, Duration::Quarter},
  
  // Measure 13
  {Frequency::e5, Duration::Half},
  {Frequency::c5, Duration::Half},
  
  // Measure 14
  {Frequency::d5, Duration::Half},
  {Frequency::b4, Duration::Half},
  
  // Measure 15
  {Frequency::c5, Duration::Quarter},
  {Frequency::e5, Duration::Quarter},
  {Frequency::g5, Duration::Half},
  
  // Measure 16
  {Frequency::f5_Sharp, Duration::Half},
  {Frequency::None, Duration::Half},
};

String SerialBuffer = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  int note = 0;
  int duration = 0;
  int beatsPerMinute = 1;
  /* for(int i = 0;i < 25;i++) {
    duration = (HappyBirthday[i].duration * 1000 / beatsPerMinute) * 60 / Duration::Quarter;
    playNote(HappyBirthday[i].frequency, duration);
  } */
}

void loop() {
  // put your main code here, to run repeatedly:
  int note = 0;
  long int duration = 0;
  int beatsPerMinute = 60;
  while(Serial.available() > 0) {
    SerialBuffer = Serial.readString();

    if(SerialBuffer.startsWith("Happy Birthday", 0)) {
      beatsPerMinute = 90;
      for(int i = 0;i < 25;i++) {
        duration = (HappyBirthday[i].duration * 60000 / Duration::Quarter) / beatsPerMinute);
        playNote(HappyBirthday[i].frequency, duration);
      }
    } else if(SerialBuffer.startsWith("Tetris", 0)) {
      beatsPerMinute = 144;
      for(int i = 0;i < 58;i++) {
        duration = ((Tetris[i].duration * 60000 / Duration::Quarter) / beatsPerMinute);
        playNote(Tetris[i].frequency, duration);
      }
    }
  }
}

void playNote(Frequency frequency, int duration) {
  int note = Frequency(frequency);

  if(note == 0) {
    noTone(BUZZER_PIN);
  } else {
    tone(BUZZER_PIN, note);
  }
  delay(duration * 6/10);
  noTone(BUZZER_PIN);
  delay(duration * 4/10);

  return;
}

