// Revisit to test slider capability for different speeds using only 1 pin instead of 5 total pins for 5 preset speeds
#include <Servo.h>

Servo continuousServo;   
Servo sweepServo1;       
Servo sweepServo2;       

const int contServoPin = 9;
const int sweepServoPin1 = 10;
const int sweepServoPin2 = 11;

// 5 Speed Buttons
const int speedBtn1 = 2;
const int speedBtn2 = 3;
const int speedBtn3 = 4;
const int speedBtn4 = 5;
const int speedBtn5 = 6;

int contStop = 90;     // Adjust if needed for true stop
bool contAttached = true;

// Movement timing
unsigned long moveInterval = 2;      
unsigned long pauseTime = 500;       

// Sweep Servo 1 (0 ↔ 90)
int sweepPos1 = 0;
bool sweepUp1 = true;
bool pauseState1 = false;
unsigned long previousMillis1 = 0;
unsigned long pauseStart1 = 0;

// Sweep Servo 2 (90 ↔ 0)
int sweepPos2 = 90;
bool sweepUp2 = false;
bool pauseState2 = false;
unsigned long previousMillis2 = 0;
unsigned long pauseStart2 = 0;

void setup() {
  continuousServo.attach(contServoPin);
  sweepServo1.attach(sweepServoPin1);
  sweepServo2.attach(sweepServoPin2);

  pinMode(speedBtn1, INPUT_PULLUP);
  pinMode(speedBtn2, INPUT_PULLUP);
  pinMode(speedBtn3, INPUT_PULLUP);
  pinMode(speedBtn4, INPUT_PULLUP);
  pinMode(speedBtn5, INPUT_PULLUP);

  continuousServo.detach();  // Start with no signal
  contAttached = false;
}

void loop() {
  controlContinuousServo();
  sweepServoOne();
  sweepServoTwo();
}

// ----------------------------
// Continuous Servo – 5 Speed Presets
// ----------------------------
void controlContinuousServo() {

  int speed = 0;

  if (digitalRead(speedBtn1) == LOW) speed = 10;
  else if (digitalRead(speedBtn2) == LOW) speed = 20;
  else if (digitalRead(speedBtn3) == LOW) speed = 30;
  else if (digitalRead(speedBtn4) == LOW) speed = 40;
  else if (digitalRead(speedBtn5) == LOW) speed = 60;

  if (speed > 0) {
    if (!contAttached) {
      continuousServo.attach(contServoPin);
      contAttached = true;
    }
    continuousServo.write(contStop + speed);
  } 
  else {
    if (contAttached) {
      continuousServo.detach();   // Remove signal completely
      contAttached = false;
    }
  }
}

// ----------------------------
// Sweep Servo 1 (0 ↔ 90)
// ----------------------------
void sweepServoOne() {
  unsigned long currentMillis = millis();

  if (pauseState1) {
    if (currentMillis - pauseStart1 >= pauseTime) {
      pauseState1 = false;
      sweepUp1 = !sweepUp1;
    }
    return;
  }

  if (currentMillis - previousMillis1 >= moveInterval) {
    previousMillis1 = currentMillis;

    sweepServo1.write(sweepPos1);

    if (sweepUp1) {
      sweepPos1++;
      if (sweepPos1 >= 90) {
        sweepPos1 = 90;
        pauseState1 = true;
        pauseStart1 = currentMillis;
      }
    } else {
      sweepPos1--;
      if (sweepPos1 <= 0) {
        sweepPos1 = 0;
        pauseState1 = true;
        pauseStart1 = currentMillis;
      }
    }
  }
}

// ----------------------------
// Sweep Servo 2 (90 ↔ 0)
// ----------------------------
void sweepServoTwo() {
  unsigned long currentMillis = millis();

  if (pauseState2) {
    if (currentMillis - pauseStart2 >= pauseTime) {
      pauseState2 = false;
      sweepUp2 = !sweepUp2;
    }
    return;
  }

  if (currentMillis - previousMillis2 >= moveInterval) {
    previousMillis2 = currentMillis;

    sweepServo2.write(sweepPos2);

    if (sweepUp2) {
      sweepPos2++;
      if (sweepPos2 >= 90) {
        sweepPos2 = 90;
        pauseState2 = true;
        pauseStart2 = currentMillis;
      }
    } else {
      sweepPos2--;
      if (sweepPos2 <= 0) {
        sweepPos2 = 0;
        pauseState2 = true;
        pauseStart2 = currentMillis;
      }
    }
  }
}
