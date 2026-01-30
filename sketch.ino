const int TRIG_PIN = 13;     // Keep as is
const int ECHO_PIN = 14;     // Changed from 12 (safe pin)
const int OPTA_SIGNAL = 23;
const int THRESHOLD_CM = 5;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(OPTA_SIGNAL, OUTPUT);
  Serial.begin(9600);
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
  
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}