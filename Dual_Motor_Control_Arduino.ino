// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

int motorSpeedA = 0; // Speed for Motor A (0 to 255)
int motorSpeedB = 0; // Speed for Motor B (0 to 255)

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Initializing motor control...");
  
  // Set all motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors initially
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  Serial.println("Motor control ready.");
}

void loop() {
  if (Serial.available() > 0) {
    // Read user input from Serial Monitor
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove any whitespace or newline characters

    if (input.equalsIgnoreCase("forward")) {
      motorForward();
    } else if (input.equalsIgnoreCase("reverse")) {
      motorReverse();
    } else if (input.startsWith("speed ")) {
      int speed = input.substring(6).toInt(); // Extract speed value
      setMotorSpeed(speed);
    } else if (input.equalsIgnoreCase("stop")) {
      stopMotors();
    } else {
      Serial.println("Invalid command. Use: forward, reverse, speed <value>, or stop.");
    }
  }
}

// Move motors forward
void motorForward() {
  Serial.println("Motors moving forward...");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Move motors in reverse
void motorReverse() {
  Serial.println("Motors moving in reverse...");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Set motor speed
void setMotorSpeed(int speed) {
  if (speed < 0 || speed > 255) {
    Serial.println("Invalid speed. Enter a value between 0 and 255.");
    return;
  }
  motorSpeedA = speed;
  motorSpeedB = speed;
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
  Serial.print("Motor speed set to: ");
  Serial.println(speed);
}

// Stop all motors
void stopMotors() {
  Serial.println("Motors stopped.");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
