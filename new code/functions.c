/*
  There is a bunch of function overloading here. That's when you make multiple functions with the same name.
  Don't panic! Just call the version of the function that you want and you're good.
  e.g. If you want to move forward at speed 5 for 5 seconds, call forward(5,5).
  And If you want to just start moving forward at speed 5, call forward(5).
*/

int abs(int number) {
  if(number > 0) {
    return number;
  }
  return -number;
}

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


//Function to pick up a pipe from anyside of the robot. 1 for rightside. -1 for leftside. 0 for front and 2 or -2 for backside. This code will also return the robot to its position before the function was applied.
void pipePickUp(int direction) //direction is for where the pipe/train cart is relative to the robot. -2 = behind the robot. -1 = left of the robot. 0 = front of the robot. 1 = right of the robot.
{
  //A: Move forward until robot's center of rotation is inline with the pipe.
  forward(15,1000); //ADJUST
  //B: Turn 90*direction degrees clockwise.
  turn(90*direction);
  //C: Move forward until ultrasonic sensor detects pipe. Save time taken.
  ClearTimer(T1);
  while(SensorValue[sonarFront] > 3)
  {
    forward(20);
  }
  int timeTaken = time1[T1];
  stop();
  //D: Close claw nowholding the pipe.
  setClawState('c');
  //E: Move backward for time taken.
  backward(20,timeTaken);
  //F: Turn 90*direction degrees counterclockwise.
  turn(-90*direction);
}

void pipePlaceDown(int direction, int position) //1 = back of train cart. 2 = front of train cart. 3 = top of train cart.
//Notes:
//- -27 degrees for 1 and 2. -17 degrees for 3.
//- may be better to let go by turning instead of backing away for 3.
{
  backward(30*direction, 1000); //Adjust time.
  turn(90*direction);
  int angle = 0;
  int length = 0;
  switch(position)
  {
    case 1:
    angle = -27;
    length = 2500; //Adjust
    break;

    case 2:
    angle = -27;
    length = 2000; //Adjust
    break;

    case 3:
    angle = -17;
    length = 2250;
    break;
  }
  turnClaw(-90);
  forward(15,length);
  moveArm(angle);
  setClawState('o');
  backward(15, length);
  moveArm(angle);
  turn(-90*direction);
  forward(30*direction, 1000); //Adjust time.
  turnClaw(90);
}
