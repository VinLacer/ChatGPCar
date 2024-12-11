#include<SoftwareSerial.h>
int tempo;
String receivedString = "";
String comando = "";
SoftwareSerial bt(2,3);
float aux = 0.45;

class DCMotor {  
  int spd = 255, pin1, pin2;
  public:  
  
    void Pinout(int in1, int in2){ 
      pin1 = in1;
      pin2 = in2;
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      }   
    void Speed(int in1){ 
      spd = in1;
      }     
    void Forward(){ 
      analogWrite(pin1, spd);
      digitalWrite(pin2, LOW);
      }   
    void Backward(){ 
      digitalWrite(pin1, LOW);
      analogWrite(pin2, spd);
      }
    void Stop(){ 
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      }
   };

   DCMotor Motor1, Motor2; 

void TurnLeft(int t){
  Serial.println("ESQUERDA");
  Motor1.Forward();
  delay(t*aux);
  Motor1.Stop();
}

void TurnRight(int t){
  Serial.println("DIREITA");
  Motor2.Forward();
  delay(t*aux);
  Motor2.Stop();
}

void CarForward(int t){
  Serial.println("FRENTE");
  Motor1.Forward();
  Motor2.Forward();
  delay(t);
  Motor1.Stop();
  Motor2.Stop();
}

void CurvaDireita(int t){
  Serial.println("CURVA PARA A DIREITA");
  Motor1.Speed(120);
  Motor2.Forward();
  Motor1.Forward();
  delay(t);
  Motor1.Stop();
  Motor2.Stop();
  Motor1.Speed(255);
}

void CurvaEsquerda(int t){
  Serial.println("CURVA PARA A DIREITA");
  Motor2.Speed(120);
  Motor1.Forward();
  Motor2.Forward();
  delay(t);
  Motor1.Stop();
  Motor2.Stop();
  Motor2.Speed(255);
}

void setup() {
  bt.begin(9600);
  Serial.begin(9600);
  Motor1.Pinout(5,6); 
  Motor2.Pinout(9,10);
   
}

void loop() {
   if (bt.available()){
        receivedString = bt.readString();
        for(int index = 0 ; index < receivedString.length(); index+=2){
            comando = receivedString[index];
            tempo = receivedString[index + 1] - '0';
            Serial.println("COMANDO");
            Serial.println(comando);
            Serial.println("TEMPO");
            Serial.println(tempo*1000);

            if (comando == "W"){
              CarForward(tempo*1000);
              
            }

            else if (comando == "R"){
              TurnRight(tempo*1000);
              
            }

            else if (comando == "L"){
              TurnLeft(tempo*1000);
              
            }

            else if (comando == "D"){
              CurvaDireita(tempo*1000);
            }

            else if (comando == "D"){
              CurvaEsquerda(tempo*1000);
            }

            else{
              Serial.println(comando);
              Motor1.Stop();
              Motor2.Stop();
            }
          }
      
    
    }
}
