//#include <BluetoothSerial.h>

#define pinYAxis 34
#define pinXAxis 35

//BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  //Serial.begin(9600);
  //SerialBT.begin("ESP32_Master"); // Name of the master device
  //Serial.println("The device started, now you can pair it with Bluetooth!");

  pinMode(pinXAxis, INPUT);
  pinMode(pinYAxis, INPUT);
}

void loop() {
  int yValue = analogRead(pinXAxis) / 4; 
  int xValue = analogRead(pinYAxis) / 4; 

  Serial.println(xValue);
  Serial.println(yValue);
  delay(500);

  // Map joystick values to actions
  if (yValue < 100) {
    Serial.println("FORWARDS");
    //SerialBT.println("FORWARDS");
    delay(100);
  }
  if (yValue > 900) {
    Serial.println("BACKWARDS");
    //SerialBT.println("BACKWARDS");
    delay(100);
  }

  if (xValue < 100) { 
    Serial.println("RIGHT");
    //SerialBT.println("RIGHT");
    delay(100);
  }
  if (xValue > 900) { 
    Serial.println("LEFT");
    //SerialBT.println("LEFT");
    delay(100);
  }

  delay(100);
}


