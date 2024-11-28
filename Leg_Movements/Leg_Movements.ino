#include <Servo.h>

  #define RXp2 16
  #define TXp2 17

Servo servo[4][3];

// Define servos' ports
const int servo_pin[4][3] = { {2, 3, 4}, {5, 6, 7}, {8, 9, 10}, {11, 12, 13} };

// Define basic positions for the servos
const int neutral_position[3] = {90, 90, 90}; // Neutral angles for all servos
const int step_up_position[3] = {70, 110, 70}; // Leg lifted position
const int step_forward_position[3] = {110, 70, 110}; // Leg moves forward

void setup()
{

  // this sample code provided by www.programmingboss.com
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

  


  // Initialize all servos
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      servo[i][j].attach(servo_pin[i][j]);
      servo[i][j].write(neutral_position[j]); // Set initial position
      delay(100); // Delay to let servos move to position
    }
  }
}

void moveLeg(int leg, const int positions[3], int delay_time)
{
  // Move the specified leg to the given positions
  for (int i = 0; i < 3; i++)
  {
    servo[leg][i].write(positions[i]);
  }
  delay(delay_time);
}

void walkCycle()
{
  // Move legs in a cycle for walking forward

  // Step 1: Lift and move Leg 0 and Leg 2 forward
  int leg_up[] = {step_up_position[0], step_up_position[1], step_up_position[2]};
  int leg_forward[] = {step_forward_position[0], step_forward_position[1], step_forward_position[2]};

  moveLeg(0, leg_up, 300);
  moveLeg(2, leg_up, 300);
  moveLeg(0, leg_forward, 300);
  moveLeg(2, leg_forward, 300);

  // Step 2: Return Leg 0 and Leg 2 to neutral
  moveLeg(0, neutral_position, 300);
  moveLeg(2, neutral_position, 300);

  // Step 3: Lift and move Leg 1 and Leg 3 forward
  moveLeg(1, leg_up, 300);
  moveLeg(3, leg_up, 300);
  moveLeg(1, leg_forward, 300);
  moveLeg(3, leg_forward, 300);

  // Step 4: Return Leg 1 and Leg 3 to neutral
  moveLeg(1, neutral_position, 300);
  moveLeg(3, neutral_position, 300);
}


void loop()
{
  
  Serial.println("Message Received: ");
  Serial.println(Serial2.readString());

  delay(1000);

  walkCycle();
}
