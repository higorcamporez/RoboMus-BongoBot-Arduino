#include <Servo.h>

#define PORTA_BONGO_GRAVE 9
#define PORTA_BONGO_AGUDO 10
#define ANGULO_DESCIDA_A 20
#define ANGULO_SUBIDA_A 5
#define ANGULO_DESCIDA_G 30 
#define ANGULO_SUBIDA_G 10

#define TEMPO_A 65 
#define TEMPO_G 65 

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
  
  bongoGrave.write(ANGULO_SUBIDA_G);
  bongoAgudo.write(ANGULO_SUBIDA_A);

  delay(500);
   
}

void tocar(Servo bongo,int anguloDescida, int anguloSubida, int tempo){
  bongo.write(anguloDescida);
  delay(tempo);
  bongo.write(anguloSubida);
}

void tocar(char bongo, int tempo){
  if(bongo == 'A'){
    tocar(bongoAgudo, ANGULO_DESCIDA_A, ANGULO_SUBIDA_A,tempo);
  }else{
    tocar(bongoGrave, ANGULO_DESCIDA_G, ANGULO_SUBIDA_G,tempo);
  }
}

void tocar(char bongo){

  //int tempo = nextMessage.data[0]<<8 | nextMessage.data[1];
  if(bongo == 'A'){
    tocar(bongo,TEMPO_A);
  }else{
    tocar(bongo,TEMPO_G);
  }
  
}

void tocarJunto(
                int anguloDescidaA,
                int anguloDescidaG,
                int anguloSubidaA,
                int anguloSubidaG,
                int tempo
                ){
                  
  bongoGrave.write(anguloDescidaG);
  bongoAgudo.write(anguloDescidaA);
  delay(tempo);
  bongoAgudo.write(anguloSubidaA);
  bongoGrave.write(anguloSubidaG);
}

void tocarJunto(int tempo){
  
  tocarJunto( ANGULO_DESCIDA_A, 
              ANGULO_DESCIDA_G,
              ANGULO_SUBIDA_A,
              ANGULO_SUBIDA_G,
              tempo);
}
void tocarJunto(){
  tocarJunto(TEMPO_A+8);
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
            tocar('G', tempo);
          break;
        }
   }
}
/*
void ritmo1(int tempo){

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
    delay(2*tempo - 60);
    tocar(bongoAgudo, 60);
    delay(1*tempo - 60);
    tocar(bongoGrave, 60);
    delay(1*tempo - 60);
    tocar(bongoGrave, 60);
    delay(2*tempo - 60);
    tocar(bongoAgudo, 60);
    //tocarJunto();
    delay(2*tempo - 60);
    

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
} */
int i = 0, medAnt=0, med;
void interrupcao(){
  med = millis();
  if(med - medAnt > 50 ){
    Serial.println(millis());
    medAnt =  med;
  }
 

 }   
void setup() {
  
  Serial.begin(9600);

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  iniciarServos();
  
  initialTime = millis();
  nextMessage.relativeTime = 0x7FFF;
  
  /*teste*/
  //tocarJunto();
  attachInterrupt(0,interrupcao,RISING);
  
  
}
/*
void loop(){
  tocar(bongoGrave, 50);
  delay(75);
  //Serial.println(analogRead(A1));
}
*/

void loop()
{ 
  //ritmo5(200);
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
        case 10://tocar bongo grave def
          
          //nextMessage.data[0] = Serial.read();
          //nextMessage.data[1] = Serial.read();
          
          readNewMsg = 0;
          
        break;
        case 20://tocar bongo grave    def
          //nextMessage.data[0] = Serial.read();
          //nextMessage.data[1] = Serial.read(); 
          readNewMsg = 0;
   
        break;
        case 30://playBongoTogetherDef 
          readNewMsg = 0;
        break;
        case 40://playBongoTogether
          nextMessage.data[0] = Serial.read(); //angulo de descida
          nextMessage.data[1] = Serial.read(); //angulo de subida
          readNewMsg = 0;
        break;
        case 50://playBongoG
          nextMessage.data[0] = Serial.read(); //angulo de descida
          nextMessage.data[1] = Serial.read(); //angulo de subida
          readNewMsg = 0;
        break;
        case 60://playBongoA
          nextMessage.data[0] = Serial.read(); //angulo de descida
          nextMessage.data[1] = Serial.read(); //angulo de subida
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
        case 10://playBongoDefG
          tocar('G');
          Serial.write(currentMessage.idMessage);
        break;
        case 20://playBongoDefA
          tocar('A');
          Serial.write(currentMessage.idMessage);
        break;
        case 30://playBongoTogetherDef
          tocarJunto();
          Serial.write(currentMessage.idMessage);
        break;
        case 40://playBongoTogether
          /*tocarJunto(currentMessage.data[0],
                     currentMessage.data[1],
                     currentMessage.duration);
          Serial.write(currentMessage.idMessage);*/
        break;
        case 50://playBongoG
          tocar(bongoGrave,
                currentMessage.data[0],
                currentMessage.data[1],
                currentMessage.duration);
          Serial.write(currentMessage.idMessage);
        break;
        case 60://playBongoA
          tocar(bongoAgudo,
                currentMessage.data[0],
                currentMessage.data[1],
                currentMessage.duration);
          Serial.write(currentMessage.idMessage);
        break;
        
       }  
    }/*else{ //preparacao
      
      switch (nextMessage.idAction){
        case 10:
        //funcao pra isso

        break;
        case 20:
        //funcao pra isso


        break;
        
       }
         
    }*/
    
  }
  
}
