# Technical Specification: Add Servo Motor Control to sketch.ino

## Task Difficulty: Medium

**Reasoning**: Requires I2C communication with PWM board, servo library integration, and coordination with existing ultrasonic sensor logic. Moderate complexity with some edge cases to consider.

---

## Technical Context

### Language & Platform
- **Language**: Arduino C++ (sketch.ino)
- **Platform**: ESP32 (based on pin assignments: GPIO 13, 14, 23)
- **Dependencies Required**:
  - `Wire.h` - I2C communication (built-in)
  - `Adafruit_PWMServoDriver.h` - PCA9685 PWM board control (needs installation)

### Current Implementation
The sketch currently:
- Uses HC-SR04 ultrasonic sensor (TRIG_PIN: 13, ECHO_PIN: 14)
- Measures distance and triggers OPTA_SIGNAL (GPIO 23) when distance < 5cm
- Outputs distance readings via Serial at 9600 baud
- 100ms loop delay

---

## Implementation Approach

### Servo Control Strategy
**Assumption**: Servo angle controlled proportionally by distance measurement

- **Distance range**: 0-50cm (configurable)
- **Servo angle range**: 0-180 degrees
- **Mapping**: Distance inversely proportional to servo angle
  - 0cm → 180° (closest = max angle)
  - 50cm+ → 0° (far = min angle)

### PWM Board Configuration
**Hardware**: PCA9685 16-Channel 12-bit PWM/Servo Driver
- **I2C Address**: 0x40 (default)
- **I2C Pins** (ESP32 default):
  - SDA: GPIO 21
  - SCL: GPIO 22
- **PWM Frequency**: 50 Hz (standard for servos)
- **Servo Channel**: Channel 0 (configurable)

### Integration Points
1. Initialize I2C and PWM board in `setup()`
2. Map distance to servo angle in `loop()`
3. Update servo position via PWM board
4. Maintain existing ultrasonic sensor and OPTA_SIGNAL functionality

---

## Source Code Structure Changes

### Files Modified
- **sketch.ino**: Add servo control logic

### Code Additions
1. **Library includes**:
   ```cpp
   #include <Wire.h>
   #include <Adafruit_PWMServoDriver.h>
   ```

2. **Constants**:
   ```cpp
   const int SERVO_CHANNEL = 0;
   const int SERVO_MIN_PULSE = 150;  // ~0 degrees
   const int SERVO_MAX_PULSE = 600;  // ~180 degrees
   const int MAX_DISTANCE = 50;       // cm
   ```

3. **Global objects**:
   ```cpp
   Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
   ```

4. **Setup additions**:
   - Initialize I2C: `Wire.begin()`
   - Initialize PWM: `pwm.begin()`
   - Set PWM frequency: `pwm.setPWMFreq(50)`

5. **Loop additions**:
   - Map distance to servo angle
   - Convert angle to PWM pulse width
   - Update servo via `pwm.setPWM()`

---

## Data Model / API / Interface Changes

### Configuration Parameters (tunable)
- `SERVO_CHANNEL`: Which PWM board channel (0-15)
- `SERVO_MIN_PULSE`: Minimum pulse length (typically 150-200)
- `SERVO_MAX_PULSE`: Maximum pulse length (typically 550-600)
- `MAX_DISTANCE`: Maximum distance for servo mapping (cm)

### Function Additions
Option to add helper function:
```cpp
void setServoAngle(uint8_t channel, int angle)
```

---

## Dependencies

### Required Library Installation
**Adafruit PWM Servo Driver Library**
- Install via Arduino Library Manager: "Adafruit PWM Servo Driver Library"
- Or manually from: https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library

**Note**: Cannot verify installation automatically as this is Arduino sketch. User must install via Arduino IDE.

---

## Verification Approach

### Hardware Testing
Since this is Arduino firmware:
1. **Compilation**: Verify sketch compiles without errors in Arduino IDE
2. **Upload**: Flash to ESP32 board
3. **Manual Testing**:
   - Verify I2C connection to PCA9685 (check Serial output)
   - Test servo movement at different distances
   - Confirm existing ultrasonic sensor still works
   - Verify OPTA_SIGNAL still triggers correctly

### Test Cases
1. **No object**: Servo at 0° (or minimum angle)
2. **Object at 5cm**: Servo at ~162° + OPTA_SIGNAL HIGH
3. **Object at 25cm**: Servo at ~90°
4. **Object at 0cm**: Servo at 180° + OPTA_SIGNAL HIGH
5. **Serial output**: Distance readings still displayed

### Error Handling
- I2C initialization failure: Add Serial debug output
- Servo limits: Constrain angles to 0-180°
- Distance reading errors: Handle 0 or timeout values gracefully

---

## Open Questions

1. **PWM Board Model**: Assuming PCA9685 - confirm if different model needed
2. **Servo Behavior**: Assuming distance-based control - confirm if different logic needed
3. **Servo Angle Mapping**: Inverse proportional assumed - confirm direction preference
4. **Multiple Servos**: Single servo assumed - specify if multiple servos needed

---

## Risk Assessment

**Low Risk**:
- Library is well-established and stable
- I2C pins (21/22) don't conflict with existing pins (13/14/23)
- PWM board handles servo timing independently

**Potential Issues**:
- I2C wiring errors (most common issue)
- Servo power supply (servos need separate 5V power, not from board)
- Pulse width calibration for specific servo model

---

## Next Steps

1. Confirm assumptions with user (PWM board model, servo behavior)
2. Implement changes to sketch.ino
3. Document required hardware connections
4. Provide compilation and upload instructions
