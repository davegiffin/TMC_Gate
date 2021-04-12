//Bi-directional LORA to USB
//Build for TMC Generic PCB
#include <SoftwareSerial.h>
#define TX 4
#define RX 5
#define M0 2
#define M1 3
#define beep 8
#define relay 7

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
  pinMode(relay, OUTPUT);
  digitalWrite(M0,LOW);
  digitalWrite(M1,LOW);

  //Startup scare
  digitalWrite(beep,HIGH);
  digitalWrite(relay,HIGH);
  delay(1000);
  digitalWrite(beep,LOW);
  digitalWrite(relay,LOW);
  
  // set the data rate for the SoftwareSerial port
  lora.begin(9600);
  lora.println("Hello");
  Serial.println(F("Initialized"));
  delay(1000);
  
}

void loop() {  // run over and over
  if (lora.available()) {
    String loraRX = lora.readString();
    Serial.println(loraRX);
    if (loraRX = "incoming"){        
        digitalWrite(beep,HIGH);
        delay(200);
        digitalWrite(beep,LOW);
        delay(100);
        digitalWrite(relay,HIGH);
        delay(200);
        digitalWrite(relay,LOW);
    }
  }
  if (Serial.available()) {
    lora.write(Serial.read());
  }
}


