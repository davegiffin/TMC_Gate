#include <SoftwareSerial.h>
#define TX 4
#define RX 5
#define M0 2
#define M1 3
#define beep 8

int IRBeam1 = A3;
int IRBeam2 = A4;

SoftwareSerial lora(5, 4); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(M0,OUTPUT);
  pinMode(M1,OUTPUT);
  pinMode(beep,OUTPUT);
  digitalWrite(M0,LOW);
  digitalWrite(M1,LOW);

  //Scare
  digitalWrite(beep,HIGH);
  delay(1000);
  digitalWrite(beep,LOW);
  
  //Data rate for the SoftwareSerial port
  lora.begin(9600);
  lora.println("Hello");

  Serial.println(F("Initialized"));

  delay(1000);
  
}

bool triggered(int beam) {
  //Beam is triggered if the input drops
  return (analogRead(beam) < 300)?true:false;
}

void loop() {  // run over and over
  if (triggered(IRBeam1)){    
      for (int i = 0; i <= 1000; i++) {
          if (triggered(IRBeam2)){
             lora.println("incoming");
             delay(10000);
             break;        
          }
         delay(10);
    }
  }
  
  if (triggered(IRBeam2)){
       for (int i = 0; i <= 1000; i++) {
            if (triggered(IRBeam1)){ 
               lora.println("outgoing");
               delay(10000);
               break;        
            }
           delay(10);
      }
  }
  delay(10);
}

