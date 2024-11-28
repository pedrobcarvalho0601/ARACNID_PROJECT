#define trigPin 13
#define echoPin 12

#include <ESP32Servo.h>

#define SERVO_PIN 18

Servo s;

float distanceD, distanceE, distanceB;

// Função para medir a distância usando o sensor ultrassônico
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

// Função para controlar o servo contínuo com base na distância
void controlContinuousServo(int distance) {
  if (distance <= 5) {
    Serial.println("Distância < 5 cm: Movendo o servo...");
    
    // Gira levemente para a direita
    s.write(70); // Valor menor que 90 para girar à direita
    delay(600);
    // Ele para de rodar
    s.write(90);
    delay(2000);
    distanceD = measureDistance();
    Serial.print("Distância direita = "); Serial.println(distanceD);

    // Gira levemente para a esquerda
    s.write(110); // Valor maior que 90 para girar à esquerda
    delay(1460);
        // Ele para de rodar
    s.write(90);
    delay(2000);
    distanceE = measureDistance();
    Serial.print("Distância esquerda = "); Serial.println(distanceE);

    // Gira levemente para a direita para a posicao inicial
    s.write(70); // Valor menor que 90 para girar à direita
    delay(660);
    // Para o servo
    s.write(90);
    delay(1000);

  } else {
    Serial.println("Distância > 5 cm: Servo parado.");
    s.write(90); // Servo parado
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  s.attach(SERVO_PIN);
  s.write(90); // Inicializa o servo parado

  Serial.println("Sistema iniciado!"); // Mensagem inicial no monitor serial
}

void loop() {
  int distance = measureDistance(); // Medir a distância
  Serial.print("Distância medida: ");
  Serial.print(distance);
  Serial.println(" cm");

  controlContinuousServo(distance); // Controlar o servo com base na distância
  delay(500); // Intervalo entre as medições
}

