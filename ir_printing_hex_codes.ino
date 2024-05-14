#include <IRremote.hpp>
#define IR_RECEIVE_PIN 7

int rearMotorPin = 5;
int directionBack = 4;
int directionForward = 3;
int motorSpeed = 255; 

int frontMotorPin = 9;
int directionRight = 10;
int directionLeft = 11;


void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  pinMode(rearMotorPin, OUTPUT);
  pinMode(directionBack, OUTPUT);
  pinMode(directionForward, OUTPUT);
  pinMode(frontMotorPin, OUTPUT);
  pinMode(directionLeft, OUTPUT);
  pinMode(directionRight, OUTPUT);
}

void loop() {
  analogWrite(rearMotorPin, motorSpeed);
  analogWrite(frontMotorPin, motorSpeed);
  if (IrReceiver.decode()) {
      // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
      // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
      Serial.println(IrReceiver.decodedIRData.command);
      if (IrReceiver.decodedIRData.command == 24){
        Serial.println("yukari");
        digitalWrite(directionBack, LOW);
        digitalWrite(directionForward, HIGH);
        delay(500);
        digitalWrite(directionForward, LOW);
      }
      else if (IrReceiver.decodedIRData.command == 82){
        digitalWrite(directionBack, HIGH);
        digitalWrite(directionForward, LOW);
        delay(500);
        digitalWrite(directionBack, LOW);
      }
      else if (IrReceiver.decodedIRData.command == 90){
        Serial.println("sag");
        digitalWrite(directionLeft, LOW);
        digitalWrite(directionRight, HIGH);
      }
      else if (IrReceiver.decodedIRData.command == 8){
        digitalWrite(directionLeft, HIGH);
        digitalWrite(directionRight, LOW);
      }
      else if (IrReceiver.decodedIRData.command == 28){
        digitalWrite(directionLeft, LOW);
        digitalWrite(directionRight, LOW);
      }
      IrReceiver.resume(); // Enable receiving of the next value
  }
}
