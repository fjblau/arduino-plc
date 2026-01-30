# Lesson 2: Using the Ultrasonic Distance Sensor

## What is an Ultrasonic Distance Sensor?

An ultrasonic sensor is like a bat! Bats make sounds we can't hear and listen for echoes to find things in the dark. The sensor does the same thing - it sends out sound waves and measures how long they take to bounce back. This tells us how far away something is!

## What You'll Need

- ESP32 board (from Lesson 1)
- Ultrasonic distance sensor (HC-SR04)
- 4 jumper wires
- Breadboard (optional, makes connecting easier)

## Understanding Your Sensor

Your ultrasonic sensor has 4 pins:

- **VCC** - Power (needs 5V)
- **TRIG** - Trigger pin (we send the signal from here)
- **ECHO** - Echo pin (we receive the signal here)
- **GND** - Ground (completes the circuit)

## Step 1: Connect the Distance Sensor

Connect the wires like this:

| Sensor Pin | ESP32 Pin |
|------------|-----------|
| VCC        | 5V        |
| GND        | GND       |
| TRIG       | Pin 13    |
| ECHO       | Pin 14    |

**Important:** Make sure the connections are firm! Loose wires are the #1 cause of problems.

## Step 2: Write the Code

Type this code into Arduino IDE:

```cpp
const int TRIG_PIN = 13;
const int ECHO_PIN = 14;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);  // TRIG sends signals OUT
  pinMode(ECHO_PIN, INPUT);   // ECHO receives signals IN
  Serial.begin(9600);         // Start talking to computer
  
  Serial.println("Distance Sensor Ready!");
}

void loop() {
  // Send a sound pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);        // Wait 2 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);       // Send pulse for 10 microseconds
  digitalWrite(TRIG_PIN, LOW);
  
  // Listen for the echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  // Calculate distance
  int distance = duration * 0.034 / 2;
  
  // Display the distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(100);  // Wait a bit before measuring again
}
```

### Understanding the Code

**`const int TRIG_PIN = 13`** - The word `const` means this number never changes. We're saying "Pin 13 is ALWAYS for TRIG."

**`pinMode(TRIG_PIN, OUTPUT)`** - TRIG sends signals OUT (like yelling into a canyon).

**`pinMode(ECHO_PIN, INPUT)`** - ECHO receives signals IN (like listening for the echo).

**`delayMicroseconds(2)`** - Wait for 2 microseconds. A microsecond is REALLY tiny - one millionth of a second!

**Sending the Pulse:**
```cpp
digitalWrite(TRIG_PIN, LOW);   // Make sure it's off first
delayMicroseconds(2);          // Wait a tiny bit
digitalWrite(TRIG_PIN, HIGH);  // Turn it ON
delayMicroseconds(10);         // Keep it on for 10 microseconds
digitalWrite(TRIG_PIN, LOW);   // Turn it OFF
```
This sends a quick sound pulse, like making a "click" sound.

**`long duration = pulseIn(ECHO_PIN, HIGH, 30000)`** - This waits for the echo to come back and measures how long it took (in microseconds). The `30000` means "give up after 30,000 microseconds if nothing comes back."

**`int distance = duration * 0.034 / 2`** - This is the magic math!
- Sound travels at 0.034 cm per microsecond
- We divide by 2 because the sound goes TO the object AND back (that's twice the distance)

**`Serial.print()` and `Serial.println()`** - These send messages to your computer so you can see the distance!

## Step 3: Upload and Test

1. Click **Verify** (checkmark button)
2. Click **Upload** (arrow button)
3. Open the **Serial Monitor** by clicking the magnifying glass icon in the top right
4. Make sure it's set to **9600 baud** at the bottom

You should see distances appearing!

## Step 4: Experiment!

Try these fun experiments:

1. **Wave your hand** in front of the sensor - watch the numbers change!
2. **Put a book** at different distances - does it measure correctly?
3. **Point it at a wall** - how far away is the wall?
4. **What's the farthest** it can measure?
5. **What's the closest** it can measure?

## How Distance Measurement Works

Think of it like this:

1. 🔊 **ESP32 says:** "Trigger, send a sound!"
2. 📡 **Sensor sends:** Sound waves fly out
3. 📦 **Sound hits:** An object and bounces back
4. 👂 **Echo hears:** The returning sound
5. ⏱️ **ESP32 measures:** How long it took
6. 🧮 **ESP32 calculates:** Distance = Time × Speed ÷ 2

## Troubleshooting

**Getting 0 cm all the time?**
- Check your wires - especially TRIG and ECHO
- Make sure VCC is connected to 5V (not 3.3V)

**Getting weird random numbers?**
- Make sure there's something in front of the sensor (not too close, not too far)
- The sensor works best between 2cm and 400cm

**Nothing showing up?**
- Make sure Serial Monitor is open
- Check that baud rate is 9600

## Challenge

Can you measure the width of your desk? How about the height of a water bottle?

## What You Learned

- How ultrasonic sensors work (like bat echolocation!)
- How to connect a sensor to your ESP32
- How to read sensor data
- How to calculate distance from time
- How to display information on the Serial Monitor

Amazing work! In Lesson 3, we'll make an LED light up when something gets too close!
