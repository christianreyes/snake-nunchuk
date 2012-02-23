/*========================================================*/
/*



*/
/*========================================================*/

#include <Wire.h>
#include "nunchuck_funcs.h"
#include "enemy.h"
#include "body.h"
#include "history.h"

//                    1   2   3    4   5  6   7   8
const int col[8] = { 13,  1, 11 ,  7,  0, A0, 4, A3 };
const int row[8] = {  6,  2,  8 ,  5, A1,  9, A2, 10 };

const int MAXLENGTH = 16;

int length = 1;
body snake[MAXLENGTH];
body *head = &snake[0];

history moves[MAXLENGTH];

int timex = 0;
int timey = 0;

int timemove = 0;

int dim = 0;

const int NUMENEMIES = 4;
enemy enemies[NUMENEMIES];

/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */

void setup() {
  pinSetup();    // establish direction of pins we are using to drive LEDs 
  testPattern(); // display a test pattern to check if LEDs are connected properly
  smilieTest();  // smilie test pattern

  //Serial.begin(19200);
  randomSeed(analogRead(A7));
  nunchuck_init(); // send the initilization handshake
  
  for(int i=0;i<NUMENEMIES;i++){ enemies[i] = generateEnemy(); }
  
  head->x = random(1,9);
  head->y = random(1,9);
}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  updateDisplay();
  moveEnemies();
  processUserInput();
  processEating();
}  // end loop()

void updateDisplay(){
  for(int r=0; r<8; r++){
    digitalWrite( row[r], LOW);
    
    for(int i=0;i<length;i++){
      body b = snake[i];
      if( b.y == (r+1) ){
        digitalWrite( col[b.x - 1], HIGH);
      }
    }
    
    if(dim == 1){
      for(int i=0; i<NUMENEMIES; i++){
        enemy e = enemies[i];
        
        if(inThisRow(r, e)){
          digitalWrite( col[(int)e.x - 1], HIGH);
        }
      }
    }
    
    //delay(1);
    delayMicroseconds(500);
    
    for(int c=0; c<8; c++){
      digitalWrite( col[c], LOW);
    }
    
    digitalWrite( row[r], HIGH);
  }
}

void processEating(){
  if(length < MAXLENGTH){
    for(int i=0;i<NUMENEMIES; i++){
      enemy e = enemies[i];
      if(head->x == (int)e.x && head->y == (int)e.y){
        body last;
        last.x = (int)e.x;
        last.y = (int)e.y;
        
        snake[length] = last;
        length++;
        
        e = generateEnemy();
        enemies[i] = e;
      }
    } 
  }
}

void moveEnemies(){
  if(dim == 1){
    timemove++;
    if(timemove > 15){
      for(int i=0; i< NUMENEMIES; i++){
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
  }
    
  if(dim == 4){
    dim = 0;
  } else {
    dim++;
  }
}

void processUserInput(){
  nunchuck_get_data();
  
  timex++;
  if(timex > 15){
    if(head->x < 8 && nunchuck_joyx() > 180){
      timex = 0;
      head->x += 1;
    } else if(head->x > 1 && nunchuck_joyx() < 80){
      timex = 0;
      head->x -= 1;
    } 
  } else if(timex > 30000){
    timex = 0;
  }
  
  
  timey++;
  if(timey > 15){
    if(head->y > 1 && nunchuck_joyy() > 180){
      timey = 0;
      head->y--;
    } else if( head->y < 8 && nunchuck_joyy() < 80){
      timey = 0;
      head->y++;
    } 
  } else if(timey > 30000){
    timey = 0;
  }
  
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
    
    e.magnitude = (float)random(1,10) / 6;

    int tx; 
    int ty;
    
    if(random(0,2) == 0){
      tx = random(4,6);
      ty = random(4,6);
    } else {
      tx = head->x;
      tx = head->y;
    }
    
    e.angle = atan2((float)-(ty - e.y), (float)tx - e.x );
    
    return e;
}

boolean inThisRow(int r, enemy e){
  return (int)e.y == (r+1);
}

boolean inBounds(enemy e){
  return ((int)e.y >= 1 && (int)e.y <= 8) && ((int)e.x >= 1 && (int)e.x <= 8);
}

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
