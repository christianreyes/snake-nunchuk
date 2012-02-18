/*========================================================*/
/*



*/
/*========================================================*/

#include <Wire.h>
#include "nunchuck_funcs.h"
#include "enemy.h"

//                    1   2   3    4   5  6   7   8
const int col[8] = { 10, 11, 12 , A3, 13, 0, A1, A2 };
const int row[8] = {  2,  7,  4 ,  3,  5, 6,  8,  9 };

int timex = 0;
int timey = 0;

enemy enemies[5];

/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */

void setup() {
  // establish direction of pins we are using to drive LEDs 
  pinSetup();
  
  // display a test pattern to check if LEDs are connected properly
  testPattern();
  
  // smilie test pattern
  smilieTest();

<<<<<<< Updated upstream
  // Serial.begin(19200);
=======
  //Serial.begin(19200);
>>>>>>> Stashed changes
  randomSeed(analogRead(A7));
  nunchuck_init(); // send the initilization handshake
  
  for(int i=0;i<5;i++){
    enemies[i] = generateEnemy();
  }
  
  //x = random(1,9);
  //y = random(1,9);
}

enemy generateEnemy(){
    enemy e;
<<<<<<< Updated upstream
    e.x = random(1,9);
    e.y = random(1,9);
    e.magnitude = random(1,3);
=======
   
    if( random(2) == 0){
      e.x = random(0,9);
      e.y = 0;
    } else {
      e.x = 0;
      e.y = random(0,9);
    }
    
    e.magnitude = (float)random(1,4);
>>>>>>> Stashed changes
    
    int tx = random(3,7);
    int ty = random(3,7);
    
    e.angle = atan2(e.x, e.y);
    
    return e;
}

boolean inThisRow(int r, enemy e){
  return e.y == (r+1);
}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  for(int r=0; r<8; r++){
    digitalWrite( row[r], LOW);
    
    for(int i=0; i<5; i++){
      enemy e = enemies[i];
      
      if(inThisRow(r, e)){
        digitalWrite( col[(int)e.x - 1], HIGH);
      }
    }
    
    delay(1);
    
    for(int c=0; c<8; c++){
      digitalWrite( col[c], LOW);
    }
    
    digitalWrite( row[r], HIGH);
  }
  
<<<<<<< Updated upstream
  
=======
  timemove++;
  if(timemove > 20){
    for(int i=0; i< 5; i++){
      enemy e = enemies[i];
      
      e.x = e.x + e.magnitude * cos(e.angle);
      e.y = e.y + e.magnitude * sin(e.angle);
      
      enemies[i] = e;
      
      //Serial.print("cos: "); Serial.println( e.x + e.magnitude * cos(e.angle) );
      //Serial.print("sin: "); Serial.println( e.x + e.magnitude * cos(e.angle) );
      //Serial.println("");
      
    }
    
    timemove = 0;
  }
 
>>>>>>> Stashed changes
}  // end loop()


void pinSetup(){
  for(int i=0; i< 8 ; i++){
    pinMode( col[i], OUTPUT);
    pinMode( row[i], OUTPUT);
    
    digitalWrite( row[i], HIGH );
    digitalWrite( col[i], LOW );
  }
}

void testPattern(){
  for(int r=0;r<8;r++){
    digitalWrite( row[r], LOW);
    for(int c=0;c<8;c++){
      digitalWrite(col[c], HIGH );
      delay(15);
      digitalWrite(col[c], LOW );
    }
    digitalWrite( row[r], HIGH);
  }
}

void smilieTest(){
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
}


    
    /*
    for(int c=0; c<8; c++){
      
      if(c==(x-1) && r==(y-1)){
        digitalWrite( col[x-1], HIGH);
        //delayMicroseconds(500);
        delay(1);
        digitalWrite( col[x-1], LOW);
        
        //Serial.print("x: "); Serial.print(x); Serial.print(" y: "); Serial.println(y);
      }
    }
    digitalWrite( row[r], HIGH);
    */
    
    
    //nunchuck_get_data();
  /*
  timex++;
  if(timex > 10){
    if(x < 8 && nunchuck_joyx() > 180){
      timex = 0;
      x+= 1;
    } else if(x > 1 && nunchuck_joyx() < 80){
      timex = 0;
      x= x-1;
    } 
  } else if(timex > 30000){
    timex = 0;
  }
  
  
  timey++;
  if(timey > 10){
    if(y > 1 && nunchuck_joyy() > 180){
      timey = 0;
      y= y-1;
    } else if( y < 8 && nunchuck_joyy() < 80){
      timey = 0;
      y+= 1;
    } 
  } else if(timey > 30000){
    timey = 0;
  }
  
  */
  // nunchuck_print_data();
