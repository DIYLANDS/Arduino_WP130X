#include <SoftwareSerial.h>

int RECV_PIN = 11;

#define BTN_PIN A3
#define BTN_DELAY 250
#define ADC3 A3
#define STAT_LED 9
#define RING_IN A0

decode_results results;

// Init Vars
uint8_t j = 0;
uint8_t i = 0;
uint8_t ring_in;
uint8_t button_state=0;
uint8_t button=0;
uint8_t loop_cnt = 0;
unsigned long mark;
uint8_t Call_state = 0;  // 0 : idle, 1 : Ringing, 2 : Call, 3 : Reinit

void setup()  
{
  
  pinMode(BTN_PIN, INPUT); 
  pinMode(RING_IN, INPUT); 
  pinMode(STAT_LED, OUTPUT);   
   
   digitalWrite(STAT_LED, HIGH);
   
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  while (!Serial) {
  
   }
  // set the data rate for the SoftwareSerial port
  
       Serial.println("ATZ");
       delay (500);    
      Serial.println("ATH");
       delay (500);    
        Serial.println("AT+FCLASS=8");
       delay (500);    
        Serial.println("AT+VSP=1");
        delay (500);    
        Serial.println("AT+VGS=255");
        delay (500);  
    
    Call_state = 0;    
  
}

void loop() // run over and over
{
//    if(digitalRead(BTN_PIN)==HIGH){
//      button_state = HIGH;
//    } else {
//       button_state = LOW;
//    }       

    

    if (Call_state == 0){
      if((analogRead(RING_IN)/4) < 0xA0 ){
            Call_state = 1;
      } 
      
          loop_cnt++;
          delay(100);
              
         if((loop_cnt%4)>2) {
           digitalWrite(STAT_LED,HIGH);       
         } else {
           digitalWrite(STAT_LED,LOW);                         
         }
    }
    
    if (Call_state == 1){
          loop_cnt++;
          delay(100);
              
         if((loop_cnt%10)>5) {
             
           digitalWrite(STAT_LED,HIGH);       
         } else {
           digitalWrite(STAT_LED,LOW);                         
         }
      
        if(button_state == HIGH) {
            Call_state = 2;
            Serial.println("AT+VLS=1");           
        }
    };   
     
     if (Call_state == 2){
         if(button_state == LOW) {
            Call_state = 3;
            Init_Modem();
          }
          
          delay(100);
    };  

    if (Call_state == 3){
        Call_state = 0;
        loop_cnt = 0;
    };  

  

 
}


boolean Init_Modem()
{
  
        Serial.println("ATZ");
       delay (500);    
      Serial.println("ATH");
       delay (500);    
        Serial.println("AT+FCLASS=8");
       delay (500);    
        Serial.println("AT+VSP=1");
        delay (500);    
        Serial.println("AT+VGS=255");
        delay (500);     
  
}



