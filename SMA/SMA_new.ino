#include <VirtualWire.h>
#define size 1

int fr ; //frequanza da raggiungere (mettiamo il valore noi per adesso)
int fa; //frequenza antenna
int fM = 434 ; //frequanza massima raggiungibile
int fm = 380 ; //frequanza minima raggiungibile

int SMA1 = 3; //molla principale (di movimento)
int SMA2 =11; //molla di bloccaggio (per lo schema provvisorio)  

int pot = A0;

byte TX_buffer[size]={0};
byte i;                     

void setup()
{
  
Serial.begin(9600); // si inizializza il monitor seriale
  
// virtual wire
vw_set_tx_pin(3); // pin
  vw_setup(2000); // bps
     
for(i=0;i<size;i++){
  TX_buffer[i]=i;
 }
    
pinMode(SMA1, OUTPUT); //si inizializza la porta SMA1
  pinMode(SMA2, OUTPUT); //si inizializza la porta SMA

analogWrite(SMA1, 0); //si spegne SMA1
  analogWrite(SMA2, 0); //si spegne SMA2
}

void loop()
{   

int val = map(analogRead(pot),0,1024,0,255);
  TX_buffer[0] = val;  
    vw_send(TX_buffer, size); 
      vw_wait_tx(); 
        
delay(500);   

if(fr =! fa){ move(SMA1,SMA2, fr, fa , fM , fm ); } // verifichiamo se la frequenza del segnale è uguale a quella della frequanza richiesta in caso non sia cosi facciamo il movimento
   
}

void move( int S1 , int S2 , int f , int fin, int fMax , int fMin ){
  
analogWrite(S2, 255 ) ; // si aprono i blocchi

int c = 3*(10^2); // velocità della luce 
  int difference; // differenza in percentuale tra fr e fa
    int LMax = (1/4)*(c/fMax) ; //lunghezza massima raggiungibile
      int LMin = (1/4)*(c/fMin) ; //lunghezza minima raggiungibile
        int La ; //lunghezza antenna
       
delay(1250);

do{
  
  if(fr>fa){ 
    difference = 1-((fa-fMin)/(fr-fMin)) ; //calcola la differenza
      analogWrite(S1, 255 * difference ) ; //la corrente uscente dipenderà dalla differenza tra le due frequenze (avanzamento graduale)
        La = (LMin*(LMin-LMax)*(fMax-fMin))/((LMax*(LMin^2)*(fin-fMin))+(LMin-LMax)*(fMax-fMin)) ; //si calcola la lunghezza ipotetica attuale in base alle frequenze che abbiamo
          Serial.println(La); //scrive sul monitor seriale la lunghezza in tempo reale
        }
        
  else if(fr<fa){ 
    analogWrite(S1, 0 ) ; //spegne SMA1 in modo tale che possa raffreddarsi ed accorciarsi
        La = (LMin*(LMin-LMax)*(fMax-fMin))/((LMax*(LMin^2)*(fin-fMin))+(LMin-LMax)*(fMax-fMin)) ; 
          Serial.println(La);
        }
        
delay(1250);

 }while(fr == fa);

analogWrite(S2, 0 ) ; //blocca l'antenna
}
