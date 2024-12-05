#define trigPin 13
#define echoPin 12

#include <ESP32Servo.h>

#define SERVO_PIN 14

//teste
#define Rotacaoesquerda 33
#define andarfrente 25
#define Rotacaodireita 26
#define para 27

Servo ultrassomservo;

int distanceD, distanceE, distanceB;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  ultrassomservo.attach(SERVO_PIN);
  ultrassomservo.write(90); // Inicializa o servo parado



  pinMode(Rotacaoesquerda, OUTPUT);
  pinMode(andarfrente, OUTPUT);
  pinMode(Rotacaodireita, OUTPUT);
  pinMode(para, OUTPUT);

  digitalWrite(Rotacaoesquerda, HIGH);
  delay(1000);
  digitalWrite(Rotacaoesquerda, LOW);

  digitalWrite(andarfrente, HIGH);
  delay(1000);
  digitalWrite(andarfrente, LOW);

  digitalWrite(Rotacaodireita, HIGH);
  delay(1000);
  digitalWrite(Rotacaodireita, LOW);

  digitalWrite(para, HIGH);
  delay(1000);
  digitalWrite(para, LOW);



}

//--------------------------------------------------------- Função para medir a distância usando o sensor ultrassônico-------------------------------------------------------------------------//
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

//-----------------------------------------------------------movimentação (teste com LEDS)------------------------------------------------------------//

void Andar_em_frente(){
  digitalWrite(andarfrente, HIGH);  
  delay(1000);                      
  digitalWrite(andarfrente, LOW);   

}

void Andar_rodar90_E(){
  digitalWrite(Rotacaoesquerda, HIGH);  
  delay(1000);                      
  digitalWrite(Rotacaoesquerda, LOW);   

}

void Andar_rodar90_D(){
  digitalWrite(Rotacaodireita, HIGH);  
  delay(1000);                      
  digitalWrite(Rotacaodireita, LOW);   

}

void Parar(){
  digitalWrite(para, HIGH);  
  delay(1000);                      
  digitalWrite(para, LOW);   

}

//----------------------------------------------------------------------fim da movimentação-----------------------------------------------------------//

//-------------------------------------------------------------decisao de caminho ---------------------------------------------------------------------------------//

void decisao_de_caminho(int distance, int distanceD, int distanceE){
  if(distance > 5){
    Andar_em_frente();                                                                                                                    //RETIRAR
  }if(distanceD -3 > distanceE){
    Andar_rodar90_D();                                                                                                                    //RETIRAR
  }if(distanceE -3 > distanceD){
    Andar_rodar90_E();                                                                                                                    //RETIRAR
  }if(distanceD +3 > distanceE && distanceD -3 < distanceE || distanceE +3 > distanceD && distanceE -3 < distanceD){
    Andar_rodar90_D();                                                                                                                    //RETIRAR
    Andar_rodar90_D();                                                                                                                    //RETIRAR
  }
}

//--------------------------------------------------------- Função para controlar o servo contínuo com base na distância--------------------------------------------------------------------------//
void controlContinuousServo(int distance) {

  if (distance <= 5) {

    Serial.println("Distância < 5 cm: Movendo o servo...");
    Parar();                                                                                                                   //RETIRAR
    // Gira levemente para a direita
    ultrassomservo.write(70); // Valor menor que 90 para girar à direita
    delay(600);
    // Ele para de rodar
    ultrassomservo.write(90);
    delay(2000);
    distanceD = measureDistance();
    Serial.print("Distância direita = "); Serial.println(distanceD);

    // Gira levemente para a esquerda
    ultrassomservo.write(110); // Valor maior que 90 para girar à esquerda
    delay(1350);
    // Ele para de rodar
    ultrassomservo.write(90);
    delay(2000);
    distanceE = measureDistance();
    Serial.print("Distância esquerda = "); Serial.println(distanceE);

  /*
    //-----------------------------------------------------------------180º-------------------------------------------------------------------------// 
    if(distanceD+3 > distanceE && distanceD-3 < distanceE || distanceE+3 > distanceD && distanceE-3 < distanceD){
          // Gira levemente para a esquerda
    ultrassomservo.write(110); // Valor maior que 90 para girar à esquerda
    delay(700);
    // Ele para de rodar
    ultrassomservo.write(90);
    delay(2000);
    distanceB = measureDistance();
    Serial.print("Distância de trás = "); Serial.println(distanceB);          //SERVO A RODAR PARA TRAS  (PODE NAO SER NECESSARIO)

        // Gira levemente para a direita para a posicao inicial
    ultrassomservo.write(70); // Valor menor que 90 para girar à direita
    delay(1150);
    // Para o servo
    ultrassomservo.write(90);
    delay(1000);

    }else{
  */

    // Gira levemente para a direita para a posicao inicial
    ultrassomservo.write(70); // Valor menor que 90 para girar à direita
    delay(620);
    // Para o servo
    ultrassomservo.write(90);
    delay(1000);

    decisao_de_caminho(distance, distanceD, distanceE);

    }
   else {
    Serial.println("Distância > 5 cm: Servo parado.");
    ultrassomservo.write(90); // Servo parado
    Andar_em_frente();                                                                                                                    //RETIRAR
  }
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------//


void loop() {

  int distance = measureDistance(); // Medir a distância
  Serial.print("Distância medida: ");
  Serial.print(distance);
  Serial.println(" cm");

  controlContinuousServo(distance); // Controlar o servo com base na distância
  delay(500); // Intervalo entre as medições
}

