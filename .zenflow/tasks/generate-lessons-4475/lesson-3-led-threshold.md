# Lesson 3: LED Distance Alert

## The Goal

In this lesson, we'll make an LED turn ON when something gets too close to the sensor! This is like a parking sensor in a car that beeps when you're getting too close to a wall.

## What You'll Need

- Your ESP32 with the distance sensor (from Lesson 2)
- 1 LED (any color you like!)
- 1 resistor (220 ohm or 330 ohm)
- 2 jumper wires
- Breadboard

## Understanding Thresholds

A **threshold** is like a limit or a line you shouldn't cross. Imagine:
- "If it's hotter than 30°C, turn on the fan"
- "If you score over 90%, you get an A"
- "If something is closer than 5cm, turn on the LED"

That last one is what we're building!

## Step 1: Add the LED

Keep all your sensor wires connected from Lesson 2, and add the LED:

1. Put the LED in your breadboard
2. The **long leg** (positive) connects to Pin 23 through a resistor
3. The **short leg** (negative) connects to GND

**Why do we need a resistor?** LEDs are like light bulbs but smaller. Too much power can burn them out! The resistor slows down the electricity to a safe amount.

## Step 2: Write the Code

Type this code (it builds on Lesson 2):

```cpp
const int TRIG_PIN = 13;
const int ECHO_PIN = 14;
const int LED_PIN = 23;
const int THRESHOLD_CM = 5;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);     // LED is an OUTPUT
  Serial.begin(9600);
  
  Serial.println("Distance Alert System Ready!");
}

void loop() {
  // Send a sound pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Listen for the echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  // Calculate distance
  int distance = duration * 0.034 / 2;
  
  // Check if something is too close
  if (distance > 0 && distance < THRESHOLD_CM) {
    digitalWrite(LED_PIN, HIGH);  // Turn LED ON
    Serial.print("⚠️  ALERT! Too close: ");
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn LED OFF
    Serial.print("✓ Safe distance: ");
  }
  
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(100);
}
```

### Understanding the New Code

**`const int LED_PIN = 23`** - This says Pin 23 controls the LED.

**`const int THRESHOLD_CM = 5`** - This sets our limit to 5 centimeters. Anything closer than 5cm triggers the alert!

**`pinMode(LED_PIN, OUTPUT)`** - We need to set the LED pin as an output so we can control it.

**The `if` Statement:**
```cpp
if (distance > 0 && distance < THRESHOLD_CM) {
    digitalWrite(LED_PIN, HIGH);
} else {
    digitalWrite(LED_PIN, LOW);
}
```

This is like making a decision! Let's break it down:

- **`if`** - "If this is true, do this"
- **`distance > 0`** - "The distance is more than 0" (makes sure we actually detected something)
- **`&&`** - Means "AND" (both things must be true)
- **`distance < THRESHOLD_CM`** - "The distance is less than our threshold (5cm)"
- **`digitalWrite(LED_PIN, HIGH)`** - If BOTH things are true, turn LED ON
- **`else`** - "Otherwise..."
- **`digitalWrite(LED_PIN, LOW)`** - If it's NOT true, turn LED OFF

Think of it like this:
```
IF (it's raining AND I'm going outside)
    Take an umbrella
ELSE
    Don't take an umbrella
```

## Step 3: Upload and Test

1. Click **Verify**
2. Click **Upload**
3. Open the **Serial Monitor**

Now try these:

1. **Put your hand far away** - LED should be OFF
2. **Move your hand closer** - When you get within 5cm, LED turns ON!
3. **Move away again** - LED turns OFF

Cool! You made a distance sensor with an alert!

## Step 4: Understanding the Logic

Here's what happens step by step:

1. 📏 **Measure distance** - Get distance from sensor
2. ❓ **Check condition** - Is it between 0 and 5cm?
3. ✅ **If YES** - Turn LED ON, show warning
4. ❌ **If NO** - Turn LED OFF, show safe message
5. 🔄 **Repeat** - Do it all again!

## Experiments to Try

### Experiment 1: Change the Threshold
Try changing `THRESHOLD_CM` from 5 to 10:
```cpp
const int THRESHOLD_CM = 10;
```
What happens? The LED now turns on when things are within 10cm instead of 5cm!

### Experiment 2: Reverse the Logic
What if you want the LED to be ON when things are FAR and OFF when things are close? Change the condition:
```cpp
if (distance > 0 && distance > THRESHOLD_CM) {  // Changed < to >
    digitalWrite(LED_PIN, HIGH);
} else {
    digitalWrite(LED_PIN, LOW);
}
```

### Experiment 3: Two Thresholds
Want a "warning zone"? Try this:
```cpp
const int CLOSE_THRESHOLD = 5;
const int FAR_THRESHOLD = 10;

if (distance > 0 && distance < CLOSE_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    Serial.print("🚨 DANGER - Too close!");
} else if (distance >= CLOSE_THRESHOLD && distance < FAR_THRESHOLD) {
    // Blink the LED for warning
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);
    delay(50);
    Serial.print("⚠️  WARNING - Getting close!");
} else {
    digitalWrite(LED_PIN, LOW);
    Serial.print("✓ Safe");
}
```

## Troubleshooting

**LED always ON or always OFF?**
- Check the LED connections (long leg to pin 23 through resistor, short leg to GND)
- Make sure the resistor is in place
- Try switching the LED legs (it might be backwards)

**LED very dim?**
- You might need a smaller resistor (but don't go below 220 ohm)

**Serial Monitor shows weird distances?**
- Review Lesson 2 troubleshooting

## Real-World Applications

This same idea is used in:
- 🚗 **Parking sensors** in cars
- 🚪 **Automatic doors** at stores
- 🤖 **Robot obstacle avoidance**
- 🔒 **Security systems**

## What You Learned

- What a threshold is and how to use it
- How to connect and control an LED with code
- How to use `if` and `else` statements to make decisions
- How to check if something is in a certain range
- The `&&` operator means "AND" in code

Fantastic! In Lesson 4, we'll add a servo motor that moves based on the distance!
