# 🤖 Robotic Arm Controller

A 5-DOF (Degrees of Freedom) robotic arm control system designed for industrial pick-and-place operations. The system combines an ESP32 microcontroller, PCA9685 PWM driver, and a custom VB.NET desktop GUI to enable precise, programmable control of up to 16 servo motors via UART and I2C protocols.

**Author:** Venu S  
**Project Type:** Personal / Academic Project  
**Duration:** Apr 2025 – Aug 2025

---

## 🎯 Project Highlights

- **5-DOF robotic arm** using ESP32 + PCA9685 + VTS-08A/SG90 servos
- **Custom VB.NET GUI** for manual control, motion sequencing, and Arduino code export
- **Layered communication protocols**: UART (PC ↔ ESP32) + I2C (ESP32 ↔ PCA9685)
- **16-channel PWM control** with 12-bit resolution via PCA9685
- **Offline sequence execution** — arm runs autonomously without PC after flashing

---

## 🏗 System Architecture

### Block Diagram

![Block Diagram](docs/block_diagram.png)

**Data flow:**
