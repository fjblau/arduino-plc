# Lesson 4: Servo Motor Distance Indicator

## The Goal

In this final lesson, we'll add a servo motor that moves like a dial or pointer, showing how far away something is! When something is close, it points one way. When it's far, it points the other way. It's like a fuel gauge in a car!

## What is a Servo Motor?

A servo motor is a special motor that can move to specific positions. Unlike a regular motor that just spins and spins, a servo can move to exact angles between 0° and 180°.

- **0°** - All the way to one side
- **90°** - In the middle
- **180°** - All the way to the other side

## What You'll Need

- Your ESP32 with distance sensor and LED (from Lesson 3)
- 1 Servo motor
- 3 jumper wires
- (Optional) A small paper arrow or pointer to attach to the servo

## Step 1: Connect the Servo Motor

Keep everything from Lesson 3 connected, and add the servo:

Servo motors have 3 wires:
- **Brown or Black** - Ground (GND)
- **Red** - Power (5V)
- **Orange or Yellow** - Signal (Pin 15)

Connect like this:

| Servo Wire | ESP32 Pin |
|------------|-----------|
| Brown/Black| GND       |
| Red        | 5V        |
| Orange/Yellow | Pin 15 |

## Step 2: Install the Servo Library

Before coding, we need to install a special library:

1. Go to **Sketch** → **Include Library** → **Manage Libraries**
2. Search for "ESP32Servo"
3. Click **Install** on "ESP32Servo by Kevin Harrington"
4. Close the Library Manager

Libraries are like instruction booklets that make controlling things easier!

## Step 3: Write the Complete Code

Here's the complete code combining everything from all 4 lessons:

```cpp
#include <ESP32Servo.h>

const int TRIG_PIN = 13;
const int ECHO_PIN = 14;
const int LED_PIN = 23;
const int THRESHOLD_CM = 5;

const int SERVO_PIN = 15;
const int MAX_DISTANCE = 20;

Servo myServo;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  
  myServo.attach(SERVO_PIN);
  
  Serial.println("Complete Distance System Ready!");
}

void loop() {
  // Measure distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int distance = duration * 0.034 / 2;
  
  // Control LED based on threshold
  if (distance > 0 && distance < THRESHOLD_CM) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
  // Control servo based on distance
  int servoAngle = map(constrain(distance, 0, MAX_DISTANCE), 0, MAX_DISTANCE, 180, 0);
  myServo.write(servoAngle);
  
  // Display information
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Servo Angle: ");
  Serial.println(servoAngle);
  
  delay(100);
}
```

### Understanding the New Code

**`#include <ESP32Servo.h>`** - This brings in the servo library we installed. It's like bringing a tool from your toolbox!

**`const int SERVO_PIN = 15`** - Pin 15 controls the servo.

**`const int MAX_DISTANCE = 20`** - We'll use 20cm as the farthest distance we care about.

**`Servo myServo`** - This creates a servo object called `myServo`. It's like giving your servo a name!

**`myServo.attach(SERVO_PIN)`** - This connects our servo to Pin 15 in the code.

**The Magic Line:**
```cpp
int servoAngle = map(constrain(distance, 0, MAX_DISTANCE), 0, MAX_DISTANCE, 180, 0);
```

Whoa! This looks complicated, but let's break it into pieces:

**`constrain(distance, 0, MAX_DISTANCE)`** - This keeps the distance between 0 and 20cm.
- If distance is 5, it stays 5
- If distance is 25, it becomes 20 (max)
- If distance is -2, it becomes 0 (min)

**`map(value, 0, MAX_DISTANCE, 180, 0)`** - This is SUPER cool! It converts one range to another:
- When distance is 0cm → servo goes to 180°
- When distance is 20cm → servo goes to 0°
- When distance is 10cm (middle) → servo goes to 90°

Think of it like this:
```
Distance Range: 0 -------- 10 -------- 20 cm
Servo Angle:    180° ----- 90° ------ 0°
```

Notice it's backwards! When something is CLOSE (0cm), servo is at 180°. When it's FAR (20cm), servo is at 0°. This makes it point like a gauge!

**`myServo.write(servoAngle)`** - This tells the servo to move to that angle.

## Step 4: Upload and Test

1. Click **Verify**
2. Click **Upload**
3. Open **Serial Monitor**

Watch your servo move as you move your hand closer and farther!

## How It All Works Together

Here's the complete system:

1. 📏 **Measure** - Ultrasonic sensor measures distance
2. 💡 **LED Alert** - If closer than 5cm, LED turns ON
3. 🎯 **Servo Movement** - Servo moves to show exact distance
4. 📊 **Display** - Serial Monitor shows distance and angle
5. 🔄 **Repeat** - Does this 10 times per second

## Understanding the `map()` Function

The `map()` function is like a translator. Here's how it works:

```cpp
map(value, fromLow, fromHigh, toLow, toHigh)
```

**Example 1:** Convert distance 0-20cm to angle 180-0°
```cpp
map(10, 0, 20, 180, 0)  // Returns 90
```
- 10 is halfway between 0 and 20
- So the answer is halfway between 180 and 0
- Halfway is 90!

**Example 2:** Convert distance to a score
```cpp
map(15, 0, 20, 0, 100)  // Returns 75
```
- 15cm out of 20cm = 75 out of 100!

## Experiments to Try

### Experiment 1: Reverse the Servo
Want the servo to point the other way? Swap the 180 and 0:
```cpp
int servoAngle = map(constrain(distance, 0, MAX_DISTANCE), 0, MAX_DISTANCE, 0, 180);
```

### Experiment 2: Change the Range
Want to measure up to 30cm instead of 20cm?
```cpp
const int MAX_DISTANCE = 30;
```

### Experiment 3: Make It Smoother
Want the servo to move more smoothly? Add this before `myServo.write()`:
```cpp
static int lastAngle = 90;
servoAngle = (lastAngle + servoAngle) / 2;  // Average with last position
lastAngle = servoAngle;
myServo.write(servoAngle);
```

### Experiment 4: Add a Pointer
Attach a small paper arrow to your servo with tape. Draw a scale on paper:
```
FAR          MEDIUM          CLOSE
0cm          10cm            20cm
```
Now you have a real distance gauge!

## Troubleshooting

**Servo not moving?**
- Check the 3 wire connections
- Make sure the signal wire is on Pin 15
- Try uploading the code again

**Servo jittering or shaking?**
- This is normal! Servos sometimes shake a little
- Make sure your distance readings are stable
- Try the "smoother" experiment above

**Servo moving backward?**
- The 180 and 0 in the map function might need to be swapped

## Real-World Applications

This project teaches skills used in:
- 📊 **Dashboard gauges** in cars and airplanes
- 🎮 **Video game controllers** (joysticks use similar sensors)
- 🦾 **Robot arms** that need to position precisely
- 🎯 **Camera systems** that track and follow objects
- 🏭 **Factory automation** for sorting and positioning

## What You Learned

- How servo motors work and how to control them
- How to install and use libraries in Arduino
- How to use the `map()` function to convert ranges
- How to use the `constrain()` function to limit values
- How to combine multiple components (sensor, LED, servo) into one system
- How to create a visual indicator of sensor data

## Amazing Work!

Congratulations! You've completed all 4 lessons and built a complete distance measurement system with:
- ✅ ESP32 microcontroller
- ✅ Ultrasonic distance sensor
- ✅ LED threshold alert
- ✅ Servo motor indicator

You now know how to:
- Read sensors
- Make decisions with code
- Control outputs (LEDs and motors)
- Display information
- Combine everything into a working system

These are the fundamental skills of robotics and electronics. Keep experimenting and building!

## Next Steps

Here are some ideas for what to build next:
- Add a buzzer that beeps when something is close
- Add more LEDs that light up at different distances
- Use buttons to change the threshold
- Make it battery powered and portable
- Add an LCD screen to display the distance

Keep learning and have fun building!
