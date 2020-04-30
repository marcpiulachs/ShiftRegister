#include <ShiftRegister.h>

// Constructor
ShiftRegister::ShiftRegister(int SER_Pin, int RCLK_Pin, int SRCLK_Pin,
		int CLEAR_Pin, int OE_Pin, int registers)
{
	// The Pins
	_SER_Pin = SER_Pin;
	_RCLK_Pin = RCLK_Pin;
	_SRCLK_Pin = SRCLK_Pin;
	_OE_Pin = OE_Pin;
	_CLEAR_Pin = CLEAR_Pin;

	// The total number of registers
	_registers = registers;

	// Set all pins to OUTPUTs
	pinMode(_SER_Pin, OUTPUT);
	pinMode(_RCLK_Pin, OUTPUT);
	pinMode(_SRCLK_Pin, OUTPUT);
	pinMode(_OE_Pin, OUTPUT);
	pinMode(_CLEAR_Pin, OUTPUT);

	clear(); //reset all register pins
	write(); //send the new state to the shift register
}

/*
 * Gets the total number of registers.
 */
int ShiftRegister::getRegisters()
{
	return (8 * _registers);
}

/*
 * Writes current state to the shift registers.
 *
 * Set and display registers
 * Only call AFTER all values are set how you would like (slow otherwise)
 *
 */
void ShiftRegister::write()
{
	// Enable the ShiftRegister
	enable();

	// Disable the clear shift register
	digitalWrite(_CLEAR_Pin, HIGH);

	// Get everything setup and nothing on the shift register pins will change.
	digitalWrite(_RCLK_Pin, LOW);

	//iterate through the registers
	for (int i = _registers - 1; i >= 0; i--)
	{
		//iterate through the bits in each registers
		for (int j = 8 - 1; j >= 0; j--)
		{
			digitalWrite(_SRCLK_Pin, LOW);

			int val = _shiftRegisters[i] & (1 << j);

			digitalWrite(_SER_Pin, val);
			digitalWrite(_SRCLK_Pin, HIGH);
		}
	}

	// We are done, set pins on shift register as per the new settings.
	digitalWrite(_RCLK_Pin, HIGH);

	// Flag that the shift register has been updated.
	_updateNeeded = false;
}

void ShiftRegister::setPin(int index, boolean val)
{
	int byteIndex = index / 8;
	int bitIndex = index % 8;

	byte current = _shiftRegisters[byteIndex];

	current &= ~(1 << bitIndex); //clear the bit
	current |= val << bitIndex; //set the bit

	// Set the value
	_shiftRegisters[byteIndex] = current;

	// Something has hanged flag the shift register as dirty.
	_updateNeeded = true;
}

void ShiftRegister::setAll(boolean val)
{
	//set all register pins to LOW
	for (int i = getRegisters() - 1; i >= 0; i--)
	{
		setPin(i, val);
	}
}

void ShiftRegister::clear()
{
	//set all register pins to LOW
	for (int i = getRegisters() - 1; i >= 0; i--)
	{
		setPin(i, LOW);
	}
}

/*
 *
 */
void ShiftRegister::enable()
{
	digitalWrite(_OE_Pin, LOW);
}

/*
 *
 */
void ShiftRegister::disable()
{
	digitalWrite(_OE_Pin, HIGH);
}

/*
 *
 */
void ShiftRegister::reset()
{
	digitalWrite(_CLEAR_Pin, LOW);
}

/*
 *
 */
bool ShiftRegister::isUpdateNeeded()
{
	return _updateNeeded;
}
