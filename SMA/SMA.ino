#include <VirtualWire.h>

int fr; 
unsigned long At = 500 ;

int SMA1 = 3;  
int M1 = 12;
int SMA2 =11;                        
int M2 = 13;                          

void setup()
{
    Serial.begin(9600); 

      fr = number_lecture(At) ;
  
    vw_set_tx_pin(M1); 
    vw_setup(3000);
    
    pinMode(M2, OUTPUT);
    
    pinMode(SMA1, OUTPUT);  
    pinMode(SMA2, OUTPUT);

    analogWrite(SMA2, 0);
    analogWrite(SMA2, 0);
}

void loop()
{    

 Serial.println(fr); 
 
  move(SMA1,SMA2);
   
}

void move( int S1 , int S2 ){
  
  analogWrite(S2, 255 ) ; 
  }

int number_lecture( unsigned long Time_waiting ){
  
  int num ;
  char Data[8];
  int i ; 
  unsigned long T ; 

  do {
    if(Serial.available()>0){
      Data[i] = Serial.read();
      i++; 
    }
    if(i<1) {
      T = millis() ; 
    }
  }while(i<6 && (millis()- T )< Time_waiting ); 

    Data[i] = 0 ; 
  num = atoi(Data); 
 i=0 ; 

  return num ; 
  }
