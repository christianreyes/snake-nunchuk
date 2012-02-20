/*========================================================*/
/*



*/
/*========================================================*/

#include <Wire.h>
#include "nunchuck_funcs.h"
#include "enemy.h"

//                    1   2   3    4   5  6   7   8
const int col[8] = { 13,  1, 11 ,  7,  0, A0, 4, A3 };
const int row[8] = {  6,  2,  8 ,  5, A1,  9, A2,  10 };

int x;
int y;

int timex = 0;
int timey = 0;

int timemove = 0;

const int numEnemies = 3;
enemy enemies[numEnemies];

/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */

void setup() {
  // establish direction of pins we are using to drive LEDs 
  pinSetup();
  
  // display a test pattern to check if LEDs are connected properly
  testPattern();
  
  // smilie test pattern
  smilieTest();

  //Serial.begin(19200);
  randomSeed(analogRead(A7));
  nunchuck_init(); // send the initilization handshake
  
  for(int i=0;i<numEnemies;i++){
    enemies[i] = generateEnemy();
  }
  
  x = random(1,9);
  y = random(1,9);
}

enemy generateEnemy(){
    enemy e;
   
    if( random(2) == 0){
      e.x = random(1,9);
      (random(2) == 0)? e.y = 1 : e.y = 8;
    } else {
      (random(2) == 0)? e.x = 1 : e.x = 8;
      e.y = random(1,9);
    }
    
    e.magnitude = (float)random(1,10) / 7;

    int tx; 
    int ty;
    
    if(random(0,2) == 0){
      tx = random(4,6);
      ty = random(4,6);
    } else {
      tx = x;
      tx = y;
    }
    
    e.angle = atan2((float)-(ty - e.y), (float)tx - e.x );
    
    //e.bright = (float) random(60,80) / 100.0;
    /*
      Serial.print("Enemy x: ");
      Serial.print(e.x);
      Serial.print("\ty: ");
      Serial.print(e.y);
      Serial.print("\ttx: ");
      Serial.print(tx);
      Serial.print("\tty: ");
      Serial.print(ty);
      Serial.print("\tmag: ");
      Serial.print(e.magnitude);
      Serial.print("\tangle: ");
      Serial.println(e.angle);
    */
    
    return e;
}

boolean inThisRow(int r, enemy e){
  return (int)e.y == (r+1);
}

boolean inBounds(enemy e){
  return ((int)e.y >= 1 && (int)e.y <= 8) && ((int)e.x >= 1 && (int)e.x <= 8);
}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  for(int r=0; r<8; r++){
    digitalWrite( row[r], LOW);
    
    if( y == (r+1) ){
      digitalWrite( col[x-1], HIGH);
    }
    
    for(int i=0; i<numEnemies; i++){
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
  
  timemove++;
  if(timemove > 10){
    for(int i=0; i< numEnemies; i++){
      enemy e = enemies[i];
      
      if(inBounds(e)){
        e.x += e.magnitude * cos(e.angle);
        e.y -= e.magnitude * sin(e.angle);
      } else {
        e = generateEnemy();
      }
      
      enemies[i] = e;


    }
    
    timemove = 0;
  }
  
  nunchuck_get_data();

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
