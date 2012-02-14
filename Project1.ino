/*========================================================*/
/*



*/
/*========================================================*/

/*------- Hardware configuration -------*/

//                   1   2   3   4   5     6   7   8

const int col[8] = { 10, 11, 12 , A3, A5, A4, A1, A2 };

//                   1   2   3   4   5   6   7   8

const int row[8] = {  2, 7,  4 , 3, 5 , 6, 8, 9 };

/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // establish direction of pins we are using to drive LEDs 
  for(int i=0; i< 8 ; i++){
    pinMode( col[i], OUTPUT);
    pinMode( row[i], OUTPUT);
    
    digitalWrite( row[i], HIGH );
  }
}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  for(int r=0;r<8;r++){
    digitalWrite( row[r], LOW);
    for(int c=0;c<8;c++){
      digitalWrite(col[c], HIGH);
      delayMicroseconds(150);
      digitalWrite(col[c], LOW);
    }
    digitalWrite( row[r], HIGH);
  }
}  // end loop()

