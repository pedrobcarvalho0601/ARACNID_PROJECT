#include <ESP32Servo.h>




Servo ServoBLP; // Back Left Pivot Servo
Servo ServoBLL; // Back Left Lift Servo
Servo ServoBLT; // Back Left Tibia Servo

Servo ServoBRP; // Back Right Pivot Servo
Servo ServoBRL; // Back Right Lift Servo
Servo ServoBRT; // Back Right Tibia Servo

Servo ServoFRP; // Front Right Pivot Servo
Servo ServoFRL; // Front Right Lift Servo
Servo ServoFRT; // Front Right Tibia Servo

Servo ServoFLP; // Front Left Pivot Servo
Servo ServoFLL; // Front Left Lift Servo
Servo ServoFLT; // Front Left Tibia Servo

void setup()
{

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
}

// Define the delay between function calls (in milliseconds)
const unsigned long FUNCTION_DELAY = 2000; // 2 seconds
const unsigned long t = 5;
const unsigned long tt = 7;

void stand_up(){
    // Move the pivot servo from 90 - 45 FLP BRP
    for (int angle = 90; angle >= 45; angle --) {
    ServoBRP.write(angle);
    ServoFLP.write(angle);
    delay(tt);
  }
      // Move the pivot servo from 90 - 135 FRP BLP
    for (int angle = 90; angle <= 135; angle ++) {
    ServoBLP.write(angle);
    ServoFRP.write(angle);
    delay(tt);
  }
    // Move the lift servo from 90 to 20 - BLL FRL
  for (int angle = 90; angle >= 20; angle --) {
    ServoBLL.write(angle);
    ServoFRL.write(angle);
    delay(tt);
  }
    // Move the lift servo from 90 to 110 - BRL FLL
  for (int angle = 90; angle <= 110; angle ++) {
    ServoBRL.write(angle);
    ServoFLL.write(angle);
    delay(tt);
  }
  delay(1000);
      // Move the Tibia servo from 90 to 20 - BLT FRT
  for (int angle = 90; angle >= 0; angle --) {
    ServoBLT.write(angle);
    ServoFRT.write(angle);
    delay(tt);
  }
    // Move the Tibia servo from 90 to 110 - BRT FLT
  for (int angle = 90; angle <= 180; angle ++) {
    ServoBRT.write(angle);
    ServoFLT.write(angle);
    delay(tt);
  }
}


void say_hello(){
    // Move the pivot servo from 90 - 45 FLP BRP
    for (int angle = 90; angle >= 45; angle -= 2) {
    ServoBRP.write(angle);
    ServoFLP.write(angle);
    delay(tt);
  }
      // Move the pivot servo from 90 - 135 FRP BLP
    for (int angle = 90; angle <= 135; angle += 2) {
    ServoBLP.write(angle);
    ServoFRP.write(angle);
    delay(tt);
  }
    // Move the lift servo from 90 to 20 - BLL FRL
  for (int angle = 90; angle >= 20; angle -= 2) {
    ServoBLL.write(angle);
    ServoFRL.write(angle);
    delay(tt);
  }
    // Move the lift servo from 90 to 110 - BRL FLL
  for (int angle = 90; angle <= 110; angle += 2) {
    ServoBRL.write(angle);
    ServoFLL.write(angle);
    delay(tt);
  }
  delay(1000);
      // Move the Tibia servo from 90 to 20 - BLT FRT
  for (int angle = 90; angle >= 0; angle -= 2) {
    ServoBLT.write(angle);
    ServoFRT.write(angle);
    delay(tt);
  }
    // Move the Tibia servo from 90 to 110 - BRT FLT
  for (int angle = 90; angle <= 180; angle += 2) {
    ServoBRT.write(angle);
    ServoFLT.write(angle);
    delay(tt);
  }
}









void moveLeg_Left_Forward(Servo& liftServo, Servo& pivotServo , Servo& oppositePivotServo)
{
  // Move the lift servo from 90 to 20 - BLL FRL
  for (int angle = 90; angle >= 20; angle -= 2) {
    liftServo.write(angle);
    delay(tt);
  }
    // Move the lift servo from 90 to 110 - BRL FLL
  for (int angle = 90; angle <= 110; angle += 2) {
    liftServo.write(angle);
    delay(tt);
  }

  // Move the pivot servo from 90 to 0
  for (int angle = 90; angle >= 0; angle -= 2) {
    pivotServo.write(angle);
    delay(tt);
  }

  // Move the lift servo from 180 to 90
  for (int angle = 180; angle >= 90; angle -= 2) {
    liftServo.write(angle);
    delay(tt);
  }
}
void moveLeg_Right_Forward(Servo& liftServo, Servo& pivotServo , Servo& oppositePivotServo)
{
  // Move the lift servo from 90 to 180
  for (int angle = 90; angle <= 180; angle += 2) {
    liftServo.write(angle);
    delay(tt);
  }

  // Move the pivot servo from 90 to 180
  for (int angle = 90; angle <= 180; angle += 2) {
    pivotServo.write(angle);
    delay(tt);
  }

  // Move the lift servo from 180 to 90
  for (int angle = 180; angle >= 90; angle -= 2) {
    liftServo.write(angle);
    delay(tt);
  }
}
        // Move Spider  Robot Backward logic
void moveLeg_Left_Backward(Servo& liftServo, Servo& pivotServo, Servo& oppositePivotServo)
{
  // Move the lift servo from 90 to 180
  for (int angle = 90; angle <= 180; angle += 2) {
    liftServo.write(angle);
    delay(tt);
  }

  // Move the pivot servo from 90 to 180
  for (int angle = 90; angle <= 180; angle += 2) {
    pivotServo.write(angle);
    delay(tt);
  }

  // Move the lift servo from 180 to 90
  for (int angle = 180; angle >= 90; angle -= 2) {
    liftServo.write(angle);
    delay(tt);
  }
}

void moveLeg_Right_Backward(Servo& liftServo, Servo& pivotServo, Servo& oppositePivotServo)
{
  // Move the lift servo from 90 to 180
  for (int angle = 90; angle <= 180; angle += 2) {
    liftServo.write(angle);
    delay(tt);
  }

  // Move the pivot servo from 90 to 0
  for (int angle = 90; angle >= 0; angle -= 2) {
    pivotServo.write(angle);
    delay(tt);
  }

  // Move the lift servo from 180 to 90
  for (int angle = 180; angle >= 90; angle -= 2) {
    liftServo.write(angle);
    delay(tt);
  }
}
             
             // Move Spider  Robot Right logic
void moveLeg_Right(Servo& liftServo, Servo& pivotServo , Servo& oppositePivotServo)
{
  // Move the lift servo from 90 to 180
  for (int angle = 90; angle <= 180; angle += 2) {
    liftServo.write(angle);
    delay(t);
  }

  // Move the pivot servo from 90 to 0
  for (int angle = 90; angle >= 0; angle -= 2) {
    pivotServo.write(angle);
    delay(t);
  }

  // Move the opposite pivot servo from 0 to 90
  for (int angle = 0; angle <= 90; angle += 2) {
    oppositePivotServo.write(angle);
    delay(t);
  }

  // Move the lift servo from 90 to 180
  for (int angle = 180; angle >= 90; angle -= 2) {
    liftServo.write(angle);
    delay(t);
  }
}

          // Move Spider  Robot Left logic
void moveLeg_Left(Servo& liftServo, Servo& pivotServo , Servo& oppositePivotServo)
{
  // Move the lift servo from 90 to 180
  for (int angle = 90; angle <= 180; angle += 2) {
    liftServo.write(angle);
    delay(t);
  }

  // Move the pivot servo from 90 to 180
  for (int angle = 90; angle <= 180; angle += 2) {
    pivotServo.write(angle);
    delay(t);
  }

  // Move the opposite pivot servo from 180 to 90
  for (int angle = 180; angle >= 90; angle -= 2) {
    oppositePivotServo.write(angle);
    delay(t);
  }

  // Move the lift servo from 180 to 90
  for (int angle = 180; angle >= 90; angle -= 2) {
    liftServo.write(angle);
    delay(t);
  }
}

void bow()
{
  center_servos();
  delay(200);
  ServoFLL.write(15);
  ServoFRL.write(15);
  delay(700);
  ServoFLL.write(90);
  ServoFRL.write(90);
  delay(700);
}

void lean_left()
{
  ServoFLL.write(15);
  ServoBLL.write(15);
  ServoBRL.write(150);
  ServoFRL.write(150);
}

void lean_right()
{
  ServoFLL.write(150);
  ServoBLL.write(150);
  ServoBRL.write(15);
  ServoFRL.write(15);
}

      // All Servos Centor function  
void center_servos()
{
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
}

       // Move Spider Robot Forward Function
void moveLegServos_Forward()
{
  // Control the servo actions for each leg
  
  // Left side leg - Leg FR
  moveLeg_Left_Forward(ServoFRL, ServoFRP, ServoFRL);
  
  // Left side leg - Leg FL
  moveLeg_Left_Forward(ServoFLL, ServoFLP, ServoFLL);
  
  // Left side leg - Leg FR and Leg FL
  for (int angle = 0; angle <= 90; angle += 2) {
    ServoFRP.write(angle);
    ServoFLP.write(angle);
    delay(tt);
  }
  
  // Right side leg - BR
  moveLeg_Right_Forward(ServoBRL, ServoBRP, ServoBRL);
  
  // Right side leg - BL
  moveLeg_Right_Forward(ServoBLL, ServoBLP, ServoBLL);
  
  // Right side leg - BR and BL
  for (int angle = 180; angle >= 90; angle -= 2) {
    ServoBRP.write(angle);
    ServoBLP.write(angle);
    delay(tt);
  }
}  
  //-------------------------------------------------------//
      // Move Spider Robot Backward Function
void moveLegServos_Backward()
{
   
   // Control the servo actions for each leg
  // Left side leg - Leg FL
  moveLeg_Left_Backward(ServoFLL, ServoFLP, ServoFLL);

  // Left side leg - Leg FR
  moveLeg_Left_Backward(ServoFRL, ServoFRP, ServoFRL);

  // Left side leg - Legs 1 and 4
  for (int angle = 180; angle >= 90; angle -= 2) {
    ServoFRP.write(angle);
    ServoFLP.write(angle);
    delay(tt);
  }

  // Right side leg - Leg BL
  moveLeg_Right_Backward(ServoBLL, ServoBLP, ServoBLL);

  // Right side leg - Leg BR
  moveLeg_Right_Backward(ServoBRL, ServoBRP, ServoBRL);

  // Right side leg - Legs 2 and 3
  for (int angle = 0; angle <= 90; angle += 2) {
    ServoBLP.write(angle);
    ServoBRP.write(angle);
    delay(tt);
  }
}
                
         // Move Spider Robot Right Function
 void moveLegServos_Right() {
  // Control the Right turn servo actions for each leg
  moveLeg_Right(ServoFRL, ServoFRP, ServoBRP); 
  moveLeg_Right(ServoFLL, ServoFLP, ServoFRP); 
  moveLeg_Right(ServoBLL, ServoBLP, ServoFLP); 
  moveLeg_Right(ServoBRL, ServoBRP, ServoBLP); 
}

       // Move Spider Robot Left Function   
void moveLegServos_Left() {
  // Control the Left turn servo actions for each leg
  moveLeg_Left(ServoFRL, ServoFRP, ServoFLP); 
  moveLeg_Left(ServoBRL, ServoBRP, ServoFRP); 
  moveLeg_Left(ServoBLL, ServoBLP, ServoBRP); 
  moveLeg_Left(ServoFLL, ServoFLP, ServoBLP); 
}
  
 /*      //  Spider Robot dance Function
void dance(){
    // Move the selected servos from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle += 2) {
    myServo1.write(angle);
    myServo3.write(angle);
    myServo5.write(angle);
    myServo7.write(angle);
    delay(t);  // Delay between each angle change (adjust as needed)
  }

  // Move the selected servos from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle -= 2) {
    myServo1.write(angle);
    myServo3.write(angle);
    myServo5.write(angle);
    myServo7.write(angle);
    delay(t);  // Delay between each angle change (adjust as needed)
  }
  
center_servos();
  delay(100);
  lean_left();
  delay(300);
  lean_right();
  delay(300);
  lean_left();
  delay(300);
  lean_right();
  delay(300);
  lean_left();
  delay(300);
  lean_right();
  delay(300);
  lean_left();
  delay(300);
  lean_right();
  delay(500);
  center_servos();
  delay(300);
  bow();
  center_servos();
}

         //  Spider Robot pushup Function    
void pushup(){
    // Move the selected servos from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle += 2) {
    myServo2.write(angle);
    myServo4.write(angle);
    myServo6.write(angle);
    myServo8.write(angle);
    delay(10);  // Delay between each angle change (adjust as needed)
  }

  // Move the selected servos from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle -= 2) {
    myServo2.write(angle);
    myServo4.write(angle);
    myServo6.write(angle);
    myServo8.write(angle);
    delay(10);  // Delay between each angle change (adjust as needed)
  }
}
*/
                           
          // Move Spider Robot Forward logic
void loop(){

  delay(10000);
  center_servos();
  stand_up();
  delay(100000000000);

/*
{
   //Move Forward 10 step 
  for (int i = 0; i < 10; i++) {
    moveLegServos_Forward();
  }
  center_servos();
  delay(FUNCTION_DELAY);
         
    // Move Backward 10 step
  for (int i = 0; i < 10; i++) {
    moveLegServos_Backward();
 }
  center_servos();
  delay(FUNCTION_DELAY);
    // Move Right 10 step
  for (int i = 0; i < 10; i++) {
    moveLegServos_Right();
  }
  center_servos();
  delay(FUNCTION_DELAY);
    // Move Left 10 step
  for (int i = 0; i < 10; i++) {
    moveLegServos_Left();
  }
  center_servos();
  delay(FUNCTION_DELAY);
  
  /*
   //  dance 10 step
  for (int i = 0; i < 5; i++) {
    dance();
  }
  center_servos();
  delay(FUNCTION_DELAY);
   // pushup 10 step
  for (int i = 0; i < 10; i++) {
    pushup();
  }
  center_servos();
  delay(FUNCTION_DELAY);
  */
  
}

