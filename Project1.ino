/*========================================================*/
/*



*/
/*========================================================*/

#include <Wire.h>
#include "nunchuck_funcs.h"

/*------- Hardware configuration -------*/

//                   1   2   3   4   5     6   7   8

const int col[8] = { 10, 11, 12 , A3, 13, 13, A1, A2 };

//                   1   2   3   4   5   6   7   8

const int row[8] = {  2, 7,  4 , 3, 5 , 6, 8, 9 };

const int upSwitch   = 1;
const int downSwitch = 0;

int x = 0;
int y = 0;

int timex = 0;
int timey = 0;

/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  
  // establish direction of pins we are using to drive LEDs 
  for(int i=0; i< 8 ; i++){
    pinMode( col[i], OUTPUT);
    pinMode( row[i], OUTPUT);
    
    digitalWrite( row[i], HIGH );
    digitalWrite( col[i], LOW );
  }
  
  // display a test pattern to check if LEDs are connected properly
   for(int r=0;r<8;r++){
    digitalWrite( row[r], LOW);
    for(int c=0;c<8;c++){
      digitalWrite(col[c], HIGH );
      delay(15);
      digitalWrite(col[c], LOW );
    }
    digitalWrite( row[r], HIGH);
  }
  
  int smilie[8][8] = {
    { 0,0,0,0,0,0,0,0 },
    { 0,1,1,0,0,1,1,0 },
    { 0,1,1,0,0,1,1,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,1,1,0,0,1,1,0 },
    { 0,1,1,1,1,1,1,0 },
    { 0,0,1,1,1,1,0,0 },
    { 0,0,0,0,0,0,0,0 } 
  };
  
  for(int i=0;i<100;i++){
    for(int r=0;r<8;r++){
      digitalWrite( row[r], LOW);
      for(int c=0;c<8;c++){
        digitalWrite(col[c], smilie[r][c] ? HIGH : LOW );
      }
      //delayMicroseconds(650);
      delay(1);
      for(int c=0;c<8;c++){
        digitalWrite(col[c], LOW );
      }
      digitalWrite( row[r], HIGH);
    }
  }
  
  Serial.begin(19200);
  
  nunchuck_init(); // send the initilization handshake
  
}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  for(int r=0; r<8; r++){
    digitalWrite( row[r], LOW);
    for(int c=0; c<8; c++){
      if(c==(x-1) && r==(y-1)){
        digitalWrite( col[x-1], HIGH);
        delay(10);
        digitalWrite( col[x-1], LOW);
      }
    }
    digitalWrite( row[r], HIGH);
  }
  
  nunchuck_get_data();
  
  timex++;
  if(timex > 3){
    if(x < 8 && nunchuck_joyx() > 180){
      timex = 0;
      x+= 1;
    } else if(x > 0 && nunchuck_joyx() < 50){
      timex = 0;
      x= x-1;
    } 
  }
  
  
  timey++;
  if(timey > 3){
    if(y > 0 && nunchuck_joyy() > 180){
      timey = 0;
      y= y-1;
    } else if( y < 8 && nunchuck_joyy() < 50){
      timey = 0;
      y+= 1;
    } 
  }
  
  
  nunchuck_print_data();
}  // end loop()
