# ESP-NOW_Rover
A four wheel drive tiny robot using ESP-NOW protocol.






https://github.com/user-attachments/assets/6212cd83-c74d-4091-b779-c6ddc8c4d6c3




COMPONENTS REQUIRED:

Transmitter:
1. ESP32
2. arduino joystick
3. 1s lipo cell

Rover:
1. Four 9 gram servo motor
2. ESP32
3. Two 1s lipo cells
4. 3D printed chassis (or any chassis of your choice).

First step would be modify the servo motors to achieve continious rotaion. Refer this video: https://www.youtube.com/watch?v=O_brwlF283c

STL file for the chassis can be found here : https://www.printables.com/model/160897-fpv-micro-rc-car/files?lang=de

ESP32 transmitter case : https://www.instructables.com/ESP-NOW-Remote-Control/

CONNECTIONS:

 Rover:

servo1 --> D13

servo2 --> D12

servo3 --> D14

servo4 --> D22

Separate battery to powerup the servos and esp32. Common ground between the esp32 and motors.

 Transmitter:

 VRX --> D34
 
 VRY --> D35
 
 5v --> vin (of esp32)
 
 gnd --> gnd 


Find out the MAC address of the esp32 of the rover by uploading the check_mac_address code onto the esp32. Once the code is uploaded the mac address will be diplayed in the serial monitor. Copy the MAC address and paste it in the mac address of the transmitter_v1.ino. 

Upload the transmitter_v1.ino to the transmitter esp32 and receiver_v1.ino to the rover esp32.

Change the motor pins in the receiver_v1.ino code according to your motor connections connections.



![IMG_6182](https://github.com/user-attachments/assets/a179e6be-36da-4199-bcb0-873b88638bbd)

![IMG_6183](https://github.com/user-attachments/assets/bbabbf0b-426f-48b6-8385-a65a49413428)

![IMG_6186](https://github.com/user-attachments/assets/b0322654-1acf-4f86-b649-7c5459cb1f78)

![IMG_6185](https://github.com/user-attachments/assets/89a14358-a075-4c32-ae1d-11dabb03ce83)
