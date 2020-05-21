
#ifndef Hexapod_Servo_h
#define Hexapod_Servo_h
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
class Hexapod_Servo{
public:
	Hexapod_Servo(int ID[], int upperLimit[], int lowerLimit[], int lastStatus[], boolean isReversed[], int part[]);
	boolean isInRange(int index, int pos);
	Hexapod_Servo();
	int getStatus(int index);
	void setStatus(int index, int pos);
	int getID(int index);
	boolean isReversed(int index);
	int getPart(int index);
	int processPosition(int index, int pos);
	void setEverything(int _ID[], int _upperLimit[], int _lowerLimit[], int _lastStatus[], boolean _isReversed[], int _part[]);
private:
	int ID[18];
	int upperLimit[18];
	int lowerLimit[18];
	int lastStatus[18];
	boolean isReverse[18];
	int part[18];
};
#endif
