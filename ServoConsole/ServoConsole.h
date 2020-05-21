
#ifndef ServoConsole_h
#define ServoConsole_h
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
#include "CDS5500_2Serials.h"
#include "Hexapod_Servo.h"
class ServoConsole{
	public:	
	      ServoConsole();
		void Move(int IDArray[], int size, int pos, int vel);
	void MoveUp(int IDArray[], int size, int incrPos, int vel);
	void MoveDown(int IDArray[], int size, int decrPos, int vel);
	private:
	CDS5500_2Serials hostServo;
	Hexapod_Servo allServos;
};
#endif



//	Hexapod_Servo servo0(0, false, 0, 361, 641);
//	Hexapod_Servo servo1(1, false, 1, 161, 861);
//	Hexapod_Servo servo2(2, true, 2, 1011, 311);
//	Hexapod_Servo servo3(10, false, 0, 361, 561);
//	Hexapod_Servo servo4(11, false, 1, 161, 861);
//	Hexapod_Servo servo5(12, true, 2, 1011, 311);
//	Hexapod_Servo servo6(20, false, 0, 411, 611);
//	Hexapod_Servo servo7(21, false, 1, 161, 861);
//	Hexapod_Servo servo8(22, true, 2, 1011, 311);
//	Hexapod_Servo servo9(30, true, 0, 621, 421);
//	Hexapod_Servo servo10(31, true, 1, 861, 161);
//	Hexapod_Servo servo11(32, false, 2, 11, 711);
//	Hexapod_Servo servo12(40, true, 0, 611, 461);
//	Hexapod_Servo servo13(41, true, 1, 861, 161);
//	Hexapod_Servo servo14(42, false, 2, 41, 741);
//	Hexapod_Servo servo15(50, true, 0, 631, 351);
//	Hexapod_Servo servo16(51, true, 1, 861, 161);
//	Hexapod_Servo servo17(52, false, 2, 11, 711);

//	allServos[0] = Hexapod_Servo(0, false, 0, 361, 641);	
//	allServos[0] = servo0;
//	allServos[1] = servo1;
//	allServos[2] = servo2;
//	allServos[3] = servo3;	
//	allServos[4] = servo4;
//	allServos[5] = servo5;	
//	allServos[6] = servo6;	
//	allServos[7] = servo7;
//	allServos[8] = servo8;
//	allServos[9] = servo9;
//	allServos[10] = servo10;
//	allServos[11] = servo11;
//	allServos[12] = servo12;
//	allServos[13] = servo13;
//	allServos[14] = servo14;
//	allServos[15] = servo15;
//	allServos[16] = servo16;
//	allServos[17] = servo17;