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

const int accelButtonPin = 2;   // Hold to accelerate

// ----------------------------
// Continuous Servo Settings
// ----------------------------
int contStop = 90;          // Adjust 88–92 if creeping

int currentSpeed = 0;       
int maxSpeed = 90;          // Full forward (90 + 90 = 180)

// Separate ramp settings
int accelStepUp = 1;        // Faster acceleration
int accelStepDown = 1;      // Slower deceleration

unsigned long accelIntervalUp = 50;    // Fast ramp up
unsigned long accelIntervalDown = 60;  // Slow ramp down

unsigned long previousMillis = 0;
bool contAttached = false;

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

  pinMode(accelButtonPin, INPUT_PULLUP);

  continuousServo.detach();  
  contAttached = false;
}

// ============================================================
// LOOP
// ============================================================
void loop() {

  handleSpeedControl();
  controlContinuousServo();
  sweepServoOne();
  sweepServoTwo();
}

// ============================================================
// SPEED CONTROL (Fast Up, Slow Down)
// ============================================================
void handleSpeedControl() {

  unsigned long currentMillis = millis();
  bool buttonPressed = digitalRead(accelButtonPin) == LOW;

  if (buttonPressed) {
    if (currentMillis - previousMillis >= accelIntervalUp) {
      previousMillis = currentMillis;

      if (currentSpeed < maxSpeed) {
        currentSpeed += accelStepUp;
      }
    }
  }
  else {
    if (currentMillis - previousMillis >= accelIntervalDown) {
      previousMillis = currentMillis;

      if (currentSpeed > 0) {
        currentSpeed -= accelStepDown;
      }
    }
  }

  currentSpeed = constrain(currentSpeed, 0, maxSpeed);
}

// ============================================================
// CONTINUOUS SERVO CONTROL
// ============================================================
void controlContinuousServo() {

  if (currentSpeed > 0) {

    if (!contAttached) {
      continuousServo.attach(contServoPin);
      contAttached = true;
    }

    continuousServo.write(contStop + currentSpeed);
  }
  else {
    if (contAttached) {
      continuousServo.detach();
      contAttached = false;
    }
  }
}

// ============================================================
// SWEEP SERVO 1
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
// SWEEP SERVO 2
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