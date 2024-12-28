#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

static const int servoPin1 = 13;
static const int servoPin2 = 12;
static const int servoPin3 = 14;
static const int servoPin4 = 27;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Structure to receive joystick data
typedef struct struct_message {
  int x_axis;  // Joystick X-axis value
  int y_axis;  // Joystick Y-axis value
} struct_message;

struct_message joystickData;  // Data structure to hold received joystick values

int x = 0;
int y = 0;

// Callback function when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&joystickData, incomingData, sizeof(joystickData));
  

  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Joystick X: ");
  Serial.print(joystickData.x_axis);
  Serial.print("\tJoystick Y: ");
  Serial.println(joystickData.y_axis);
}

// Function to control servo positions
void stop() {
    servo1.write(88);
    servo2.write(88);
    servo3.write(88);
    servo4.write(88);
    Serial.println("stop");
}

void front() {
    servo1.write(60);
    servo2.write(60);
    servo3.write(120);
    servo4.write(120);
    Serial.println("front");
}

void back() {
    servo1.write(120);
    servo2.write(120);
    servo3.write(60);
    servo4.write(60);
    Serial.println("back");
}

void right() {
    servo1.write(120);
    servo2.write(120);
    servo3.write(120);
    servo4.write(120);
    Serial.println("right");
}

void left() {
    servo1.write(60);
    servo2.write(60);
    servo3.write(60);
    servo4.write(60);
    Serial.println("left");
}

void setup() {
  Serial.begin(115200);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);

  // Set Wi-Fi mode to Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register receive callback
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Map joystick data to control flags
  if (joystickData.x_axis < 1400) x = 1;
  else if (joystickData.x_axis > 1800) x = 2;
  else x = 3;

  if (joystickData.y_axis < 1400) y = 1;
  else if (joystickData.y_axis > 1800) y = 2;
  else y = 3;

  // Combine X and Y for case identification
  int caseIdentifier = x * 10 + y;

  Serial.print("Case Identifier: ");
  Serial.println(caseIdentifier);

  // Execute corresponding function
  switch (caseIdentifier) {
    case 33: stop(); break;
    case 23: front(); break;
    case 32: right(); break;
    case 31: left(); break;
    case 13: back(); break;
    default:
      Serial.println("Default case: No matching joystick range.");
      stop(); // Default to stop
      break;
  }

  delay(100); 
}
