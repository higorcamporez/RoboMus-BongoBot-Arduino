#include <Servo.h>

#define PORTA_BONGO_GRAVE 10
#define PORTA_BONGO_AGUDO 9
#define ANGULO_DESCIDA 18
#define ANGULO_SUBIDA 5
#define TEMPO 60 

struct Message{
  
  byte idAction;
  byte idMessage;
  short relativeTime;
  short duration;
  byte data[20];
  long initialTime;
  long finalTime;
  
};
struct Message currentMessage,nextMessage;

//flag que de termina se é pra ler nova mensagem
byte readNewMsg = 1;
byte firstByte;
//variaveis auxiliares
byte hByte;
byte lByte;
byte h2Byte;
byte l2Byte;

long initialTime;

Servo bongoGrave; 
Servo bongoAgudo;

void iniciarServos(){

  bongoGrave.attach(PORTA_BONGO_GRAVE);
  bongoAgudo.attach(PORTA_BONGO_AGUDO);
  
  bongoGrave.write(0);
  bongoAgudo.write(0);

  delay(500);
   
}

void tocar(Servo bongo,int anguloDescida, int anguloSubida, int tempo){
  bongo.write(anguloDescida);
  delay(tempo);
  bongo.write(anguloSubida);
}

void tocar(Servo bongo, int tempo){
  tocar(bongo, ANGULO_DESCIDA, ANGULO_SUBIDA,tempo);
}

void tocar(Servo bongo){

  //int tempo = nextMessage.data[0]<<8 | nextMessage.data[1];
  tocar(bongo,TEMPO);
  
}

void tocarJunto(int anguloDescida, int anguloSubida, int tempo){
  bongoGrave.write(anguloDescida);
  bongoAgudo.write(anguloDescida);
  delay(tempo);
  bongoGrave.write(anguloSubida);
  bongoAgudo.write(anguloSubida);
}

void tocarJunto(int tempo){
  tocarJunto(ANGULO_DESCIDA,ANGULO_SUBIDA,tempo);
}
void tocarJunto(){
  tocarJunto(TEMPO);
}
// funcoes para teste 
void testAngulo(){
  int angulo;
   if (Serial.available() >= 3) {
        char fb = Serial.read();
        switch(fb){
          case 'a'://axx
            angulo = 10*(Serial.read() - 48);
            
            angulo += (Serial.read() - 48);
            Serial.println(angulo);
            tocar(bongoGrave,angulo, 0, 20);
          break;
          case 't'://txx
            int tempo = 10*(Serial.read() - 48);
            
            tempo += (Serial.read() - 48);
            Serial.println(tempo);
            tocar(bongoGrave, tempo);
          break;
        }
   }
}
void ritmo1(int tempo){
    /*
    tocarJunto();
    delay(tempo);
    tocarJunto();
    delay(tempo); */

    tocar(bongoGrave, 60);
    delay(2*tempo);
    tocar(bongoAgudo, 60);
    delay(tempo);
    tocar(bongoAgudo, 60);
    delay(2*tempo);
    tocar(bongoGrave, 60);
    delay(tempo);
    tocar(bongoAgudo, 60);
    delay(2*tempo);

}
void ritmo2(int tempo){
    
    tocar(bongoGrave, 60);
    delay(tempo);
    tocar(bongoGrave, 60);
    delay(tempo);
    tocar(bongoGrave, 60);
    delay(tempo);
    tocar(bongoGrave, 60);
    delay(tempo);
    tocarJunto();
    delay(tempo);
    

}
void ritmo3(int tempo){
    
    tocar(bongoGrave, 60);
    delay(tempo);
    tocar(bongoGrave, 60);
    delay(tempo);
    tocar(bongoGrave, 60);
    delay(tempo);
    tocar(bongoAgudo, 60);
    //tocarJunto();
    delay(tempo);
    

}

void ritmo4(int tempo){
    
    tocar(bongoGrave, 60);
    delay(4*tempo - 60);
    tocar(bongoAgudo, 60);
    delay(2*tempo - 60);
    tocar(bongoGrave, 60);
    delay(2*tempo - 60);
    tocar(bongoGrave, 60);
    delay(4*tempo - 60);
    tocar(bongoAgudo, 60);
    //tocarJunto();
    delay(4*tempo - 60);
    

}

void ritmo5(int tempo){
    
    tocar(bongoGrave, 60);
    delay(3*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
    tocar(bongoAgudo, 60);
    delay(2*tempo - 60);
    tocar(bongoGrave, 60);
    delay(3*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
    tocar(bongoGrave, 60);
    delay(2*tempo - 60);
    tocar(bongoAgudo, 60);
    delay(4*tempo - 60);
    
}
void comeAsYouAre(int tempo){
    
    tocar(bongoGrave, 60);
    delay(2*tempo - 60);
    tocar(bongoAgudo, 60);
    delay(2*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
    tocar(bongoAgudo, 60);
    delay(1*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
    tocar(bongoAgudo, 60);
    delay(1*tempo - 60);
    tocar(bongoGrave, 60);
    delay(2*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
    tocar(bongoAgudo, 60);
    delay(1*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
}
   
void setup() {
  
  Serial.begin(9600);

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  iniciarServos();
  
  initialTime = millis();
  nextMessage.relativeTime = 0x7FFF;
  
  /*teste*/
  //tocar(bongoGrave,15, 0, 50);
  

}
/*
void loop(){
  ritmo4(150);
}

*/
void loop()
{
  if(readNewMsg){
    if(Serial.available() > 0){
      //Read the header
      firstByte = Serial.read();
      nextMessage.idAction = firstByte;
      //Serial.write(firstByte);
      delay(10);
      nextMessage.idMessage = Serial.read();
     
      hByte = Serial.read();
      h2Byte = Serial.read();
      lByte = Serial.read();
      l2Byte = Serial.read();
      
      nextMessage.relativeTime = hByte<<24 | h2Byte<<16 | lByte<<8 | l2Byte;
      
      hByte = Serial.read();
      lByte = Serial.read();
      nextMessage.duration = hByte<<8 |  (lByte);
      
      //end header
      
      switch (firstByte){
        case 10://tocar bongo grave
          
          //nextMessage.data[0] = Serial.read();
          //nextMessage.data[1] = Serial.read();
          
          readNewMsg = 0;
          
        break;
        case 20://tocar bongo grave
          
          //nextMessage.data[0] = Serial.read();
          //nextMessage.data[1] = Serial.read();
          
          readNewMsg = 0;
          
        break;
        
        
       }
    }   
  }else{
    //nextMessage.relativeTime = 3000;
    //nextMessage.duration = 5000;
    if( millis() >= (initialTime + nextMessage.relativeTime) 
       ){ //execucao
        
      currentMessage = nextMessage;
      readNewMsg = 1;
      if(currentMessage.relativeTime == 0){
        initialTime = millis();
      }
      switch (currentMessage.idAction){
        case 10://playString
          //funcao pra isso
          //currentMessage.initialTime = millis();
          
          tocar(bongoGrave);
          
          Serial.write(currentMessage.idMessage);
        break;
        case 20://playString
          //funcao pra isso
          //currentMessage.initialTime = millis();
          
          tocar(bongoAgudo);
          
          Serial.write(currentMessage.idMessage);
        break;
        
       }  
    }else{ //preparacao
      
      switch (nextMessage.idAction){
        case 10:
        //funcao pra isso
          digitalWrite(13,HIGH);
          delay(40);
          digitalWrite(13,LOW);
          delay(40);
        break;
        case 20:
        //funcao pra isso
          digitalWrite(13,HIGH);
          delay(40);
          digitalWrite(13,LOW);
          delay(40);

        break;
        
       }
         
    }
    
  }
  
} 
