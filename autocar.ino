#include <Servo.h>

Servo servo;

int trigPin = 8;
int echoPin = 9;
int IN1 = 2;  // Motor 1
int IN2 = 3;  // Motor 1
int IN3 = 4;  // Motor 2
int IN4 = 5;  // Motor 2

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  servo.attach(10); // Servo on pin 10
  servo.write(90);
  delay(500);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  int frontDist = getDistance();
  int leftDist, rightDist;
  
  servo.write(45);
  delay(500);
  leftDist = getDistance();
  
  servo.write(135);
  delay(500);
  rightDist = getDistance();
  
  servo.write(90);
  delay(500);
  
  if (frontDist > 20) {
    moveForward();
  } else {
    if (leftDist > rightDist) {
      turnLeft();
      delay(1000);
      moveForward();
      delay(1000);
      turnRight();
      delay(1000);
    } else {
      turnRight();
      delay(1000);
      moveForward();
      delay(1000);
      turnLeft();
      delay(1000);
    }
  }
  
  stopMotors();
}
