/*
 * ESP32 Firmware — Robotic Arm Controller
 * 
 * Receives 34-byte UART command packets from PC-side VB.NET GUI
 * and drives 16 servo motors via PCA9685 PWM driver over I2C.
 * 
 * Hardware:
 *   - ESP32 (main controller)
 *   - PCA9685 (16-channel, 12-bit PWM driver)
 *   - VTS-08A / SG90 servo motors
 * 
 * Connections:
 *   - GPIO21 → PCA9685 SDA
 *   - GPIO22 → PCA9685 SCL
 *   - Serial @ 115200 bps for PC communication
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// PCA9685 default I2C address
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  // Initialize serial for PC communication
  Serial.begin(115200);
  Serial.println("PCA9685 Servo Controller Starting...");

  // Initialize I2C on ESP32 default pins
  Wire.begin(21, 22);           // SDA=21, SCL=22

  // Initialize PCA9685
  pwm.begin();
  pwm.setPWMFreq(50);            // 50 Hz for standard hobby servos

  Serial.println("Setup complete. Waiting for servo data...");
}

void loop() {
  // Wait for full 34-byte packet from PC
  if (Serial.available() >= 34) {
    uint8_t buffer[34];
    Serial.readBytes(buffer, 34);

    // Verify start byte and command ID
    if (buffer[0] == 0xAA && buffer[1] == 0x0A) {
      Serial.println("Valid packet received:");

      // Process all 16 servo channels
      for (int i = 0; i < 16; i++) {
        int lsb = buffer[2 + (i * 2)];
        int msb = buffer[3 + (i * 2)];
        int pulse = (msb << 8) | lsb;   // Combine LSB + MSB → microseconds

        if (pulse > 0) {
          // Convert microseconds → PCA9685 12-bit value (102-491)
          int pwm_val = map(pulse, 500, 2400, 102, 491);
          pwm.setPWM(i, 0, pwm_val);

          Serial.print("CH");
          Serial.print(i);
          Serial.print(": pulse=");
          Serial.print(pulse);
          Serial.print("us -> pwm_val=");
          Serial.println(pwm_val);
        }
      }
    } else {
      Serial.println("Invalid packet header. Ignored.");
    }
  }
}
