#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

bool left, right, forward, backward = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Slave"); // Name of the slave device
  Serial.println("The device started, now you can pair it with Bluetooth!");
}

void loop() {
  left, right, forward, backward = false;

  if (SerialBT.available()) {
    String message = SerialBT.readString();
    Serial.println("Received: " + message);

    if(message == "FORWARD"){
      forward = true;
      left, right, backward = false;
    }
    if(message == "BACKWARD"){
      backward = true;
      left, right, forward = false;
    }
    if(message == "RIGHT"){
      right = true;
      left, forward, backward = false;
    }
    if(message == "LEFT"){
      left = true;
      forward, right, backward = false;
    }
  }
  delay(1000);
}