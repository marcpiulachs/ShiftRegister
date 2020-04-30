#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

// Include the standard types
#include <Arduino.h>

#define MAX_REGISTER_SIZE 32

// Define the Shifter class
class ShiftRegister
{
  public:
    // Constructor
    ShiftRegister(int SER_Pin, int RCLK_Pin, int SRCLK_Pin, int CLEAR_Pin, int OE_Pin, int registers);
   	void write();
   	void setPin(int index, boolean val);
   	void setAll(boolean val);
   	void clear();
	void enable();
	void disable();
	void reset();
    bool isUpdateNeeded();
    int getRegisters();
  private:
	int _SER_Pin;
  	int _RCLK_Pin;
  	int _SRCLK_Pin;
	int _OE_Pin;
	int _CLEAR_Pin;
  	int _registers;
  	byte _shiftRegisters[MAX_REGISTER_SIZE];
    bool _updateNeeded;
};

#endif //SHIFTREGISTER_H
