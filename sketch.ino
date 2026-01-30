#include <ESP32Servo.h>

const int TRIG_PIN = 13;
const int ECHO_PIN = 14;
const int OPTA_SIGNAL = 23;
const int THRESHOLD_CM = 5;

const int SERVO_PIN = 15;
const int MAX_DISTANCE = 50;

Servo myServo;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(OPTA_SIGNAL, OUTPUT);
  Serial.begin(9600);
  
  myServo.attach(SERVO_PIN);
  
  Serial.println("Servo initialized on pin 15");
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int distance = duration * 0.034 / 2;
  
  digitalWrite(OPTA_SIGNAL, (distance > 0 && distance < THRESHOLD_CM));
  
  int servoAngle = map(constrain(distance, 0, MAX_DISTANCE), 0, MAX_DISTANCE, 180, 0);
  myServo.write(servoAngle);
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Servo Angle: ");
  Serial.println(servoAngle);
  delay(100);
}