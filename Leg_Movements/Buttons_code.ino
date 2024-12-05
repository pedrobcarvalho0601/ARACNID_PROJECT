const int startPin = 35;
const int modePin = 34;

//12, 14, 27 FL (FR)
//26, 25, 33 BL (BR)
//4, 16, 17 FR (FL)
//5, 18, 19 BR (BL)

bool movementON = false;

enum STATE_START {
  OFF,
  ON
} start_state;

int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
bool currentButtonState = false;

void setup() {
  Serial.begin(115200);

  pinMode(startPin, INPUT);
  pinMode(modePin, INPUT);

  lastButtonState = digitalRead(startPin);
  start_state = OFF;
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
      }
      break;

    case ON:
      //movementON = true;
      //getting up
      currentButtonState = buttonPressed();
      if(currentButtonState && movementON == false){
        currentButtonState = false;
        start_state = OFF;
      }
      break;

    default: 
      start_state = OFF;
      break;
  }
}
