#include <Servo.h>

// ----------------------------
// Servo Objects
// ----------------------------
Servo continuousServo;   
Servo sweepServo1;       
Servo sweepServo2;       

// ----------------------------
// Pin Assignments
// ----------------------------
const int contServoPin = 9;
const int sweepServoPin1 = 10;
const int sweepServoPin2 = 11;
const int modeButtonPin = 2;

// ----------------------------
// Continuous Servo Settings
// ----------------------------
int contStop = 90;          // Adjust 88–92 if slight creeping
bool contAttached = false;
int speedMode = 0;          // 0 = OFF, 1–5 = speed levels
bool lastButtonState = HIGH;

// ----------------------------
// Sweep Timing
// ----------------------------
unsigned long moveInterval = 2;      
unsigned long pauseTime = 500;       

// ----------------------------
// Sweep Servo 1 (0 ↔ 90)
// ----------------------------
int sweepPos1 = 0;
bool sweepUp1 = true;
bool pauseState1 = false;
unsigned long previousMillis1 = 0;
unsigned long pauseStart1 = 0;

// ----------------------------
// Sweep Servo 2 (90 ↔ 0)
// ----------------------------
int sweepPos2 = 90;
bool sweepUp2 = false;
bool pauseState2 = false;
unsigned long previousMillis2 = 0;
unsigned long pauseStart2 = 0;

// ============================================================
// SETUP
// ============================================================
void setup() {

  continuousServo.attach(contServoPin);
  sweepServo1.attach(sweepServoPin1);
  sweepServo2.attach(sweepServoPin2);

  pinMode(modeButtonPin, INPUT_PULLUP);

  continuousServo.detach();  // Start OFF
  contAttached = false;
}

// ============================================================
// LOOP
// ============================================================
void loop() {

  handleButton();
  controlContinuousServo();
  sweepServoOne();
  sweepServoTwo();
}

// ============================================================
// BUTTON HANDLER (Cycle Speeds)
// ============================================================
void handleButton() {

  bool buttonState = digitalRead(modeButtonPin);

  // Detect button press (HIGH → LOW)
  if (lastButtonState == HIGH && buttonState == LOW) {

    speedMode++;
    if (speedMode > 5) speedMode = 0;

    delay(200);   // Simple debounce
  }

  lastButtonState = buttonState;
}

// ============================================================
// CONTINUOUS SERVO CONTROL
// ============================================================
void controlContinuousServo() {

  int speed = 0;

  switch (speedMode) {
    case 1: speed = 15; break;
    case 2: speed = 25; break;
    case 3: speed = 35; break;
    case 4: speed = 45; break;
    case 5: speed = 60; break;
    default: speed = 0; break;
  }

  if (speed > 0) {

    if (!contAttached) {
      continuousServo.attach(contServoPin);
      contAttached = true;
    }

    continuousServo.write(contStop + speed);
  }
  else {

    if (contAttached) {
      continuousServo.detach();  // Remove signal completely
      contAttached = false;
    }
  }
}

// ============================================================
// SWEEP SERVO 1 (0 ↔ 90)
// ============================================================
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

// ============================================================
// SWEEP SERVO 2 (90 ↔ 0)
// ============================================================
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
