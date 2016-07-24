#ifndef LCD_Low_Level_h
#define LCD_Low_Level_h

#include <Arduino.h>

/*
TODO: 
-Use direct port manipulation rather than DigitalWrite/Read: direct port manipulation will be slightly faster, and more portable to non-arduino code
-Improve naming of functions: Some functions could have better namespace
-Reorganize where functions are defined in header as well as where they're implemented in the cpp: Readability improvements
-Add ability to use/not use R/W: Read functionality may not be important, so this would be an improvement.  Some rework is required
-Add two class initializations to support using/not using R/W: See one above
-Remove _display_function: This was added as I was using the Liquad Crystal library as reference.  I may not need this as it's only used in initialization


*/

// Commands
#define LCD_ClearDisplay 0x01
#define LCD_ReturnHome 0x02
#define LCD_EntryModeSet 0x04
#define LCD_DisplayControl 0x08
#define LCD_CursorShift 0x10
#define LCD_FunctionSet 0x20
#define LCD_SetCGRAMAddress 0x40
#define LCD_SetDDRAMAddress 0x80

// Entry Mode Data
#define LCD_CursorLeft 0x00
#define LCD_CursorRight 0x01
#define LCD_DisplayLeft 0x00
#define LCD_DisplayRight 0x02

// Display Control Data
#define LCD_BlinkOff 0x00
#define LCD_BlinkOn 0x01
#define LCD_CursorOff 0x00
#define LCD_CursorOn 0x02
#define LCD_DisplayOff 0x00
#define LCD_DisplayOn 0x04

// Cursor Shift Data
#define LCD_MoveLeft 0x00
#define LCD_MoveRight 0x04
#define LCD_MoveCursor 0x00
#define LCD_MoveDisplay 0x08

// Function Set Data
#define LCD_5x8Dots 0x00
#define LCD_5x10Dots 0x04
#define LCD_1Line 0x00
#define LCD_2Line 0x08
#define LCD_4BitMode 0x00
#define LCD_8BitMode 0x10

class LCD_Low_Level {
  public:
 
    LCD_Low_Level(uint8_t, uint8_t, uint8_t,           // rs ,rw, and enable pins
          	      uint8_t, uint8_t, uint8_t, uint8_t); // d4-d7 pins (4-bit mode)
            
    LCD_Low_Level(uint8_t, uint8_t, uint8_t,           // rs, rw, and enable pins
                  uint8_t, uint8_t, uint8_t, uint8_t,  // d0-d3 pins
                  uint8_t, uint8_t, uint8_t, uint8_t); // d4-d7 pins
	
    void init(uint8_t, uint8_t, uint8_t, uint8_t,  // 4-bit mode, rs, rw, and enable pins
	          uint8_t, uint8_t, uint8_t, uint8_t,  // d0-d3
	          uint8_t, uint8_t, uint8_t, uint8_t); // d4-d7

    void begin(uint8_t columns, uint8_t rows, uint8_t charsize = LCD_5x8Dots);
    // Direct instruction functions for LCD
    void clearDisplay();
    void returnHome();
    void entrySetMode(uint8_t, uint8_t);
    void displayControl(uint8_t, uint8_t, uint8_t);
    void cursorDisplayShift(uint8_t, uint8_t);
    void functionSet(uint8_t, uint8_t, uint8_t);
    void setCGRAMAddress(uint8_t);
    void setDDRAMAddress(uint8_t);
	
    // Direct data functions for LCD
    uint8_t readAddress();
    uint8_t readBusyFlag();
    void writeDataToRAM(uint8_t);
    uint8_t readDataFromRAM();

  private: 
  
    // Eight commands, one write, and two read functions
    void command(uint8_t);
    void writeData(uint8_t);
    uint8_t readData(uint8_t);
	
    // Support functions for writing to and reading from LCD
    void writeControl(uint8_t, uint8_t);
    void sendData(uint8_t, uint8_t);
    uint8_t receive(uint8_t);
    void waitUntilNotBusy();
  
    void write4bits(uint8_t);
    void write8bits(uint8_t);
	
    uint8_t read4bits();
    uint8_t read8bits(); 

    void pulseLow();
    void pulseHigh();
    void pulseEnable();

    uint8_t _data_pins[8];
    uint8_t _rs_pin; // Low: Command.  High: Data
    uint8_t _rw_pin; // Low: Write.  High: Read
    uint8_t _enable_pin; // Pulse High for function

    uint8_t _display_function;
};

#endif
