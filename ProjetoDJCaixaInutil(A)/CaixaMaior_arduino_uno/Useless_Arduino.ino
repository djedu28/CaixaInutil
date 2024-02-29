/*Connect the black/brown servo wire to the ground of your Arduino
Connect the red servo wire to the 5V pin of your Arduino
Connect the white/yellow servo wire to pin 9
Connect one side of the switch to pin 10
Connect the other side of the switch to the ground
(switch should be open when it's pointing in the direction of the flap)
*/


#include <Servo.h> 
Servo servo_1; 
int pos = 0; 
int switchState; 
int switchInit;
bool inizio;
bool demo;
unsigned long time; //tempo di accensione
long randNumber;
long tempo_trascorso;
long durata;
long demotime;
long demoaction;

void setup() 
{ 
	Serial.begin(9600);
	servo_1.attach(9); 
	pinMode(10, INPUT); 
	digitalWrite(10, HIGH); 
	switchInit = digitalRead(10); 
	servo_1.write(102); 
	inizio	=false;
	demo=false;
	if(switchInit==LOW) {
		demo=true;	
	}
	
	
	delay(50);
	
	//demo=true; delay(500); 	ApriDemo6();
	tempo_trascorso=0;
	time =0 ;
} 
void loop(){ 
	//time = millis(); //lettura tempo di accensione
	randNumber = random(1, 10);
	
	switchState = digitalRead(10);	//lettura interruttore

	durata=tempo_trascorso-time;

	//Serial.println(durata);
	//Serial.println(tempo_trascorso);
		
	if (demo==true){
		demotime =random(6000,12000);
		if (durata>demotime){
			
			switch (randNumber) {
				case 1: ApriDemo1();
				case 2: ApriDemo2();
				case 3: ApriDemo3();
				case 4: ApriDemo4();
				case 5: ApriDemo5();
				case 6: ApriDemo6();
			}
			time=millis();
		}
			else
		{
			if(switchState==LOW)
			{
				Apri();
				time=millis();
			}
		}
		
	}
	
	if (demo==false){
		if(switchState==LOW)
		{
			Apri();
		}
		
	}
	

	delay(5); 
	tempo_trascorso=millis();

}

void Apri(){
	delay(50);
	servo_1.write(0);
	delay(300);
	for(pos = 0; pos < 110; pos+=3){
		servo_1.write(pos);
		delay(5);
	}

}

void ApriDemo1(){
	delay(50);
	servo_1.write(10);	delay(1000);
	servo_1.write(30);	delay(500);
	servo_1.write(130);	delay(1000);
}

void ApriDemo2(){
	delay(50);
	servo_1.write(10); 		delay(1000);
	servo_1.write(80); 		delay(500);
	servo_1.write(10);		delay(500);
	servo_1.write(130); 	delay(1000);
}

void ApriDemo3(){
	delay(50);
	servo_1.write(30);	delay(2000);
	servo_1.write(80);	delay(300);
	servo_1.write(130);	delay(1000);
}

void ApriDemo4(){
	delay(50);
	servo_1.write(30);	delay(3000);
	servo_1.write(20);	delay(300);
	servo_1.write(30);	delay(300);
	servo_1.write(10);	delay(300);
	servo_1.write(30);	delay(300);
	servo_1.write(130);	delay(1000);
}

void ApriDemo5(){
	delay(50);
	servo_1.write(30);	delay(1000);
	servo_1.write(120);	delay(2000);
	servo_1.write(50);	delay(2000);
	servo_1.write(120);	delay(1000);
	//servo_1.write(30);	delay(300);
	//servo_1.write(130);	delay(1000);
}

void ApriDemo6(){
	delay(50);
	
	
	for(pos = 0; pos < 20; pos+=1){
		demoaction=random(20,120);
		servo_1.write(demoaction);
		//Serial.println(pos);
		delay(100);
	}

	servo_1.write(120);	delay(1000);
}
