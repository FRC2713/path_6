
// Robot Platform

#include <IRremote.h>

int IR_RECEIVE_PIN = 6;
IRrecv IrReceiver(IR_RECEIVE_PIN);


#include "moves.h"

//#define wheelDiameter 2.320
// Phil's robot
#define wheelDiameter 1.5  
#define degPerStep 11.25                                    // deg per full step   /1/5.625  //5.625/64.0
#define stepsPerRev (360/(degPerStep/64))                   // full steps per rev of output shaft = 2048
#define inchPerStep ((3.1415*wheelDiameter)/stepsPerRev)    //degPerStep/360.0) =  
#define stepsPerInch 1./inchPerStep                         // = 0.003589" (with 2.34" dia.)
//#define wheelBase 6.48
// Phil's robot
#define wheelBase 7.75

// d8stance between wheels
#define stepsPerDegree (wheelBase*3.1415/inchPerStep)/360   // = 27.3 with abocve dia and base


// motion profile states
#define accel  1
#define conspd 2
#define decel  3

float test;


volatile unsigned int stepcnt;  // decremented in interrupt
volatile unsigned int stepCount;         // 
unsigned int stepSave;
unsigned int moveSteps;
unsigned int endRampUp;
unsigned int startRampDn;

volatile byte waveform;
volatile byte mask;
volatile int freq;
unsigned int n;
unsigned int i;               // index
unsigned int j;
unsigned int jfinal;
unsigned int runState;        // accel, const, decel
volatile int d;
volatile boolean moveDone;
boolean cmdRcvd;
int compVal=150;              // value to use for timer compare interrupt
bool state=0;
int timer;
long Serial_;
// IO pin use
#define STEPPIN 8
#define R_DIRPIN 11
#define L_DIRPIN 9
#define R_ENPIN 7
#define L_ENPIN 12
#define TESTPIN 10

int RECV_PIN =6;     
IRrecv irrecv(RECV_PIN);     
decode_results results;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
 }  // prints title with ending line break
//  irrecv.enableIRIn();     

  Serial.print("wheelDiameter = ");
  Serial.println(wheelDiameter, 10);  
  Serial.print("stepsPerRev = ");
  Serial.println(stepsPerRev, 10);  
  Serial.print("inchPerStep = ");
  Serial.println(inchPerStep, 10);  
  Serial.print("stepsPerInch = ");
  Serial.println(stepsPerInch, 10);  
  Serial.print("stepsPerDeg = ");
  Serial.println(stepsPerDegree, 10);  
  
  //set pins as outputs
 pinMode(STEPPIN, OUTPUT);
 pinMode(R_DIRPIN, OUTPUT);
 pinMode(L_DIRPIN, OUTPUT);
 pinMode(R_ENPIN, OUTPUT);
 pinMode(L_ENPIN, OUTPUT);
 digitalWrite (R_ENPIN, HIGH);              // disable drivers
 digitalWrite (L_ENPIN, HIGH);              // disable drivers

 pinMode(TESTPIN, OUTPUT);
  pinMode( LED_BUILTIN, OUTPUT ); //Phil    
//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = compVal;  //124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  TCCR0A |= (1 << WGM01);           // turn on CTC mode
  TCCR0B |= (1 << CS02);            // clock/256   
  TIMSK0 |= (1 << OCIE0A);          // enable timer compare interrupt
//  IrReceiver.enableIRIn();  // Start the receiver
  irrecv.enableIRIn();  // Start the receiver
}

ISR(TIMER0_COMPA_vect){    //This is the interrupt request
  digitalWrite(STEPPIN, HIGH);
//  digitalWrite (STEPPIN1, !bitRead(PORTB, 0));          
  for (d=0; d<2;)
  {
    d++;
  }
  OCR0A = compVal;
  stepCount++;
  digitalWrite(STEPPIN, LOW);
}


void loop(){
  
  digitalWrite (R_ENPIN, HIGH);              // disable drivers
  digitalWrite (L_ENPIN, HIGH);              // disable drivers
  results.value = 0;
  cmdRcvd = false;
  do {
    digitalWrite( LED_BUILTIN, HIGH );
    if (irrecv.decode(&results)){
      Serial.println(results.value, HEX);
      irrecv.resume();
    }
    switch (results.value) {
      case 0xff18e7:        // "2"
        pm= &moves[0];      // 6x6 box
        cmdRcvd = true;
        break;
      case 0xff30cf:        // "1"
        pm= &moves_1[0];    // long move with anti backlash
        cmdRcvd = true;
        break;
      case 0xff7a85:        // "3"
        pm= &moves_2[0];    // forward 6 inches
        cmdRcvd = true;
        break;
      case 0xff6897:        // "0"
        pm= &moves_3[0];    // rotate 360
        cmdRcvd = true;
        break;
      case 0xff10ef:        // "4"
        pm= &moves_4[0];    // rotate 90
        cmdRcvd = true;
        break;
      case 0xff38c7:        // "5"
        pm= &moves_5[0];    // move -6 inches
        cmdRcvd = true;
        break;
      case 0xff5aa5:        // "6"
        pm= &moves_6[0];    // rotate -90
        cmdRcvd = true;
        break;
      case 0xff42bd:        // "7"
        pm= &moves_7[0];    // rotate -90
        cmdRcvd = true;
        break;
      case 0xff4ab5:        // "8"
        pm= &moves_8[0];    // rotate -90
        cmdRcvd = true;
        break;
        default:
        break;      
    }
  } while (!cmdRcvd);
  
  Serial.println("start loop");
//  digitalWrite (R_ENPIN, LOW);              // enable drivers
//  digitalWrite (L_ENPIN, LOW);              // enable drivers
//  pm= &moves[0];
  for (i=0; ; i++)
  {
    if (pm[i].amount != 0) {
      digitalWrite( LED_BUILTIN, LOW ); // Phil

     #include "domove.h"
    }
    else
      break;
  }
  Serial.println("end move");
  digitalWrite (R_ENPIN, HIGH);              // disable drivers
  digitalWrite (L_ENPIN, HIGH);              // disable drivers
}    
