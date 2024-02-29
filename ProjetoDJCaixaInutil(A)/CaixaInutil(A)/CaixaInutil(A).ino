// impressão 3d
// versão 1.3
// DJEDU28 (https://github.com/djedu28)


#define pinServo 9
#define pinBtn 7

// Inclui a biblioteca
#include <Servo.h> 

// macro
#define btnPress !digitalRead(pinBtn)

Servo alavanca;

int min_pos = 30;
int max_pos = 160;
//int mid_pos = min_pos+(max_pos-min_pos)/2;

const int provocar_min_pos = 60;
const int provocar_max_pos = 145;

unsigned long last_click_timestamp = 0;
int fast_clicks = 0;
bool provocar_mode = false;
 
void setup() 
{ 
  alavanca.write(min_pos);
  alavanca.attach(pinServo);
  
  pinMode(pinBtn, INPUT_PULLUP);

  randomSeed(analogRead(0));

  Serial.begin(9600);
  Serial.println("Iniciando");
  
  //calibrar();

  last_click_timestamp = millis();
} 

void loop(){ 

  int speed1 = random(2, 5);
  int speed2 = random(2, 8);

  if(deve_provocar())
    provocar();

  // Dormir enquanto não está ligado
  // Aguarde o clique
  if(!btnPress)
    return;
    
  //Serial.println("ON!");
  
  verifique_se_incomodou();

  if(btnPress&&!provocar_mode){
    // Avançar até que o interruptor esteja desligado  
    move_servo(max_pos, speed1, true);

    //Serial.println("OFF");

    // Agora mova para trás até min pos ou usuário clicar em alternar novamente
    move_servo(min_pos, speed2, true);
    
    //Serial.println("End of lopp");
  }
  //delay();
} 



// funções
bool move_servo(int end_pos, int step_delay, bool look_for_switch) {
  int cur_pos = alavanca.read();

  // Check if we are already there
  if(cur_pos == end_pos) {
    //Serial.println("Already there");
    return true;
  }

  // Move from current position to the end position  
  int servo_step = cur_pos < end_pos ? 1 : -1;
  bool switching_state = (cur_pos >= end_pos);
  for(; cur_pos != end_pos; cur_pos += servo_step)
  {                                
    alavanca.write(cur_pos);
    delay(step_delay);

    // If servo is moving forward - expect for switch off
    // if moving backward - switch on will break the loop
    if(look_for_switch && (btnPress == switching_state))
    {
      //Serial.println("Switch change detected");
      return false;
    }
  } 
  
  //Serial.println("Move done");
  return true;
}

void provocar() {

  Serial.println("Provocando!");
  
  move_servo(provocar_min_pos, random(4, 6), false);
  delay(200 + random(2000));
  
  do {
    Serial.println("Laço de provocação!");

    if(btnPress) // O usuário clicou novamente no botão
      return;
    
    move_servo(provocar_max_pos, random(2, 6), false);
    delay(random(1000)); 
    move_servo(provocar_min_pos, random(4, 6), false);
    delay(200 + random(2000));  
  }

  while(random(5) > 2);

  if(btnPress) // O usuário clicou novamente no botão
    return;
  
  Serial.println("Saindo do loop de provocação!");
  move_servo(min_pos, random(4, 6), false);
  
  // Não provoque mais
  if(random(5) > 2)
  {
    Serial.println("Não provoca mais!");
    provocar_mode = false;
  }
}

void verifique_se_incomodou(){

  const int fast_click_threshold = 2000; //2 seconds
  const int clicks_for_provocar_mode = 4;

  unsigned long cur_timestamp = millis();
  
  // Verifique se o clique anterior não foi muito longo
  if(cur_timestamp - last_click_timestamp > fast_click_threshold) {
    // Se o último clique foi muito antigo (usuário normal) - redefina o contador de cliques
    Serial.println("Clique lento!");
    fast_clicks = 0;
  }
  else {
    // Nosso usuário é nerd de cliques
    Serial.println("Clique rápido!");
    fast_clicks++;
  }
  
  last_click_timestamp = cur_timestamp;
  
  // Se o usuário nos incomodar clicando - entre no modo de provocação
  if(fast_clicks > clicks_for_provocar_mode) {
    Serial.println("Modo de provocação");
    provocar_mode = true;
  }
}

bool deve_provocar(){

  const int provocar_threshold = 1000; //4 segundos após o último clique

  unsigned long cur_timestamp = millis();

  // Verifique se não houve ação durante os últimos segundos para que possamos provocar
  if(provocar_mode && (cur_timestamp - last_click_timestamp > provocar_threshold))
    return true;
    
  return false;
}

void calibrar(){
  
  Serial.begin(9600);
  int ang = 90;
  while (1){
    if (Serial.available()) {
      ang = Serial.parseInt();
    }
    alavanca.write(ang);
    delay(10);
  }
}