#include <AFMotor.h>
#include <Servo.h>

// Motor setup for the Adafruit Motor Shield
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Servo setup for seed dispensing
Servo seedServo;
int seedPosition = 90;       // Position of the servo to release seeds
int restPosition = 0;        // Rest position of the seed servo
unsigned long lastReleaseTime = 0; // Time when the last seed was released
const int seedReleaseInterval = 2000; // Time between seed releases in milliseconds

// Additional Servo setup for plough control
Servo ploughServo;
int ploughUpPosition = 90;    // Plough is up at +90 degrees
int ploughDownPosition = -90; // Plough is down at -90 degrees

// Pump setup for fertilizer dispensing
const int pumpPin = 8;  // Pin to control the fertilizer pump
const int pumpRunTime = 3000; // Pump run time in milliseconds

// Obstacle detection setup using IR sensors
const int irSensor1 = 4;     // IR sensor 1 connected to pin 4
const int irSensor2 = 5;     // IR sensor 2 connected to pin 5

// Bluetooth command setup
char bluetoothCommand;

// Speed for motors
int Speeed = 255;

void setup() {
  Serial.begin(9600);  // Set the baud rate for Bluetooth communication
  seedServo.attach(9);  // Attach the seed servo to pin 9
  ploughServo.attach(10); // Attach the plough servo to pin 10
  pinMode(pumpPin, OUTPUT);  // Set pump pin as output
  pinMode(irSensor1, INPUT);  // Set IR sensor 1 as input
  pinMode(irSensor2, INPUT);  // Set IR sensor 2 as input

  seedServo.write(restPosition);  // Initialize seed servo to rest position
  ploughServo.write(ploughDownPosition);  // Initialize plough servo to down position
  Stop(); // Initialize all motors to stop
}

void loop() {
  unsigned long currentTime = millis();

  // Bluetooth control
  if (Serial.available() > 0) {
    bluetoothCommand = Serial.read();
    handleBluetoothCommand(bluetoothCommand);
  }

  // Seed sowing and fertilizer dispensing
  if (currentTime - lastReleaseTime >= seedReleaseInterval) {
    releaseSeed(); // This function will now control the plough as well
    dispenseFertilizer();
    lastReleaseTime = currentTime;
  }

  // Obstacle detection using IR sensors
  int ir1Status = digitalRead(irSensor1);
  int ir2Status = digitalRead(irSensor2);

  if (ir1Status == LOW && ir2Status == LOW) { // Obstacle detected by both IR sensors
    Stop();
    Serial.println("Obstacle Detected by both IR sensors");
  } else if (ir1Status == LOW && ir2Status == HIGH) { // Obstacle detected by IR sensor 1
    right(); // Turn right to avoid obstacle
    Serial.println("Turning Right to avoid obstacle detected by IR Sensor 1");
  } else if (ir1Status == HIGH && ir2Status == LOW) { // Obstacle detected by IR sensor 2
    left(); // Turn left to avoid obstacle
    Serial.println("Turning Left to avoid obstacle detected by IR Sensor 2");
  }
}

void handleBluetoothCommand(char command) {
  switch (command) {
    case 'F': 
      ploughServo.write(ploughDownPosition); // Ensure plough is down
      forward(); 
      break;
    case 'B': 
      ploughServo.write(ploughDownPosition); // Ensure plough is down
      back(); 
      break;
    case 'L': 
    case 'R': 
    case 'I': 
    case 'J': 
    case 'K': 
    case 'M': 
      ploughServo.write(ploughUpPosition); // Lift plough when turning
      if (command == 'L') left();
      if (command == 'R') right();
      if (command == 'I') topright();
      if (command == 'J') topleft();
      if (command == 'K') bottomright();
      if (command == 'M') bottomleft();
      break;
    case 'T': 
      Stop(); 
      break;
    default: 
      Stop(); 
      break; // Stop if unknown command
  }
}

void releaseSeed() {
  seedServo.write(seedPosition);  // Move servo to release position
  delay(500);  // Wait for seed to drop
  seedServo.write(restPosition);  // Move servo back to rest position
  Serial.println("Seed Released");
}

void dispenseFertilizer() {
  digitalWrite(pumpPin, HIGH);  // Turn on the pump
  delay(pumpRunTime);  // Run the pump for the specified time
  digitalWrite(pumpPin, LOW);   // Turn off the pump
  Serial.println("Fertilizer Dispensed");
}

void forward() {
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.setSpeed(Speeed); motor3.run(FORWARD);
  motor4.setSpeed(Speeed); motor4.run(FORWARD);
}

void back() {
  motor1.setSpeed(Speeed); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed); motor4.run(BACKWARD);
}

void left() {
  motor1.setSpeed(Speeed); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed); motor3.run(FORWARD);
  motor4.setSpeed(Speeed); motor4.run(FORWARD);
}

void right() {
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.setSpeed(Speeed); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed); motor4.run(BACKWARD);
}

void topleft() {
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.setSpeed(Speeed/3.1); motor3.run(FORWARD);
  motor4.setSpeed(Speeed/3.1); motor4.run(FORWARD);
}

void topright() {
  motor1.setSpeed(Speeed/3.1); motor1.run(FORWARD);
  motor2.setSpeed(Speeed/3.1); motor2.run(FORWARD);
  motor3.setSpeed(Speeed); motor3.run(FORWARD);
  motor4.setSpeed(Speeed); motor4.run(FORWARD);
}

void bottomleft() {
  motor1.setSpeed(Speeed); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed/3.1); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed/3.1); motor4.run(BACKWARD);
}

void bottomright() {
  motor1.setSpeed(Speeed/3.1); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed/3.1); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed); motor4.run(BACKWARD);
}

void Stop() {
  motor1.setSpeed(0); motor1.run(RELEASE);
  motor2.setSpeed(0); motor2.run(RELEASE);
  motor3.setSpeed(0); motor3.run(RELEASE);
  motor4.setSpeed(0); motor4.run(RELEASE);
}