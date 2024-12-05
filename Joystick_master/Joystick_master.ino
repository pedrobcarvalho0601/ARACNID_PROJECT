#include <BluetoothSerial.h>

#define pinYAxis 34
#define pinXAxis 35

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Master"); // Name of the master device
  Serial.println("The device started, now you can pair it with Bluetooth!");

  pinMode(pinXAxis, INPUT);
  pinMode(pinYAxis, INPUT);
}

void loop() {
  int xValue = analogRead(pinXAxis); 
  int yValue = analogRead(pinYAxis); 

  Serial.println(xValue);
  Serial.println(yValue);
  delay(500);

  // Map joystick values to actions
  if (yValue < 400) { // Joystick pushed up
    Serial.println("BACKWARDS");
    SerialBT.println("BACKWARDS");
    delay(100);
  } else if (yValue > 3600) { // Joystick pulled down
    Serial.println("FORWARDS");
    SerialBT.println("FORWARDS");
    delay(100);
  }

  if (xValue < 400) { // Joystick pushed left
    Serial.println("LEFT");
    SerialBT.println("LEFT");
    delay(100);
  } else if (xValue > 3600) { // Joystick pushed right
    Serial.println("RIGHT");
    SerialBT.println("RIGHT");
    delay(100);
  }

  delay(100); // Delay for readability
}


