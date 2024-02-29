#include <Servo.h>

Servo meuServo;
const int pinoChaveAlavaca = 7;
const int pinoServo = 9;


void setup() {
 meuServo.attach(pinoServo); // Conecta o servo no pino 9
 meuServo.write(90); // Move o servo para 90 graus
 pinMode(chaveAlavaca, INPUT_PULLUP); // Configura o pino da chave alavanca como entrada
}

void loop() {
 int estadoChave = digitalRead(chaveAlavaca); // Lê o estado da chave alavanca

 if (estadoChave == LOW) { // Se a chave estiver ativa (LOW)
    meuServo.write(0); // Move o servo para 0 graus
 } else {
    meuServo.write(90); // Move o servo para 90 graus
 }
}
