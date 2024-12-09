
// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

#define trigPin 23
#define echoPin 22
#define SERVO_PIN 2

Servo ServoBLP;  // Back Left Pivot Servo (backwards) (135)
Servo ServoBLL;  // Back Left Lift Servo (down) (70)
Servo ServoBLT;  // Back Left Tibia Servo (up) (0)

Servo ServoBRP;  // Back Right Pivot Servo (forwards) (45)
Servo ServoBRL;  // Back Right Lift Servo (up) (110)
Servo ServoBRT;  // Back Right Tibia Servo (down) (180)

Servo ServoFRP;  // Front Right Pivot Servo (forwards) (135)
Servo ServoFRL;  // Front Right Lift Servo (down) (70)
Servo ServoFRT;  // Front Right Tibia Servo (up) (0)

Servo ServoFLP;  // Front Left Pivot Servo (backwards) (45)
Servo ServoFLL;  // Front Left Lift Servo (up) (110)
Servo ServoFLT;  // Front Left Tibia Servo (down) (180)

Servo ultrassomservo;
float distanceD, distanceE, distanceB;

//12, 14, 27 FL
//26, 25, 33 BL
//4, 16, 17 FR
//5, 18, 19 BR

void setup() {

  // Set up Serial Monitor
  Serial.begin(115200);

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
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

  // --------------------------- sensor -------------------------------//
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  ultrassomservo.attach(SERVO_PIN);
  ultrassomservo.write(90);  // Inicializa o servo parado
}

typedef struct struct_message {
  bool d;
  int move;
  bool start;
} struct_message;

// Create a structured object
struct_message myData;


// Callback function executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
}


// Função para medir a distância usando o sensor ultrassônico
long measureDistance() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;  // Conversão para cm
  return distance;
}

// Função para controlar o servo contínuo com base na distância
void looking_Path(int distance) {
  if (distance <= 10) {

    // Gira levemente para a direita
    ultrassomservo.write(0);  // Valor menor que 90 para girar à direita
    delay(2000);
    distanceD = measureDistance();
    // Gira levemente para a esquerda
    ultrassomservo.write(180);  // Valor maior que 90 para girar à esquerda
    delay(2000);
    distanceE = measureDistance();
    ultrassomservo.write(90);
    delay(2000);
    Path_choice(distanceD, distanceE);
  } else {
    ultrassomservo.write(90);  // Servo parado
    move_forward();
  }
}

void manualhello(int distance) {
  if (distance <= 10) {
    say_hello();
  }
}

void Path_choice(int distanceD, int distanceE) {
  if (distanceD - 3 > distanceE) {
    move_right(2);
  }
  if (distanceE - 3 > distanceD) {
    move_left(2);
  }
  if (distanceD + 3 > distanceE && distanceD - 3 < distanceE || distanceE + 3 > distanceD && distanceE - 3 < distanceD) {
    move_right(4);
  }
}

void receivejoystick() {
  if (myData.move == 1) {
    move_left(2);
  }
  if (myData.move == 2) {
    move_forward();
  }
  if (myData.move == 3) {
    move_right(2);
  }
  if (myData.move == 4) {
  }
}

void stand_up() {
  //
  ServoBRP.write(85);
  delay(500);
  ServoFLP.write(55);
  delay(500);
  ServoBLP.write(125);
  delay(500);
  ServoFRP.write(95);
  delay(500);

  //
  ServoBLL.write(80);
  delay(500);
  ServoFRL.write(80);
  delay(500);
  ServoBRL.write(100);
  delay(500);
  ServoFLL.write(100);
  delay(500);

  //
  ServoBLT.write(0);
  delay(500);
  ServoBRT.write(180);
  delay(500);
  ServoFRT.write(0);
  delay(500);
  ServoFLT.write(180);
  delay(500);
}

void move_forward() {
  delay(250);
  //first step

  //low BL
  ServoBLL.write(85);
  ServoBLT.write(5);
  delay(350);
  //rotate FR
  ServoFRL.write(60);
  ServoFRT.write(10);
  delay(250);
  ServoFRP.write(135);
  delay(300);
  ServoFRL.write(80);
  ServoFRT.write(0);
  delay(250);
  //rise BL
  ServoBLL.write(80);
  ServoBLT.write(0);
  delay(350);

  //crawl step
  ServoBRP.write(55);
  ServoFLP.write(90);
  ServoBLP.write(135);
  ServoFRP.write(125);
  delay(500);

  //second step
  //low FR
  ServoFRL.write(85);
  ServoFRT.write(5);
  delay(350);
  //rotate BL
  ServoBLL.write(60);
  ServoBLT.write(10);
  delay(250);
  ServoBLP.write(90);
  delay(300);
  ServoBLL.write(80);
  ServoBLT.write(0);
  delay(250);
  //rise FR
  ServoFRL.write(80);
  ServoFRT.write(0);
  delay(350);

  //Third step
  //low BR
  ServoBRL.write(95);
  ServoBRT.write(175);
  delay(350);
  //rotate FL
  ServoFLL.write(120);
  ServoFLT.write(170);
  delay(250);
  ServoFLP.write(45);
  delay(300);
  ServoFLL.write(100);
  ServoFLT.write(180);
  delay(250);
  //rise BR
  ServoBRL.write(100);
  ServoBRT.write(180);
  delay(350);
  //crawl step
  ServoBRP.write(45);
  ServoFLP.write(55);
  ServoBLP.write(125);
  ServoFRP.write(95);
  delay(500);

  //quarter step
  //low FL
  ServoFLL.write(95);
  ServoFLT.write(175);
  delay(350);
  //rotate BR
  ServoBRL.write(120);
  ServoBRT.write(170);
  delay(250);
  ServoBRP.write(85);
  delay(300);
  ServoBRL.write(100);
  ServoBRT.write(180);
  delay(250);
  //rise FL
  ServoFLL.write(100);
  ServoFLT.write(180);
  delay(350);
}

//-----------------------------------------------------------------------------//

void move_left(int n) {

  for (int x = 0; x <= n; x++) {
    delay(250);
    //first step

    //Lift FR
    ServoFRL.write(60);
    ServoFRT.write(10);
    delay(250);
    //rotate ALL
    ServoFLP.write(45);
    ServoFRP.write(135);
    ServoBLP.write(105);
    ServoBRP.write(75);
    delay(250);
    //down FR
    ServoFRL.write(80);
    ServoFRT.write(0);
    delay(450);

    //second step
    //Lift FL
    ServoFLL.write(120);
    ServoFLT.write(170);
    delay(250);
    //rotate ALL
    ServoBRP.write(55);
    ServoFRP.write(125);
    ServoBLP.write(95);
    ServoFLP.write(85);
    delay(250);
    //down FL
    ServoFLL.write(100);
    ServoFLT.write(180);
    delay(250);

    //Third step
    //Lift BL
    ServoBLL.write(60);
    ServoBLT.write(10);
    delay(250);
    //rotate ALL
    ServoBRP.write(45);
    ServoFRP.write(105);
    ServoBLP.write(135);
    ServoFLP.write(70);
    delay(250);
    //down BL
    ServoBLL.write(80);
    ServoBLT.write(0);
    delay(250);

    //quarter step
    //Lift BR
    ServoBRL.write(120);
    ServoBRT.write(170);
    delay(250);
    //rotate ALL
    ServoBRP.write(85);
    ServoFLP.write(55);
    ServoBLP.write(125);
    ServoFRP.write(95);
    delay(250);
    //down BR
    ServoBRL.write(100);
    ServoBRT.write(180);
    delay(250);
  }
}

//----------------------------------------------------------------------------------//
void move_right(int n) {

  for (int x = 0; x <= n; x++) {
    delay(250);
    //first step

    //Lift BR
    ServoBRL.write(120);
    ServoBRT.write(170);
    delay(250);
    //rotate ALL
    ServoBRP.write(45);
    ServoFRP.write(105);
    ServoBLP.write(135);
    ServoFLP.write(70);
    delay(250);
    //down BR
    ServoBRL.write(100);
    ServoBRT.write(180);
    delay(450);

    //second step
    //Lift BL
    ServoBLL.write(60);
    ServoBLT.write(10);
    delay(250);
    //rotate ALL
    ServoBRP.write(55);
    ServoFRP.write(125);
    ServoBLP.write(95);
    ServoFLP.write(85);
    delay(250);
    //down BL
    ServoBLL.write(80);
    ServoBLT.write(0);
    delay(250);

    //Third step
    //Lift FL
    ServoFLL.write(120);
    ServoFLT.write(170);
    delay(250);
    //rotate ALL
    ServoFLP.write(45);
    ServoFRP.write(135);
    ServoBLP.write(105);
    ServoBRP.write(75);
    delay(250);
    //down FL
    ServoFLL.write(100);
    ServoFLT.write(180);
    delay(250);

    //quarter step
    //Lift FR
    ServoFRL.write(60);
    ServoFRT.write(10);
    delay(250);
    //rotate ALL
    ServoFLP.write(55);
    ServoBRP.write(85);
    ServoFRP.write(95);
    ServoBLP.write(125);
    delay(250);
    //down FR
    ServoFRL.write(80);
    ServoFRT.write(0);
    delay(250);
  }
}

void say_hello() {
  stand_up();
  delay(300);

  //low BL
  ServoBLL.write(88);
  ServoBLT.write(8);
  delay(350);
  //rotate FR
  ServoFRL.write(55);
  ServoFRT.write(10);
  delay(250);

  ServoFRP.write(145);
  delay(300);
  for (int i = 0; i < 4; i++) {
    ServoFRT.write(55);
    delay(150);
    ServoFRT.write(0);
    delay(150);
  }
  ServoFRP.write(95);
  delay(300);
  ServoFRL.write(80);
  ServoFRT.write(0);
  //rise BL
  ServoBLL.write(80);
  ServoBLT.write(0);
  delay(350);
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

  ServoBRP.write(85);
  delay(500);
  ServoFLP.write(55);
  delay(500);
  ServoBLP.write(125);
  delay(500);
  ServoFRP.write(95);
  delay(500);
}

bool up = false;
bool finish = false;

/*
void UP_DOWN(){
  if(myData.start==false){
    center_servos_down();
    up=false;
    delay(200);
  }
  if(myData.start==true){
    stand_up();
    up=true;
    delay(200);
  }
}
 */

void loop() {
  delay(4000);
  center_servos_down();
  delay(500);
  stand_up();
  up = true;
  say_hello();
  delay(300);

  //controlo manual
  if (myData.d == true) {
    if (up == false) {
      delay(100);
      stand_up();
    }
    if (up == true) {
      while (myData.d == true) {
        receivejoystick();
        delay(400);
        int distance = measureDistance();
        manualhello(distance);
        delay(500);
      }
    }
  }
  //contorlo automatico
  if (myData.d == false) {
    if (up == false) {
      delay(100);
      stand_up();
    }
    if (up == true) {
      while (myData.d == false) {
        delay(400);
        int distance = measureDistance();
        looking_Path(distance);
        delay(100);
      }
    }
  }
}