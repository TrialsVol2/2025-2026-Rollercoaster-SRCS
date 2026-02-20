#include <Servo.h>

Servo continuousServo;   
Servo sweepServo1;       
Servo sweepServo2;       

const int contServoPin = 9;
const int sweepServoPin1 = 10;
const int sweepServoPin2 = 11;
const int buttonPin = 2;

int contSpeed = 30;

// Movement timing
unsigned long moveInterval = 2;      // ~0.5 sec for 90°
unsigned long pauseTime = 500;       // pause at ends (ms)

bool directionForward = true;
bool lastButtonState = HIGH;

// Pin 10 (0 ↔ 90)
int sweepPos1 = 0;
bool sweepUp1 = true;
bool pauseState1 = false;
unsigned long previousMillis1 = 0;
unsigned long pauseStart1 = 0;

// Pin 11 (90 ↔ 0)
int sweepPos2 = 90;
bool sweepUp2 = false;
bool pauseState2 = false;
unsigned long previousMillis2 = 0;
unsigned long pauseStart2 = 0;

void setup() {
  continuousServo.attach(contServoPin);
  sweepServo1.attach(sweepServoPin1);
  sweepServo2.attach(sweepServoPin2);

  pinMode(buttonPin, INPUT_PULLUP);

  continuousServo.write(90);
}

void loop() {
  checkButton();
  controlContinuousServo();
  sweepServoOne();
  sweepServoTwo();
}

// ----------------------------
// Continuous Servo (Pin 9)
// ----------------------------
void controlContinuousServo() {
  if (directionForward) {
    continuousServo.write(90 + contSpeed);
  } else {
    continuousServo.write(90 - contSpeed);
  }
}

// ----------------------------
// Button Toggle (Pin 9 Only)
// ----------------------------
void checkButton() {
  bool currentButtonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    directionForward = !directionForward;
  }

  lastButtonState = currentButtonState;
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
