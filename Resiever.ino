#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

#define led 3
#define button 8

bool buttonState = 0;
uint32_t receiver[3];
uint32_t input[3];

RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network

const uint16_t this_node = 02;   // Address of our node in Octal format ( 04,031, etc)


void setup() {
   Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
  pinMode(button, INPUT_PULLUP);

  
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
}
void loop() {
  network.update();
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    network.read(header, &receiver, sizeof(receiver)); // Read the incoming data
    Serial.println(receiver[0]);                          // Print whatever is received to the serial for debugging
      if (receiver[0] == 0) {digitalWrite(led, HIGH);}      // check the received if it's 0 then turn on the LED
     else if (receiver[0] == 1) {digitalWrite(led, LOW);} 
  }
}
