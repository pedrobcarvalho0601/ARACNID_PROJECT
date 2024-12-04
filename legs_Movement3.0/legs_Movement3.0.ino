#include <ESP32Servo.h>




Servo ServoBLP;  // Back Left Pivot Servo
Servo ServoBLL;  // Back Left Lift Servo
Servo ServoBLT;  // Back Left Tibia Servo

Servo ServoBRP;  // Back Right Pivot Servo
Servo ServoBRL;  // Back Right Lift Servo
Servo ServoBRT;  // Back Right Tibia Servo

Servo ServoFRP;  // Front Right Pivot Servo
Servo ServoFRL;  // Front Right Lift Servo
Servo ServoFRT;  // Front Right Tibia Servo

Servo ServoFLP;  // Front Left Pivot Servo
Servo ServoFLL;  // Front Left Lift Servo
Servo ServoFLT;  // Front Left Tibia Servo


void setup() {

  // Attach servos to Arduino Pins
  ServoFLP.attach(17);
  ServoFLL.attach(16);
  ServoFLT.attach(4);

  ServoBLP.attach(5);
  ServoBLL.attach(18);
  ServoBLT.attach(19);

  ServoBRP.attach(26);
  ServoBRL.attach(25);
  ServoBRT.attach(33);

  ServoFRP.attach(27);
  ServoFRL.attach(14);
  ServoFRT.attach(12);
  /*
  ServoFLP.write(90);
  ServoFLL.write(90);
  ServoFLT.write(90);
  ServoBLP.write(90);
  ServoBLL.write(90);
  ServoBLT.write(90);
  ServoBRP.write(90);
  ServoBRL.write(90);
  ServoBRT.write(90);
  ServoFRP.write(90);
  ServoFRL.write(90);
  ServoFRT.write(90);
  */
}
// Define the delay between function calls (in milliseconds)
const unsigned long FUNCTION_DELAY = 2000;  // 2 seconds
const unsigned long t = 5;
const unsigned long tt = 7;


void stand_up() {
  // Move the pivot servo from 90 - 45 FLP BRP
  for (int angle = 90; angle >= 45; angle--) {
    ServoBRP.write(angle);
    ServoFLP.write(angle);
    delay(tt);
  }
  // Move the pivot servo from 90 - 135 FRP BLP
  for (int angle = 90; angle <= 135; angle++) {
    ServoBLP.write(angle);
    ServoFRP.write(angle);
    delay(tt);
  }
  // Move the lift servo from 90 to 20 - BLL FRL
  for (int angle = 90; angle >= 20; angle--) {
    ServoBLL.write(angle);
    ServoFRL.write(angle);
    delay(tt);
  }
  // Move the lift servo from 90 to 110 - BRL FLL
  for (int angle = 90; angle <= 110; angle++) {
    ServoBRL.write(angle);
    ServoFLL.write(angle);
    delay(tt);
  }
  delay(1000);
  // Move the Tibia servo from 90 to 20 - BLT FRT
  for (int angle = 90; angle >= 0; angle--) {
    ServoBLT.write(angle);
    ServoFRT.write(angle);
    delay(tt);
  }
  // Move the Tibia servo from 90 to 110 - BRT FLT
  for (int angle = 90; angle <= 180; angle++) {
    ServoBRT.write(angle);
    ServoFLT.write(angle);
    delay(tt);
  }
}

void stand_up_without_for() {
  // Move the pivot servo from 90 - 45 FLP BRP
  ServoBRP.write(45);
  delay(500);
  ServoFLP.write(45);
  delay(500);
  // Move the pivot servo from 90 - 135 FRP BLP
  ServoBLP.write(135);
  delay(500);
  ServoFRP.write(135);
  delay(800);

  // Move the lift servo from 90 to 20 - BLL FRL
  ServoBLL.write(75);
  delay(500);
  ServoFRL.write(75);
  delay(500);
  // Move the lift servo from 90 to 110 - BRL FLL
  ServoBRL.write(105);
  delay(500);
  ServoFLL.write(105);
  delay(800);
  // Move the Tibia servo from 90 to 0 - BLT FRT
  ServoBLT.write(0);
  delay(500);
  ServoFRT.write(0);
  delay(500);
  // Move the Tibia servo from 90 to 110 - BRT FLT
  ServoBRT.write(180);
  delay(500);
  ServoFLT.write(180);
  delay(800);
}

void say_hello() {
}

void center_servos() {

  ServoFRT.write(90);
  delay(500);
  ServoBRT.write(90);
  delay(500);
  ServoFLT.write(90);
  delay(500);
  ServoBLT.write(90);
  delay(500);

  ServoBRL.write(90);
  delay(500);
  ServoFLL.write(85);
  delay(500);
  ServoFRL.write(90);
  delay(500);
  ServoBLL.write(90);
  delay(500);

  ServoBRP.write(95);
  delay(500);
  ServoFRP.write(90);
  delay(500);
  ServoBLP.write(90);
  delay(500);
  ServoFLP.write(90);
  delay(500);
}

void loop() {

  delay(10000);
  center_servos();
  delay(2000);
  stand_up_without_for();
  delay(100000000000);
}
