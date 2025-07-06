# Agri_Rover
🔧 Project Title
Multi-Function Autonomous Agricultural Robot
## Team Member/Contributors
-[Metuku Dhanush] (https://github.com/dhanushmetuku) - Arduino Programming , Bluetooth logic

-[my contribution] - Hardware Integration, Circuit design, Arduino Programming

📌 Overview
This project is a smart agriculture robot designed to automate seed sowing, fertilizer dispensing, and ploughing, while avoiding obstacles and being remotely controlled via Bluetooth. It’s ideal for small to mid-scale farms and aims to reduce manual labor and increase efficiency in farming operations.

⚙️ Features
✅ Autonomous seed sowing at regular intervals

✅ Fertilizer dispensing pump with controlled timing

✅ Servo-based ploughing mechanism for accurate soil tilting

✅ Bluetooth control for navigation and remote operations

✅ Obstacle detection using IR sensors to avoid collisions

✅ Multi-directional movement (Forward, Backward, Turns, Diagonal)

✅ Integrated motor shield (Adafruit) for better motor control

🧠 Working Principle
1. Movement & Navigation
The robot uses 4 DC motors connected to the Adafruit Motor Shield to move in various directions.

Based on Bluetooth commands (F, B, L, R, etc.), the motors move forward, backward, or turn.

2. Ploughing Mechanism
A servo motor lifts or lowers the plough.

When moving forward/backward, the plough is lowered to till the soil.

When turning, the plough is lifted to prevent soil disturbance.

3. Seed Sowing
A servo motor connected to a seed dispenser drops seeds at regular intervals (every 2 seconds).

It moves to a 90° position to release the seed, then back to 0°.

4. Fertilizer Dispensing
A water pump is turned ON after each seed is released, running for a set duration (3 seconds) to pour fertilizer.

5. Obstacle Detection
2 IR sensors (left and right) detect obstacles:

If both detect, the robot stops.

If only one detects, the robot turns left or right to avoid the object.

| Component                  | Description                                    |
|---------------------------|------------------------------------------------|
| Arduino UNO or Mega       | Main microcontroller to run the code           |
| Adafruit Motor Shield     | Motor driver for controlling 4 DC motors       |
| DC Motors (x4)            | Used for robot wheel movement                  |
| Servo Motor (x2)          | 1 for seed dispensing, 1 for plough control    |
| IR Sensors (x2)           | For obstacle detection (connected to pins 4, 5)|
| Water Pump (5V/12V)       | For fertilizer dispensing                      |
| Bluetooth Module (HC-05)  | For wireless Bluetooth control                 |
| Battery Pack              | Power supply for motors and Arduino            |


| **Command** | **Action**                         |
| ----------- | ---------------------------------- |
| `F`         | Move Forward (plough down)         |
| `B`         | Move Backward (plough down)        |
| `L`         | Turn Left (plough up)              |
| `R`         | Turn Right (plough up)             |
| `I`         | Top Right (diagonal, plough up)    |
| `J`         | Top Left (diagonal, plough up)     |
| `K`         | Bottom Right (diagonal, plough up) |
| `M`         | Bottom Left (diagonal, plough up)  |
| `T`         | Stop Movement                      |


Flow of Working
| Step | Task Description                                                                 |
|------|-----------------------------------------------------------------------------------|
| 1    | Initialize serial communication, attach servos, set pin modes for pump and sensors |
| 2    | Set plough servo to down position and stop all motors initially                  |
| 3    | Continuously check for incoming Bluetooth commands from the user                 |
| 4    | On receiving movement commands (F, B, L, R, etc.), control motors accordingly     |
| 5    | Lower plough when moving forward/backward, and lift it during turns              |
| 6    | Every 2 seconds, activate seed dispensing servo to release seeds                 |
| 7    | Immediately after seed release, turn on water pump to dispense fertilizer        |
| 8    | Continuously monitor IR sensors for obstacle detection                           |
| 9    | Stop the robot or take turn actions if obstacles are detected                    |
| 10   | Repeat the loop for continuous operation                                          |

 Future Improvements
 Add GPS for path tracking

 Integrate IoT for remote monitoring via mobile app

 Add AI-based plant/pest detection

 Use solar panels for power efficiency

 Use Case
Designed for Indian farmers owning 1-acre cotton fields, this robot reduces labor, ensures uniform sowing and fertilization, and increases crop yield while minimizing resource usage.
