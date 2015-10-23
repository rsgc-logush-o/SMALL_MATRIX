//INTERRUPT TIMER USE
//COMPARE MATCH REGISTER IS 259
//PRESCALER IS 1024
//FREQUENCY IS 6HZ
//ARDUINO CLOCK SPEED IS 16,000,000 HZ OR 16 MHZ
//I WILL HAVE TO USE TIMER1
//

# define

int dataPin = 9;
int clockPin = 10;
int latchPin = 8;
byte y[8];
byte x[8];

void setup() {

cli(); //TO TURN OFF INTERRUPTS

TCCR1A = 0; //SET REGISTER TO 0
TCCR1B = 0; // SET REGISTER TO 0
TCNT1 = 0; //INITIALIZE COUNTER TO 0 VALUE

OCR1A = 259; //SET THE COMPARE MATCH REGISTER TO 259 VALUE

TCCR1B |= (1 << WGM12); //TURN ON CTC MODE

TCCR1B |= (1 << CS12) | (1 << CS10); // MAKE THE 1024 BIT PRESCALER

TIMSK1 |= (1 << OCIE1A); //ENABLE THE COMPARE INTERRUPT


sei(); //TURN ON INTERRUPTS
// x = new byte[8];
// y = new byte[8];

 pinMode(dataPin, OUTPUT);
 pinMode(clockPin, OUTPUT);
 pinMode(latchPin, OUTPUT);

 for(int i = 0; i < 8; i++)
 {
    bitWrite(y[i], i, 1);
    x[i] = 255;
 }

 // thread(displayToMatrix);

}

void loop() {


//writePixel(7,7);
//writePixel(6,6);
//writePixel(5,5);
//writePixel(4,4);
//writePixel(3,3);
//writePixel(2,2);
//writePixel(1,1);
//writePixel(0,0);
//writePixel(0,7);
//writePixel(1,6);
//writePixel(2,5);
//writePixel(3,4);
//writePixel(4,3);
//writePixel(5,2);
//writePixel(6,1);
//writePixel(7,0);


for(int i = 0; i < 8; i++)
{
  for(int j = 0; j < 8; j++)
  {

    writePixel(i, j);

    //displayToMatrix();

    delay(500);

    erasePixel(i, j);
    
  }
}


  
  
 

}


void displayToMatrix()
{

 
  for(int i = 0; i < 8; i++)
  {

    digitalWrite(latchPin, LOW);

      
      shiftOut(dataPin, clockPin, LSBFIRST, x[i]);
      shiftOut(dataPin, clockPin, LSBFIRST, y[i]);

    digitalWrite(latchPin, HIGH);

  //  delay(500);
      
    
  }
  
}


void writePixel(int xDraw, int yDraw)
{

    bitWrite(x[yDraw], xDraw, 0);
    
}
void erasePixel(int xErase, int yErase)
{
  bitWrite(x[yErase], xErase, 1);

}


ISR(TIMER1_COMPA_vect)
{
   for(int i = 0; i < 8; i++)
  {

    digitalWrite(latchPin, LOW);

      
      shiftOut(dataPin, clockPin, LSBFIRST, x[i]);
      shiftOut(dataPin, clockPin, LSBFIRST, y[i]);

    digitalWrite(latchPin, HIGH);

  //  delay(500);
      
    
  }
}


