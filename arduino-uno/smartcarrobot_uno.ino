#include <AFMotor.h> //import your motor shield library

AF_DCMotor motor1(1,MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor2(2, MOTOR12_64KHZ);

void setup() {
  Serial.begin(9600);
  motor1.setSpeed(250); //set the speed of the motors, between 0-255
  motor2.setSpeed (250); 
}

void loop() {
  if (Serial.available()){
    int inByte = Serial.read();
    if(inByte=='F'){
      motor1.run(FORWARD);  motor2.run(FORWARD);
      delay (250);
      motor1.run(RELEASE);  motor2.run(RELEASE);
    }
    if(inByte=='B'){
      motor1.run(BACKWARD); motor2.run(BACKWARD);
      delay (250);
      motor1.run(RELEASE);  motor2.run(RELEASE);
    }
    if(inByte=='R'){
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      delay (250);
      motor1.run(RELEASE);
      motor2.run(RELEASE);
    }
    if(inByte=='L'){
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      delay (250);
      motor1.run(RELEASE);
      motor2.run(RELEASE);
    }
  }
}
