#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

#define led 3
#define button 8

int value = 1;
int pirState = LOW;


bool buttonState = 0;
uint32_t receiver[3];
uint32_t input[3];


RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);   // Include the radio in the network


const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;      
const uint16_t node02 = 02; 


void setup() {

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
  pinMode(button, INPUT_PULLUP);


  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
}

void loop() {
  network.update();                                               // set the delay to 5 milliseconds for stability                                    // Stop listening and start receiving
  input[0] = digitalRead(button);                           // Assigning led status to input[0] 
  Serial.println(input[0]);                                 // Print input[0] to the serial for debugging
  RF24NetworkHeader header(node01);     // (Address where the data is going)
  RF24NetworkHeader header2(node02);
  
  bool ok = network.write(header, &input, sizeof(input)); // Send the data
  bool ok2 = network.write(header2, &input, sizeof(input));

//on board led
   value = digitalRead(button);

  if (value == LOW) {
    digitalWrite(led,HIGH);

    if (pirState == HIGH) {
      Serial.println("Motion Detected!");
      pirState = HIGH;
    }
  }else{
    digitalWrite(led, LOW);

    if(pirState == LOW){
      Serial.println("Motion Ended!");
      pirState = LOW;
      }
    }
}
