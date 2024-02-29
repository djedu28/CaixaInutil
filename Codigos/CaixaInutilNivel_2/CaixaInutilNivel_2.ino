#include <Servo.h>

Servo meuServo;
const int pinoChaveAlavaca = 7;
const int pinoServo = 9;

int contadorPressionamentos = 0;
unsigned long tempoUltimoPressionamento = 0;

void setup() {
 meuServo.attach(pinoServo); // Conecta o servo no pino 9
 meuServo.write(90); // Move o servo para 90 graus
 pinMode(pinoChaveAlavaca, INPUT_PULLUP); // Configura o pino da chave alavanca como entrada
}

void loop() {
 int estadoChave = digitalRead(pinoChaveAlavaca); // Lê o estado da chave alavanca

 if (estadoChave == LOW) { // Se a chave estiver ativa (LOW)
    meuServo.write(0); // Move o servo para 0 graus
    if (millis() - tempoUltimoPressionamento < 30000) { // Verifica se o último pressionamento foi dentro de 30 segundos
      
      contadorPressionamentos++; // soma mais um no contador

      if (contadorPressionamentos >= 3) { // Se a chave foi pressionada 3 vezes seguidas
        // Abre e fecha a tampa com raixa
        for (int x =0; x<=4;x++;){
            meuServo.write(50);
            delay(10)
            meuServo.write(10);
            delay(10)
        }
        meuServo.write(0);// Move o servo para 0 graus (com raiva)
        contadorPressionamentos = 0; // Reseta o contador de pressionamentos
      }
    } else {
      contadorPressionamentos = 1; // Reseta o contador de pressionamentos se passar mais de 1 segundo
    }
    tempoUltimoPressionamento = millis(); // Atualiza o tempo do último pressionamento
 } else {
    meuServo.write(90); // Move o servo para 90 graus
 }
}