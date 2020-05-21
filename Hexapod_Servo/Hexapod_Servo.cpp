
/**
 *Created on June 24th
 *by Danfei Xu
 *This class mainly stores all the informations, including IDs, upper/lower rotation limitations, last 
 *positions, and if the rotation direction is reversed.
 *Hexapod_Servo库主要功能为存储所有舵机的信息，包括ID, 转角限制，上一次移动的位置，还有是否需要反方向转动（六足左右两边舵机转动方向相反）。
 */

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
#include "Hexapod_Servo.h"
/**
 * constructor of the Hexapod_Servo class.
 * 声明 Hexapod_Servo 库
 */
Hexapod_Servo::Hexapod_Servo(int _ID[], int _upperLimit[], int _lowerLimit[], int _lastStatus[], boolean _isReversed[], int _part[]){
	for(int i = 0; i < 18; i++){
		ID[i] = _ID[i];
		upperLimit[i] = _upperLimit[i];
		lowerLimit[i] = _lowerLimit[i];
		lastStatus[i] = _lastStatus[i];
		isReverse[i] = _isReversed[i];
		part[i] = _part[i];
	}

}

/*
 *Empty Constructor
 */
Hexapod_Servo::Hexapod_Servo(){
}



/*
 *Check if the position is in the range of limitation
 *检查移动的位置是否在转角限制内
 */
boolean Hexapod_Servo:: isInRange(int index, int pos){
	if((!isReverse[index] && (pos+lowerLimit[index]) >= lowerLimit[index] && (pos+lowerLimit[index]) <= upperLimit[index])
	   ||(isReverse[index] && (lowerLimit[index] - pos) <= lowerLimit[index] && (lowerLimit[index] - pos) >= upperLimit[index])){
		return true;
	} else {
		return false;
	}
}
/*
 *存入所有舵机的信息
 *Store all the information of the servos. 
 *
 */
void Hexapod_Servo::setEverything(int _ID[], int _upperLimit[], int _lowerLimit[], int _lastStatus[], boolean _isReversed[], int _part[]){
	for(int i = 0; i < 18; i++){
		ID[i] = _ID[i];
		upperLimit[i] = _upperLimit[i];
		lowerLimit[i] = _lowerLimit[i];
		lastStatus[i] = _lastStatus[i];
		isReverse[i] = _isReversed[i];
		part[i] = _part[i];
	}
}
/*
 *Return the last position of the servo
 *取得舵机上一次移动到的位置
 */
int Hexapod_Servo:: getStatus(int index){
	return lastStatus[index];
}
/*
 *设置移动的位置
 *Set the position status.
 */
void Hexapod_Servo:: setStatus(int index, int pos){
	lastStatus[index] = pos;
}

/*
 *return the ID of the servo according to the index of the array
 *根据数组的位置得到舵机的ID.
 */
int Hexapod_Servo:: getID(int index){
	return ID[index];
}
/**
 *Return true if the servo need to rotate reversely
 *检查是否需要反向转动
 */
boolean Hexapod_Servo:: isReversed(int index){
	return isReverse[index];
}
int Hexapod_Servo:: getPart(int index){
	return part[index];
}

/*
 *Constrain the position in the limitation range.
 *
 */
int Hexapod_Servo:: processPosition(int index, int pos){
	if(isReversed(index)){
		return lowerLimit[index] - pos;
	} else {
		return lowerLimit[index] + pos;
	}
}