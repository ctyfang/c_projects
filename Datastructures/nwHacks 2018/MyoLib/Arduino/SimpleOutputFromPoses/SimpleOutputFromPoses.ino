// NWHACKS 2018, TEAM MYO-HOME

// GLOBALS
#include <MyoController.h>
#include <Servo.h>

Servo myservo;
#define FIST_PIN 8
#define WAVEIN_PIN 2
#define WAVEOUT_PIN 8
#define FINGERSSPREAD_PIN 3
#define DOUBLETAP_PIN 9

#define STEP1 4
#define DIR1 5
#define STEP2 6
#define DIR2 7

MyoController myo = MyoController();
int LED = 0;
int nwLED = 0;
int doorState = 0; // closed = 0
int i;

// GPIO PIN INITIALIZATION
void setup() {
  myservo.attach(WAVEIN_PIN); // Servo
  
  pinMode(FIST_PIN, OUTPUT); // Stepper1
  pinMode(STEP1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  digitalWrite(DIR1, HIGH);

  pinMode(STEP2, OUTPUT); // Stepper2
  pinMode(DIR2, OUTPUT);
  digitalWrite(DIR2, HIGH);
  
  pinMode(FINGERSSPREAD_PIN, OUTPUT); // LED
  pinMode(DOUBLETAP_PIN, OUTPUT); // TBD
  
  myo.initMyo();
}

// EVENT LAYOUT LOOP
void loop()
{
   myo.updatePose();
   
   switch ( myo.getCurrentPose() ) {
    // cases: rest, fist, waveIn, waveOut, fingersSpread, doubleTap
    
    case rest:
      //Serial.println("rest");
      digitalWrite(FIST_PIN,LOW); 
      digitalWrite(WAVEOUT_PIN,LOW);
      //digitalWrite(FINGERSSPREAD_PIN,LOW);
      //digitalWrite(DOUBLETAP_PIN,LOW);
      
      //myservo.write(90);
      break;
      
    case fist:
      //digitalWrite(FINGERSSPREAD_PIN, LOW);
      for(i=0; i<200; i++){
        digitalWrite(STEP1, HIGH);
        digitalWrite(STEP1, LOW);
        delay(5);
      }
      //digitalWrite(FIST_PIN,HIGH);
      
      digitalWrite(LED_BUILTIN,HIGH);
      break;
      
    case waveIn:
      if(doorState == 0){
        doorState = 1;
        myservo.write(90);
      }
      else{
        doorState = 0;
        myservo.write(0);
      }
      
      //digitalWrite(FINGERSSPREAD_PIN, LOW);
      delay(1500);      
      break;
      
    case waveOut:

      digitalWrite(LED_BUILTIN,LOW);
      for(i=0; i<200; i++){
        digitalWrite(STEP2, HIGH);
        digitalWrite(STEP2, LOW);
        delay(5);
      }
      break;

    case doubleTap:
      if(nwLED == 0){
        digitalWrite(DOUBLETAP_PIN, HIGH);
        nwLED = 1;
      }
      else{
        digitalWrite(DOUBLETAP_PIN, LOW);
        nwLED = 0;
      }
      
      delay(1000);
      break;


   case fingersSpread:
      if(LED == 0){
        digitalWrite(FINGERSSPREAD_PIN, HIGH);
        LED = 1;
      }
      else{
        digitalWrite(FINGERSSPREAD_PIN, LOW);
        LED = 0;
      }
      
      delay(1000);
      break;
   }
   
   delay(2); // sample frequency
}
