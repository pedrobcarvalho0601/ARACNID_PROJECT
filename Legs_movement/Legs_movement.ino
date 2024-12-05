 
// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

Servo ServoBLP; // Back Left Pivot Servo (backwards) (135)
Servo ServoBLL; // Back Left Lift Servo (down) (70) 
Servo ServoBLT; // Back Left Tibia Servo (up) (0)

Servo ServoBRP; // Back Right Pivot Servo (forwards) (45)
Servo ServoBRL; // Back Right Lift Servo (up) (110) 
Servo ServoBRT; // Back Right Tibia Servo (down) (180)

Servo ServoFRP; // Front Right Pivot Servo (forwards) (135)
Servo ServoFRL; // Front Right Lift Servo (down) (70)
Servo ServoFRT; // Front Right Tibia Servo (up) (0)

Servo ServoFLP; // Front Left Pivot Servo (backwards) (45)
Servo ServoFLL; // Front Left Lift Servo (up) (110)
Servo ServoFLT; // Front Left Tibia Servo (down) (180)

//12, 14, 27 FL (FR)
//26, 25, 33 BL (BR)
//4, 16, 17 FR (FL)
//5, 18, 19 BR (BL)

void setup() {

 // Set up Serial Monitor
  Serial.begin(115200);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);

  // Attach servos to Arduino Pins
  ServoFLP.attach(5);
  ServoFLL.attach(18);
  ServoFLT.attach(19);

  ServoBLP.attach(17);
  ServoBLL.attach(16);
  ServoBLT.attach(4);

  ServoBRP.attach(27);
  ServoBRL.attach(14);
  ServoBRT.attach(12);

  ServoFRP.attach(26);
  ServoFRL.attach(25);
  ServoFRT.attach(33);

}

typedef struct struct_message {
  bool d;
} struct_message;
 
// Create a structured object
struct_message myData;

bool finish=false;
 
// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Data received: ");
  Serial.println(len);
  Serial.print("Boolean Value: ");
  Serial.println(myData.d);
  Serial.println();
}

// Define the delay between function calls (in milliseconds)
const unsigned long FUNCTION_DELAY = 2000;  // 2 seconds
const unsigned long t = 5;
const unsigned long tt = 7;

/*
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
*/
void stand_up_without_for() {
  // Move the pivot servo from 90 - 45 FLP BRP
  ServoBRP.write(90);
  delay(500);
  ServoFLP.write(55);
  delay(500);
  // Move the pivot servo from 90 - 135 FRP BLP
  ServoBLP.write(125);
  delay(500);
  ServoFRP.write(90);
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

void move_forward(){
  stand_up_without_for();
  delay(1000);
  //first step
  //low BL
  ServoBLL.write(80);
  ServoBLT.write(5);
  delay(450);
  //rotate FR
  ServoFRL.write(65);
  delay(250);
  ServoFRP.write(135);
  delay(300);
  //rise BL
  ServoBLL.write(75);
  ServoBLT.write(0);
  delay(450);

  //crawl step
  ServoBRP.write(55);
  ServoFLP.write(90);
  ServoBLP.write(135);
  ServoFRP.write(125);
  delay(500);

}

void say_hello() {
}

void center_servos_down() {

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
  ServoFLL.write(90);
  delay(500);
  ServoFRL.write(90);
  delay(500);
  ServoBLL.write(90);
  delay(500);

  ServoBRP.write(90);
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
center_servos_down();
delay(1000);
move_forward();
delay(100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000);

/*
  if(mydata.d==true && finish == false){
  delay(1000);
  center_servos_down();
  delay(2000);
  stand_up_without_for();
  finish=true;
  }
  if(mydata.d==false && finish==true){
  delay(1000);
  center_servos();
  delay(2000);
  finish=false;
  }

*/
}
