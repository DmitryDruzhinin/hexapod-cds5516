/*
 * CDS5500_2Serials.cpp
 * ArduinoHexapod
 *  Created on: Jun 7, 2011
 *      Author: Danfei Xu
 *		DFRobot
 */     

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 
#include "CDS5500_2Serials.h"

//This library uses two servo drivers to control the servos.


CDS5500_2Serials::CDS5500_2Serials (){
}

//Write position for single servo. 为单个舵机写入位置
//@param ID the ID of the servo. 
//@param position the position you want the servo to move.
//@param velocity the velocity you want the servo to move.

void CDS5500_2Serials:: WritePos(int ID, int position, int velocity){
	int messageLength = 7;
	byte pos2 =  position/255;
	byte pos =  position%255;	
	byte vel2 =  velocity/255;
	byte vel =  velocity%255;
	
	if(ID<30){//If the ID is smaller than 30, use Serial2 to print data
		Serial2.write(startByte);              // send some data
		Serial2.write(startByte);
		Serial2.write(ID);
		Serial2.write(messageLength);
		Serial2.write(INST_WRITE);
		Serial2.write(P_GOAL_POSITION_L);
		Serial2.write(pos);
		Serial2.write(pos2);
		Serial2.write(vel);
		Serial2.write(vel2);
		Serial2.write((~(ID + (messageLength) + INST_WRITE + P_GOAL_POSITION_L + pos + pos2 + vel + vel2))&0xFF);
	} 
	if(ID>=30){//If the ID is greater than 30, use Serial1 to print data
		Serial1.write(startByte);              // send some data
		Serial1.write(startByte);
		Serial1.write(ID);
		Serial1.write(messageLength);
		Serial1.write(INST_WRITE);
		Serial1.write(P_GOAL_POSITION_L);
		Serial1.write(pos);
		Serial1.write(pos2);
		Serial1.write(vel);
		Serial1.write(vel2);
		Serial1.write((~(ID + (messageLength) + INST_WRITE + P_GOAL_POSITION_L + pos + pos2 + vel + vel2))&0xFF);
	}
	
}
//Set the ID of the servo.

void CDS5500_2Serials:: SetID(int ID, int newID){
	int messageLength = 4;
	if(ID<30){
		Serial2.write(startByte);              // send some data
		Serial2.write(startByte);
		Serial2.write(ID);
		Serial2.write(messageLength);
		Serial2.write(INST_WRITE);
		Serial2.write(P_ID);
		Serial2.write(newID);
		Serial2.write((~(ID + (messageLength) + INST_WRITE+ P_ID + newID))&0xFF);
	} else {
		Serial1.write(startByte);              // send some data
		Serial1.write(startByte);
		Serial1.write(ID);
		Serial1.write(messageLength);
		Serial1.write(INST_WRITE);
		Serial1.write(P_ID);
		Serial1.write(newID);
		Serial1.write((~(ID + (messageLength) + INST_WRITE+ P_ID + newID))&0xFF);
	}
	
}
//Set the angle limitation of the servo 
void CDS5500_2Serials:: SetAngleLimit(int ID, int lowerLimit, int upperLimit){
	int messageLength = 8;
	byte lowerLimitB = lowerLimit%255;
	byte lowerLimitS = lowerLimit/255;
	byte upperLimitB = upperLimit%255;
	byte upperLimitS = upperLimit/255;
	Serial2.write(startByte);              // send some data
	Serial2.write(startByte);
	Serial2.write(ID);
	Serial2.write(messageLength);
	Serial2.write(INST_WRITE);
	Serial2.write(0x08);
	Serial2.write(upperLimitB);
	Serial2.write(0x09);
	Serial2.write(upperLimitS);
	Serial2.write(0x06);
	Serial2.write(lowerLimitB);
	Serial2.write(0x07);
	Serial2.write(lowerLimitS);	
	Serial2.write((~(ID + (messageLength) + INST_WRITE+ 0x08 + 0x09 + 0x06 + 0x07 + upperLimitB+ upperLimitS+
					 lowerLimitB + lowerLimitS))&0xFF);
}

//Synchronously write positions. 同时为多个舵机写入位置
//@param ID the array of IDs that you want write position to.
//@position the array of the positions that you want the servos to move. 
void CDS5500_2Serials:: SyncWritePos(int ID[], int size, int position[], int velocity){

	int smallIDcount = 0;
	byte smallCheckSum = 0;
	int bigIDcount= 0;
	byte bigCheckSum = 0;
	//Count number of ID
	for(int i = 0; i < size; i++){
		if(ID[i] < 30){
			smallIDcount ++;
		} else {
			bigIDcount ++;
		}
	}
	
	if(bigIDcount > 0){
		int messageLength = bigIDcount*(5) + 4;
		Serial1.write(startByte);              // send some data
		Serial1.write(startByte);
		Serial1.write(0xFE);
		Serial1.write(messageLength);
		Serial1.write(INST_SYNC_WRITE);
		Serial1.write(0x1e);
		Serial1.write(0x04);
		for(int i = 0; i < size; i++){
			if(ID[i] >= 30){
				Serial1.write(ID[i]);
				Serial1.write(position[i]%255);
				Serial1.write(position[i]/255);
				Serial1.write(velocity%255);
				Serial1.write(velocity/255);
				bigCheckSum += byte(ID[i]) + byte(position[i]%255) + byte(position[i]/255)
				+ byte(velocity%255) + byte(velocity/255); // sum of ID and data
			}
		}
		Serial1.write((~(0xFE + (messageLength) + INST_SYNC_WRITE+ 0x1e + 0x04 + bigCheckSum))&0xFF);
	}
	if(smallIDcount > 0){
		int messageLength = smallIDcount*(5) + 4;
		Serial2.write(startByte);              // send some data
		Serial2.write(startByte);
		Serial2.write(0xFE);
		Serial2.write(messageLength);
		Serial2.write(INST_SYNC_WRITE);
		Serial2.write(0x1e);
		Serial2.write(0x04);
		for(int i = 0; i < size; i++){
			if(ID[i] < 30){
				Serial2.write(ID[i]);
				Serial2.write(position[i]%255);
				Serial2.write(position[i]/255);
				Serial2.write(velocity%255);
				Serial2.write(velocity/255);
				smallCheckSum += byte(ID[i]) + byte(position[i]%255) + byte(position[i]/255)
				+ byte(velocity%255) + byte(velocity/255); //sum of ID and data
			}
		}
		Serial2.write((~(0xFE + (messageLength) + INST_SYNC_WRITE + 0x1e +0x04 + smallCheckSum))&0xFF);
	}
	
}

//Synchronously write positions. 同时为多个舵机写入位置
//@param ID the array of IDs that you want write position to.
//@position the array of the positions that you want the servos to move. 
void CDS5500_2Serials:: SyncWritePos(int ID[], int size, int position[], int velocity[]){
	
	int smallIDcount = 0;
	byte smallCheckSum = 0;
	int bigIDcount= 0;
	byte bigCheckSum = 0;
	//Count number of ID
	for(int i = 0; i < size; i++){
		if(ID[i] < 30){
			smallIDcount ++;
		} else {
			bigIDcount ++;
		}
	}
	
	if(bigIDcount > 0){
		int messageLength = bigIDcount*(5) + 4;
		Serial1.write(startByte);              // send some data
		Serial1.write(startByte);
		Serial1.write(0xFE);
		Serial1.write(messageLength);
		Serial1.write(INST_SYNC_WRITE);
		Serial1.write(0x1e);
		Serial1.write(0x04);
		for(int i = 0; i < size; i++){
			if(ID[i] >= 30){
				Serial1.write(ID[i]);
				Serial1.write(position[i]%255);
				Serial1.write(position[i]/255);
				Serial1.write(velocity[i]%255);
				Serial1.write(velocity[i]/255);
				bigCheckSum += byte(ID[i]) + byte(position[i]%255) + byte(position[i]/255)
				+ byte(velocity[i]%255) + byte(velocity[i]/255); // sum of ID and data
			}
		}
		Serial1.write((~(0xFE + (messageLength) + INST_SYNC_WRITE+ 0x1e + 0x04 + bigCheckSum))&0xFF);
	}
	if(smallIDcount > 0){
		int messageLength = smallIDcount*(5) + 4;
		Serial2.write(startByte);              // send some data
		Serial2.write(startByte);
		Serial2.write(0xFE);
		Serial2.write(messageLength);
		Serial2.write(INST_SYNC_WRITE);
		Serial2.write(0x1e);
		Serial2.write(0x04);
		for(int i = 0; i < size; i++){
			if(ID[i] < 30){
				Serial2.write(ID[i]);
				Serial2.write(position[i]%255);
				Serial2.write(position[i]/255);
				Serial2.write(velocity[i]%255);
				Serial2.write(velocity[i]/255);
				smallCheckSum += byte(ID[i]) + byte(position[i]%255) + byte(position[i]/255)
				+ byte(velocity[i]%255) + byte(velocity[i]/255); //sum of ID and data
			}
		}
		Serial2.write((~(0xFE + (messageLength) + INST_SYNC_WRITE + 0x1e +0x04 + smallCheckSum))&0xFF);
	}
	
}


int CDS5500_2Serials::ReadPos(int ID){
	int messageLength = 4;
	int count = 0;
	if(ID<30){//If the ID is smaller than 30, use Serial2 to print data
//		Serial2.flush();
		Serial2.write(startByte);              // send some data
		Serial2.write(startByte);
		Serial2.write(ID);
		Serial2.write(messageLength);
		Serial2.write(INST_READ);
		Serial2.write(0x25);
		Serial2.write(0x01);
		Serial2.write((~(ID + (messageLength) + INST_READ + 0x25 + 0x01))&0xFF);
//		Serial2.write(0x2B);
//		Serial2.write(0x01);
//		Serial2.write((~(ID + (messageLength) + INST_READ + 0x2B + 0x01))&0xFF);
		
//		delay(1000);
		while(count <6){
//			Serial.println("reading");
			if(Serial2.available()>0){
				byte incomingByte = Serial2.read();
				Serial.print("I received: ");
				Serial.println(incomingByte, DEC);
				count++;
			}
		}
	} 
	if(ID>=30){//If the ID is greater than 30, use Serial1 to print data
		Serial1.write(startByte);              // send some data
		Serial1.write(startByte);
		Serial1.write(ID);
		Serial1.write(messageLength);
		Serial1.write(INST_READ);
		Serial1.write(0x24);
		Serial1.write(0x25);
		Serial1.write((~(ID + (messageLength) + INST_READ + 0x24 + 0x25))&0xFF);
		if(Serial1.available()> 0){
			byte incomingByte = Serial1.read();
			Serial.print("I received: ");
			Serial.println(incomingByte, DEC);
		}
	}
	
	return 1;
}


//Reset all settings of the servo
//@param ID the ID of the servo that you want to reset

void CDS5500_2Serials:: Reset(int ID){
	Serial2.write(startByte);              // send some data
	Serial2.write(startByte);
	Serial2.write(ID);
	Serial2.write(0x02);
	Serial2.write(0x06);
	Serial2.write((~(ID + 0x02 +0x06))&0xFF);
}

//set the working temrature limit of the servo
void CDS5500_2Serials::SetTempLimit(int ID, int temperature){
	Serial2.write(startByte);              // send some data
	Serial2.write(startByte);
	Serial2.write(ID);
	Serial2.write(0x04);
	Serial2.write(0x03);
	Serial2.write(0x0B);
	Serial2.write(temperature);
	Serial2.write((~(ID + 0x04 +0x03 + 0x0B + temperature))&0xFF);
}