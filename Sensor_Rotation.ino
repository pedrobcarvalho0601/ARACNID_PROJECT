#define trigPin 13
#define echoPin 12

#include <Servo.h>

#define SERVO_PIN 11

Servo s;

long measureDistance() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration / 58; // Conversão para cm
  return distance;
}

void controlContinuousServo() {
  int distance = measureDistance();

  if (distance > 5){
    s.write(90); 
  }

  if (distance <= 5) { 
    // Para o servo (posição neutra)
    s.write(90); 
    delay(1500); 
    
    // Gira para a esquerda (valor menor que 90)
    s.write(89); // Ajuste conforme necessário
    delay(1000);
    
    // Gira para a direita (valor maior que 90)
    s.write(91); // Ajuste conforme necessário
    delay(1000);
    
    // Para o servo novamente
    s.write(90); 
    delay(1000);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  s.attach(SERVO_PIN);
  s.write(90); // Inicializa o servo parado
}

void loop() {
  Serial.println(measureDistance());
  controlContinuousServo();
  delay(500);
}
