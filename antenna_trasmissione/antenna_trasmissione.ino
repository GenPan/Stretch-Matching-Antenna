/* 1byte 433Mhz TRANSMITTER example.
/* Tutorial link: http://electronoobs.com/eng_arduino_tut99.php
 * Code: http://electronoobs.com/eng_arduino_tut99_code1.php
 * Scheamtic: http://electronoobs.com/eng_arduino_tut99_sch1.php
 * Youtube Channel: http://www.youtube/c/electronoobs   
// Arduino          433Mhz Tx
// GND              GND
// 5V               VCC
// D3               Data
*/

#include <VirtualWire.h> //Download it here: http://electronoobs.com/eng_arduino_virtualWire.php
#define size 1
int pot = A0;
byte TX_buffer[size]={0};
byte i;


void setup() 
{
  // virtual wire+
  vw_set_tx_pin(3); // pin
  vw_setup(2000); // bps
  for(i=0;i<size;i++)
  {
     TX_buffer[i]=i;
  }
}

void loop()
{ 
  int val = map(analogRead(pot),0,1024,0,255);
  TX_buffer[0] = val;  
  vw_send(TX_buffer, size); 
  vw_wait_tx(); 
  delay(10);
}
