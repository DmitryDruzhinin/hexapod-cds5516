#include <CDS5500_2Serials.h> 
#include <Hexapod_Servo.h> 
#include <ServoConsole.h> 
int axisA[] = {0, 20, 40}; 
int axisB[] = {10, 30, 50}; 
int hipA[] = {1, 21, 41}; 
int hipB[] = {11, 31, 51}; 
int legA[] = {2, 22, 32}; 
int legB[] = {12, 32, 52}; 
int axis[] = {0, 10, 20, 30, 40, 50}; 
int hips[] = {1, 11, 21, 31, 41, 51}; 
int legs[] = {2, 12, 22, 32 ,42, 52}; 
int hip2[]={1}; 
int hip4[]={21}; 
int axis10[]={10}; 
int axis30[]={30}; 
int axis50[]={50}; 
int axis20[]={20}; 
int axis40[]={40}; 
int axis0[]={0};
int val, q=300; 
ServoConsole console; 
void setup(){ 
Serial3.begin(9600); 
Serial3.println("Hello leather!"   );
Serial3.println("8 - walk"  );
Serial3.println("2 - moonwalk" ); 
Serial3.println("4 - left"  );
Serial3.println("6 - right"  );
Serial3.println("7 - up"  );
Serial3.println("5 - mid"  );
Serial3.println("1 - down"  ); 
Serial3.println("9 - one"  );  
Serial3.println("3 - start"  );  
Serial.begin(115200); 
Serial2.begin(1000000); 
Serial1.begin(1000000);
console.Move(legs, 6, 350, 511); //Legs move to 170 for standing up 
console.Move(hips,6, 480, 511); // hips move to 480 for standing up 
console.Move(axisA, 3, 130, 511); // axis group A move to 130. Prepare for walking 
console.Move(axisB, 3, 70, 511); // axis group B move 70. Prepare for walking                         
} 
void loop(){ 
if (Serial3.available()) // check if any commands are coming 
{ 
val = Serial3.read(); // the variable val is equal to the received command
if (val == '8'){ walk(); }  
if (val == '2'){ moonwalk(); }  
if (val == '4'){ left(); }  
if (val == '6'){ right(); } 
if (val == '7'){ up(); }  
if (val == '5'){ mid(); }  
if (val == '1'){ down(); } 
} 
} 
void walk(){ 
delay(300); 
console.MoveUp(hipB, 3, 100, 500); //hips group B move up 100 
console.MoveUp(axisB, 3, 60, 300);// axis group B move forward 60
console.MoveDown(axisA, 3, 60, 300);// axis group A move backward 60 
delay(300);// waits for movement 
console.MoveDown(hipB, 3, 100, 500);//hips group B move down 100 
delay(300);// waits for movement 
console.MoveUp(hipA, 3, 100, 500);//hips group A move up 100 
console.MoveDown(axisB, 3, 60, 300);// axis group B move backward 60 
console.MoveUp(axisA, 3, 60, 300);// axis group A move forward 60
delay(300);// waits for movement 
console.MoveDown(hipA,3, 100, 500);//hips group A move down 100 
} 
void moonwalk(){ 
delay(300); 
console.MoveUp(hipB, 3, 100, 500); //hips group B move up 100 
console.MoveDown(axisB, 3, 60, 300);// axis group B move backward 60 
console.MoveUp(axisA, 3, 60, 300);// axis group A move forward 60
delay(300);// waits for movement 
console.MoveDown(hipB, 3, 100, 500);//hips group B move down 100 
delay(300);// waits for movement 
console.MoveUp(hipA, 3, 100, 500);//hips group A move up 100 
console.MoveUp(axisB, 3, 60, 300);// axis group B move forward 60
console.MoveDown(axisA, 3, 70, 300);// axis group A move backward 60 
delay(300);// waits for movement 
console.MoveDown(hipA,3, 100, 500);//hips group A move down 100 
} 
void right(){ 
delay(300); 
console.MoveUp(hipB, 3, 100, 500); //hips group B move up 100 
console.MoveUp(axisA, 3, 60, 100);// axis group B move forward 60
console.MoveDown(axisB, 3, 60, 100);// axis group B move forward 60
delay(300);// waits for movement 
console.MoveDown(hipB, 3, 100, 500);//hips group B move down 100 
delay(300);// waits for movement 
console.MoveUp(hipA, 3, 100, 500);//hips group A move up 100   
console.MoveUp(axisB, 3, 60, 100);// axis group B move forward 60
console.MoveDown(axisA, 3, 60, 100);// axis group A move forward 60
delay(300);// waits for movement 
console.MoveDown(hipA,3, 100, 500);//hips group A move down 100 
} 
void left(){ 
delay(300); 
//[place for your advertisement]
console.MoveUp(hipB, 3, 100, 500); //hips group B move up 100 
console.MoveDown(axisB, 3, 60, 300);// axis group B move forward 60
console.MoveDown(axisA, 3, 60, 300);// axis group A move backward 60 
delay(300);// waits for movement 
console.MoveDown(hipB, 3, 100, 500);//hips group B move down 100 
delay(300);// waits for movement 
console.MoveUp(hipA, 3, 100, 500);//hips group A move up 100 
console.MoveUp(axisB, 3, 60, 300);// axis group B move backward 60 
console.MoveUp(axisA, 3, 60, 300);// axis group A move forward 60
delay(300);// waits for movement 
console.MoveDown(hipA,3, 100, 500);//hips group A move down 100 
} 
void mid(){ 
console.Move(legs, 6, 350, 511); //Legs move to 170 for standing up 
console.Move(hips,6, 510, 511); // hips move to 480 for standing up 
console.Move(axisA, 3, 130, 511); // axis group A move to 130. Prepare for walking 
console.Move(axisB, 3, 60, 511); // axis group B move 70. Prepare for walking     
} 
void up(){  
console.Move(legs, 6, 700, 511); //Legs move to 170 for standing up 
console.Move(hips,6, 120, 511); // hips move to 480 for standing up 
console.Move(axisA, 3, 130, 511); // axis group A move to 130. Prepare for walking 
console.Move(axisB, 3, 60, 511); // axis group B move 70. Prepare for walking   
} 
void down(){ 
console.Move(legs, 6, 300, 511); //Legs move to 170 for standing up 
console.Move(hips,6, 250, 511); // hips move to 480 for standing up 
console.Move(axisA, 3, 130, 511); // axis group A move to 130. Prepare for walking 
console.Move(axisB, 3, 60, 511); // axis group B move 70. Prepare for walking  
} 
