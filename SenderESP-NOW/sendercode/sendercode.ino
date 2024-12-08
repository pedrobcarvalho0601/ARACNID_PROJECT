// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

#define LED_BUILTIN 33
#define pinYAxis 15
#define pinXAxis 2

const int startPin = 25;
const int modePin = 26;

// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = { 0x08, 0xB6, 0x1F, 0xEF, 0x82, 0x28 };

// Define a data structure
bool movementON = false;

typedef struct struct_message {
  bool d;
  int move;
} struct_message;

//forward = 2
//left = 1
//right = 3
//back = 4

enum STATE_START {
  OFF,
  ON
} start_state;

// Create a structured object
struct_message myData;

int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
bool currentButtonState = false;


// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  // Set up Serial Monitor
  Serial.begin(115200);

  pinMode(startPin, INPUT);
  pinMode(modePin, INPUT);

  pinMode(pinXAxis, INPUT);
  pinMode(pinYAxis, INPUT);

  lastButtonState = digitalRead(startPin);
  start_state = OFF;

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void joystick() {
  int yValue = analogRead(pinXAxis) / 4;
  int xValue = analogRead(pinYAxis) / 4;

  Serial.println(xValue);
  Serial.println(yValue);
  delay(500);

  // Map joystick values to actions
  if (yValue < 100) {
    Serial.println("FORWARDS");
    myData.move = 2;
    delay(100);
  } 
  if (xValue < 100) {
    Serial.println("RIGHT");
    myData.move = 3;
    delay(100);
  }
  if (xValue > 900) {
    Serial.println("LEFT");
    myData.move = 1;
    delay(100);
  }
  delay(100);
}

bool buttonPressed() {
  int reading = digitalRead(startPin);
  bool pressed = false;
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        pressed = true;
      }
    }
  }
  lastButtonState = reading;
  return pressed;
}



void loop() {

  switch (start_state) {
    case OFF:
      //movementON = true;
      //getting down
      currentButtonState = buttonPressed();
      if (currentButtonState && movementON == false) {
        currentButtonState = false;
        start_state = ON;
        myData.d = true;
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
        digitalWrite(LED_BUILTIN, HIGH);
        while(currentButtonState == false){
          joystick();
          esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
          currentButtonState = buttonPressed();
          delay(300);
        }
      }
      break;

    case ON:
      //movementON = true;
      //getting up
      currentButtonState = buttonPressed();
      if (currentButtonState && movementON == false) {
        currentButtonState = false;
        start_state = OFF;
        myData.d = false;
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
        digitalWrite(LED_BUILTIN, OFF);
      }
      break;

    default:
      start_state = OFF;
      break;
  }

  // Invert the boolean value
  // bool_value = !bool_value;

  // Send message via ESP-NOW

  /*  
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
  delay(2000);
  */
}