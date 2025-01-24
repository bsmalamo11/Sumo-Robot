# Sumo Robot Project

This repository contains the design, code, and implementation details for a sumo robot controlled by an **ESP32** microcontroller. The robot is designed to compete in sumo matches with advanced features such as obstacle detection, wireless control, and precise motor movement.

---

## Features
- **Microcontroller**: ESP32 for wireless communication and control.
- **Motion Control**: DC motors with L298 motor driver.
- **Obstacle Avoidance**: Infrared (IR) sensors.
- **Wireless Control**: Controlled using a PlayStation controller.
- **Chassis Design**: Custom 3D-printed frame for optimized weight and structure.

---

## Components
### Hardware
1. **ESP32**: The main microcontroller for handling wireless communication and robot logic.
2. **DC Motors**: High-torque motors for movement and pushing opponents.
3. **L298 Motor Driver Module**: To control motor direction and speed.
4. **IR Sensors**: For obstacle detection and edge detection.
5. **3D-Printed Chassis**: Designed in SolidWorks and printed for durability and lightweight construction.
6. **PlayStation Controller**: For precise and user-friendly wireless control.
7. **Battery**: Supplies power to all components.

### Software
- **ESP32 Code**: Written in Arduino IDE to control the robot's functionality.
- **Wireless Communication**: The ESP32 handles Bluetooth signals from the PlayStation controller.

---

## Design
The robot's chassis was designed using **SolidWorks** and optimized for performance. All components are securely housed, ensuring stability during matches.

---

## How to Use
1. **Hardware Setup**:
   - Assemble the components as per the design.
   - Connect the ESP32 to the motor driver and sensors.

2. **Software Setup**:
   - Upload the ESP32 code using Arduino IDE.
   - Pair the PlayStation controller with the ESP32 via Bluetooth.

3. **Power On**:
   - Use a 3S or 4S LiPo battery for optimal performance.
   - Test the robot's movement and sensor functionality.

4. **Compete**:
   - Control the robot wirelessly using the PlayStation controller.
   - Utilize obstacle detection features strategically during the match.
