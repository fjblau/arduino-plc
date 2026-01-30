#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const int TRIG_PIN = 13;
const int ECHO_PIN = 14;
const int OPTA_SIGNAL = 23;
const int THRESHOLD_CM = 5;

const int SERVO_CHANNEL = 0;
const int SERVO_MIN_PULSE = 150;
const int SERVO_MAX_PULSE = 600;
const int MAX_DISTANCE = 50;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(OPTA_SIGNAL, OUTPUT);
  Serial.begin(9600);
  
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);
  
  Serial.println("PWM board initialized");
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
  int pulselen = map(servoAngle, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  pwm.setPWM(SERVO_CHANNEL, 0, pulselen);
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Servo Angle: ");
  Serial.println(servoAngle);
  delay(100);
}