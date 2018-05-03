/*
  There is a bunch of function overloading here. That's when you make multiple functions with the same name.
  Don't panic! Just call the version of the function that you want and you're good.
  e.g. If you want to move forward at speed 5 for 5 seconds, call forward(5,5).
  And If you want to just start moving forward at speed 5, call forward(5).
*/
void stop(int time) { // stop for some time
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	motor[armMotor] = 0;
	wait1Msec(time);
}

void stop() { // just stop
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	motor[armMotor] = 0;
}

void forward(int speed, int time) { // move forward at some speed for some time
	motor[leftMotor] = speed;
	motor[rightMotor] = speed;
	wait1Msec(time);
}

void forward(int speed) { // just move forward
	motor[leftMotor] = speed;
	motor[rightMotor] = speed;
}

void backward(int speed, int time) { // move backward at some speed for some time
	motor[leftMotor] = -speed;
	motor[rightMotor] = -speed;
	wait1Msec(time);
	stop();
}

void backward(int speed) { // just move backward
	motor[leftMotor] = -speed;
	motor[rightMotor] = -speed;
}

void turn(int angle) {
  int turnSpeed = 32 * (angle / abs(angle));
  motor[leftMotor] = turnSpeed;
  motor[rightMotor] = -turnSpeed;
  wait1Msec(angle * 12);
  stop();
}

void moveArm(int angle) { // angle is in degrees, clockwise if you look at the robot from its left side
	motor[armMotor] = 32;
	wait1Msec((int) (angle * (float) (2500 / 45)));
	stop();
}

void turnClaw(int angle) { // angle is in degrees, clockwise from the robot's perspective
  motor[wristServo] = angle / 180 * 127;
}

void setClawState(char state) { // opens/closes the claw
  if(state == 'o') {
    motor[clawServo] = 127;
  } else if(state == 'c') {
    motor[clawServo] = -127;
  }
}

int abs(int number) {
	if(number > 0) {
		return number;
	}
	return -number;
}