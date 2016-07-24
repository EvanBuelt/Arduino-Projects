#include "LCD_develop.h"
#include "Arduino.h"

LCD_Low_Level::LCD_Low_Level(uint8_t rs_pin, uint8_t rw_pin, uint8_t enable_pin, 
                             uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {

  init(1, rs_pin, rw_pin, enable_pin, 0, 0, 0, 0, d4, d5, d6, d7);
}

LCD_Low_Level::LCD_Low_Level(uint8_t rs_pin, uint8_t rw_pin, uint8_t enable_pin, 
                             uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                             uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {

  init(0, rs_pin, rw_pin, enable_pin, d0, d1, d2, d3, d4, d5, d6, d7);
}

void LCD_Low_Level::init(uint8_t fourbitmode, uint8_t rs_pin, uint8_t rw_pin, uint8_t enable_pin, 
                         uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, 
                         uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {

  _rs_pin = rs_pin;
  _rw_pin = rw_pin;
  _enable_pin = enable_pin;

  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3;
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7;

  if (fourbitmode) {
    _display_function = LCD_4BitMode | LCD_1Line | LCD_5x8Dots;
  } else {
    _display_function = LCD_8BitMode | LCD_1Line | LCD_5x8Dots;
  }

  begin(16, 1);
}

void LCD_Low_Level::begin(uint8_t columns, uint8_t rows, uint8_t dotsize) {
  if (rows > 1) {
    _display_function |= LCD_2Line;
  }

  if ((dotsize != LCD_5x8Dots) && (rows == 1)) {
    _display_function |= LCD_5x10Dots;
  }

  pinMode(_rs_pin, OUTPUT);
  pinMode(_rw_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);

  // According to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands.  Wait 50ms to be safe.
  delayMicroseconds(50000);

  // Pull RS and RW low to begin sending commands
  digitalWrite(_rs_pin, LOW);
  digitalWrite(_rw_pin, LOW);

  // Put the LCD into 4 bit or 8 bit mode
  if (! (_display_function & LCD_8BitMode)) {

    // LCD starts in 8-bit mode.  Try to set 4 bit mode
    write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1 ms

    // Second try
    write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1 ms

    // Third try
    write4bits(0x03);
    delayMicroseconds(150);

    // Fourth try will set the LCD to 4-bit interface
    write4bits(0x02);
  } else {

    // Send function set command sequence
    command(LCD_FunctionSet | _display_function);
    delayMicroseconds(4500); // wait more than 4.1 ms

    // Second try
    command(LCD_FunctionSet | _display_function);
    delayMicroseconds(150);

    // Third try
    command(LCD_FunctionSet | _display_function);
  }

  // Set # lines, font size, etc
  command(LCD_FunctionSet | _display_function);

  // turn the display on with no cursor or blinking default
  displayControl(LCD_DisplayOn, LCD_CursorOff, LCD_BlinkOn);

  // Clear the display
  clearDisplay();

  // Initialize default text direction for romance language
  entrySetMode(LCD_CursorRight, LCD_DisplayLeft);
  
}

// Direct instruction functions for LCD
void LCD_Low_Level::clearDisplay() {
  
	waitUntilNotBusy();
 
	command(LCD_ClearDisplay);
	// delayMicroseconds(2000); // Must wait 1.53ms, so waiting 2ms to be safe.
}

void LCD_Low_Level::returnHome() {
  
	waitUntilNotBusy();
 
	command(LCD_ReturnHome);
	// delayMicroseconds(2000); // Must wait 1.53ms, so waiting 2ms to be safe.
	
}

void LCD_Low_Level::entrySetMode(uint8_t direction, uint8_t shift_enable) {

  waitUntilNotBusy();
  
	uint8_t data = LCD_EntryModeSet;
	if (direction) {
		data |= LCD_DisplayRight;
	}
	if (shift_enable) {
		data |= LCD_CursorRight;
	}
	
	command(data);
	// delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe.
}

void LCD_Low_Level::displayControl(uint8_t display_on, uint8_t cursor_on, uint8_t blinking_on) {

  waitUntilNotBusy();
  
	uint8_t data = LCD_DisplayControl;
	if (display_on) {
		data |= LCD_DisplayOn;
	}
	if (cursor_on) {
		data |= LCD_CursorOn;
	}
	if (blinking_on) {
		data |= LCD_BlinkOn;
	}
	command(data);
	
	// delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

void LCD_Low_Level::cursorDisplayShift(uint8_t screen_shift, uint8_t direction) {
  
	waitUntilNotBusy();
 
	uint8_t data = LCD_CursorShift;
	if (screen_shift) {
		data |= LCD_MoveDisplay;
	}
	if (direction) {
		data |= LCD_MoveRight;
	}
	command(data);
	
	// delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

void LCD_Low_Level::functionSet(uint8_t data_length, uint8_t number_lines, uint8_t display_font) {
  
	waitUntilNotBusy();
 
	uint8_t data = LCD_FunctionSet;
	if (data_length) {
		data |= LCD_8BitMode;
	}
	if (number_lines) {
		data |= LCD_2Line;
	}
	if (display_font) {
		data |= LCD_5x10Dots;
	}
	command(data);
	
	// delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

void LCD_Low_Level::setCGRAMAddress(uint8_t CGRAM_address) {

  waitUntilNotBusy();
  
	uint8_t data = LCD_SetCGRAMAddress | (CGRAM_address & 0x3F);
	command(data);
	
	// delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

void LCD_Low_Level::setDDRAMAddress(uint8_t DDRAM_address) {

  waitUntilNotBusy();
  
	uint8_t data = LCD_SetDDRAMAddress | (DDRAM_address & 0x7F);
	command(data);
	
	// delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
}

// Direct data functions for LCD
uint8_t LCD_Low_Level::readAddress(void) {
	
	uint8_t data =  readData(0);
	
	data = (data & 0x7F);
	return data;
}

uint8_t LCD_Low_Level::readBusyFlag(void) {
	
	return (readData(0) >> 7) & 0x01;
}

void LCD_Low_Level::writeDataToRAM(uint8_t data) {

  waitUntilNotBusy();
  
	writeData(data);
	
	// delayMicroseconds(100); // Must wait 43us, so waiting 100us to be safe
}

uint8_t LCD_Low_Level::readDataFromRAM(void) {

  waitUntilNotBusy();
  
	uint8_t data = 0;
	data = readData(1);
	
	// delayMicroseconds(100); // Must wait 39us, so waiting 100us to be safe
	
	return data;
}

inline void LCD_Low_Level::writeControl(uint8_t rs_data, uint8_t rw_data) {
  
	digitalWrite(_rs_pin, rs_data);
	digitalWrite(_rw_pin, rw_data);
	delayMicroseconds(1);
}

void LCD_Low_Level::command(uint8_t data) {
	
	sendData(data, 0);
}

void LCD_Low_Level::writeData(uint8_t data) {
	
	sendData(data, 1);
}

uint8_t LCD_Low_Level::readData(uint8_t rs_bit) {
	
	return receive(rs_bit);
}

void LCD_Low_Level::sendData(uint8_t value, uint8_t rs_bit) {
  
	writeControl(rs_bit, 0);
	
	if (_display_function & LCD_8BitMode) {
		write8bits(value);
	} else {
		write4bits((value & 0xF0)>>4);
		write4bits(value & 0x0F);
	}
}

uint8_t LCD_Low_Level::receive(uint8_t rs_bit) {
	
	writeControl(rs_bit, 1);
	
	int data = 0;
	
	if (_display_function & LCD_8BitMode) {
		data = read8bits();
	} else {
		data = (read4bits() & 0x0F) << 4;
		data = data | (read4bits() & 0x0F);
	}
	return data;
}

inline void LCD_Low_Level::waitUntilNotBusy() {
  while(readBusyFlag()) {
    delayMicroseconds(4);
  }
}

inline uint8_t LCD_Low_Level::read4bits() {
	uint8_t data = 0;

  for (uint8_t i = 0; i < 4; i++) {
    pinMode(_data_pins[4 + i], INPUT);
  }
  
  pulseHigh();

  for (uint8_t i = 0; i < 4; i++) {
    data |= (digitalRead(_data_pins[4 + i]) & 0x01) << i;
  }

  pulseLow();
  
  return data;
}

inline uint8_t LCD_Low_Level::read8bits() {
	int data = 0;

	for (uint8_t i = 0; i < 8; i++) {
    pinMode(_data_pins[i], INPUT);
  }

  pulseHigh();

  for (uint8_t i = 0; i < 8; i++) {
    data |= (digitalRead(_data_pins[i]) & 0x01) << i;
  }

  pulseLow();
  
	return data;
}

inline void LCD_Low_Level::write4bits(uint8_t data) {

  for (uint8_t i = 0; i < 4; i++) {
    pinMode(_data_pins[4 + i], OUTPUT);
    digitalWrite(_data_pins[4 + i], (data >> i) & 0x01);
  }
  
	pulseEnable();
}
inline void LCD_Low_Level::write8bits(uint8_t data) {

  for (uint8_t i = 0; i < 8; i++) {
    pinMode(_data_pins[i], OUTPUT);
    digitalWrite(_data_pins[i], (data >> i) & 0x01);
  }
	
	pulseEnable();
}

inline void LCD_Low_Level::pulseLow() {
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(1);
}

inline void LCD_Low_Level::pulseHigh() {
  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(1);
}

void LCD_Low_Level::pulseEnable() {
	pulseHigh();
	pulseLow();
}
