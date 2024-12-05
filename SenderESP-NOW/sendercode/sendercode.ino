// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
 
const int startPin = 36;
const int modePin = 39;
// Variables for test data
int int_value;
float float_value;
bool bool_value = true;
 
// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0x08, 0xB6, 0x1F, 0xEF, 0x82, 0x28};
 
// Define a data structure
bool movementON = false;

typedef struct struct_message {
  bool d;
} struct_message;

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
  
  // Set up Serial Monitor
  Serial.begin(115200);

  pinMode(startPin, INPUT);
  pinMode(modePin, INPUT);

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
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
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

   switch (start_state){
    case OFF:
      //movementON = true;
      //getting down
      currentButtonState = buttonPressed();
      if(currentButtonState && movementON == false){
        currentButtonState = false;
        start_state = ON;
        myData.d = false;
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      }
      break;

    case ON:
      //movementON = true;
      //getting up
      currentButtonState = buttonPressed();
      if(currentButtonState && movementON == false){
        currentButtonState = false;
        start_state = OFF;
        myData.d = true;
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
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