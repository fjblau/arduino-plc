# Lesson 1: Getting Started with ESP32 and Blink Test

## What is an ESP32?

The ESP32 is like a tiny computer that can control lights, motors, sensors, and many other things! It's about the size of a stick of gum but powerful enough to make awesome projects.

## What You'll Need

- ESP32 board
- USB cable (to connect to your computer)
- Computer with Arduino IDE installed
- An LED (built into most ESP32 boards)

## Step 1: Install the Arduino IDE

1. Download Arduino IDE from arduino.cc
2. Install it on your computer
3. Open the Arduino IDE

## Step 2: Add ESP32 Support

1. Click on **File** → **Preferences**
2. In "Additional Board Manager URLs", paste this:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
3. Click **OK**
4. Go to **Tools** → **Board** → **Boards Manager**
5. Search for "ESP32" and click **Install**

## Step 3: Connect Your ESP32

1. Plug the USB cable into your ESP32
2. Plug the other end into your computer
3. In Arduino IDE, go to **Tools** → **Board** and select your ESP32 model
4. Go to **Tools** → **Port** and select the port that shows your ESP32

## Step 4: Your First Program - Blink!

Let's make a light blink on and off! Type this code into Arduino IDE:

```cpp
void setup() {
  pinMode(2, OUTPUT);  // Pin 2 controls the LED
  Serial.begin(9600);  // Start communication at 9600 speed
}

void loop() {
  digitalWrite(2, HIGH);  // Turn LED ON
  delay(1000);            // Wait 1 second
  digitalWrite(2, LOW);   // Turn LED OFF
  delay(1000);            // Wait 1 second
}
```

### Understanding the Code

**`void setup()`** - This runs once when you start your ESP32. It's like getting ready before a game!

**`pinMode(2, OUTPUT)`** - This tells pin 2 that we want to send signals OUT to control something (the LED).

**`Serial.begin(9600)`** - This lets your ESP32 talk to your computer. The number 9600 is the speed.

**`void loop()`** - This runs over and over again, forever! Like riding in circles on your bike.

**`digitalWrite(2, HIGH)`** - Sends power to pin 2, turning the LED ON.

**`delay(1000)`** - Wait for 1000 milliseconds (1 second). Like counting "one Mississippi."

**`digitalWrite(2, LOW)`** - Stops sending power to pin 2, turning the LED OFF.

## Step 5: Upload Your Code

1. Click the **checkmark** button (Verify) - this checks for mistakes
2. Click the **arrow** button (Upload) - this sends your code to the ESP32
3. Wait for "Done uploading" message
4. Watch your LED blink!

## Troubleshooting

**LED not blinking?**
- Check if you selected the right board and port
- Some ESP32 boards use a different pin (try pin 13 or 5 instead of 2)

**Upload failed?**
- Try unplugging and plugging in the USB cable again
- Press the "BOOT" button on your ESP32 while uploading

## Challenge

Can you make the LED blink faster? Try changing the `delay(1000)` to `delay(500)`. What happens?

## What You Learned

- How to install and set up Arduino IDE for ESP32
- How to connect your ESP32 to your computer
- What `setup()` and `loop()` do
- How to turn an LED on and off
- How to upload code to your ESP32

Great job! You're now ready for Lesson 2 where we'll use a distance sensor!
