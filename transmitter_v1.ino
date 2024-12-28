#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverMAC[] = {0xCC, 0x7B, 0x5C, 0x27, 0x0D, 0x8C}; //replace with your mac id.

typedef struct struct_message {
  int x_axis;  // Joystick X-axis value
  int y_axis;  // Joystick Y-axis value
} struct_message;

struct_message joystickData;  // Data structure to hold joystick values

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);

  // Set Wi-Fi mode to Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register send callback
  esp_now_register_send_cb(OnDataSent);

  // Register peer
   memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Read joystick values 
  joystickData.x_axis = analogRead(34); 
  joystickData.y_axis = analogRead(35);  

  // Map joystick values to PWM range (1000 to 2000)
  joystickData.x_axis = map(joystickData.x_axis, 0, 4095, 1000, 2000);
  joystickData.y_axis = map(joystickData.y_axis, 0, 4095, 1000, 2000);

  Serial.print("Joystick X: ");
  Serial.print(joystickData.x_axis);
  Serial.print("\tJoystick Y: ");
  Serial.println(joystickData.y_axis);

  // Send joystick data via ESP-NOW
  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *) &joystickData, sizeof(joystickData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } 
  else {
    Serial.println("Error sending the data");
  }

  delay(200);  
}
