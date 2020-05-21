/**
 *Created on June 24th
 *by Danfei Xu
 */
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
#include "ServoConsole.h"
#include "CDS5500_2Serials.h"
#include "Hexapod_Servo.h"

/*
 *The data below is not appicable to all the hexapod robot. Need to be modified according
 *to the default position of the servo.
 */
ServoConsole::ServoConsole(){
	int ID[] = {0, 1, 2, 10, 11, 12, 20, 21, 22, 30, 31, 32, 40, 41, 42, 50, 51, 52};
	boolean isReversed[] = {false, false, true, false, false, true, false, false, true, true, true, false, true, true, false, true, true, false};
	int part[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2};
	int lastStatus[] = {511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511};
	int lowerLimit[] = {361, 151, 1011, 391, 161, 1021, 411, 171, 1011, 621, 841, 21, 621, 881, 51, 631, 851, 21};
	int upperLimit[] = {641, 851, 311, 591, 861, 321, 611, 871, 311, 421, 141, 721, 421, 181, 751, 351, 151, 721};
//	int lowerLimit[] = {361, 151, 1011, 391, 161, 1021, 411, 171, 1011, 621, 841, 21, 621, 881, 51, 631, 851, 21};
//	int upperLimit[] = {561, 851, 311, 591, 861, 321, 611, 871, 311, 421, 141, 721, 421, 181, 751, 431, 151, 721};

	allServos.setEverything(ID, upperLimit, lowerLimit, lastStatus, isReversed, part);
}
/**
 *Limitation of rotation:
 *Legs: 0 - 700
 *Heaps: 0 - 700
 *Axis(front):0 - 280(300 is not suggested but is applicable)
 *Axis(mid and back): 0 - 200
 */

void ServoConsole::Move(int IDArray[], int size, int pos, int vel){
	int position[18];
	for(int i = 0; i < size; i++){
		int index = (IDArray[i]/10)*3 + IDArray[i]-((IDArray[i]/10)*10); 
		if(allServos.isInRange(index, pos)){
			position[i] = allServos.processPosition(index, pos);
			allServos.setStatus(index, pos);
		}
	}
	hostServo.SyncWritePos(IDArray, size, position, vel);
}

void ServoConsole::MoveUp(int IDArray[], int size, int incrPos, int vel){
	int position[18];
	for(int i = 0; i < size; i++){
		int index = (IDArray[i]/10)*3 + IDArray[i]-((IDArray[i]/10)*10); 
		int pos = allServos.getStatus(index) + incrPos;
		if(allServos.isInRange(index, pos)){
			position[i] = allServos.processPosition(index, pos);
			allServos.setStatus(index, pos);
		}
	}
	hostServo.SyncWritePos(IDArray, size, position, vel);
}

void ServoConsole:: MoveDown(int IDArray[], int size, int decrPos, int vel){
	int position[18];
	for(int i = 0; i < size; i++){
		int index = (IDArray[i]/10)*3 + IDArray[i]-((IDArray[i]/10)*10); 
		int pos = allServos.getStatus(index) - decrPos;
		if(allServos.isInRange(index, pos)){
			position[i] = allServos.processPosition(index, pos);
			allServos.setStatus(index, pos);
		}
	}
	hostServo.SyncWritePos(IDArray, size, position, vel);
}