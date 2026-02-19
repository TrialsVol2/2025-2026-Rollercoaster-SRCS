This file explains in a _minor_ amount of detail the standard operation procedures and the exceptions

**ASTM	11.2.8 When a different protocol occurs such as the automated forced stop, a warning will flash on the human-machine interface followed by a noise to grab the ride operator’s attention.**

**Have a system check protocol before starting ride functionality**<br>

_HMI Objectives_<br>
a. Buttons that control motors movement individually. Forwards and Backwards (possibly speed as a slide bar,like volume) as well as audio cues eg. ping, bell, alarm<br>
b. Differing windows as panes or titles. These windows cannot be closable**<br>

_Arduino Objectives_<br>
a. Save all of code up to this point<br>
b. create a module (block of code) that when pushing arduino button, switches direction of motor<br>
c. create a **DIFFERENT** module that when **HOLDING** arduino button, allows movement of motor in singular direction (this code should not allow opposite direction rotation)<br>

1. Standard Operation Procedure
2. **Automated Forced Stop Procedure**<br>
	a. Cease all lift hill motion<br>
	b. Bring riders into station without moving them forwards to the lift hill<br>
	c. Open exit gates but not the enterance gates.
5.
6. Sensor Failure Procedure<br>
  a. **Automated Forced Stop Procedure**<br>
  b. Ride Operator checks sensor integrity<br>
  c. Ride starts up without passengers for 1 lap<br>
  d. If sensors are working, then load riders and proceed as normal. if not, return to 4b.<br>
7. 
8. Motor failure
