/*
 Name:		AirWolf_Cell_Guns_Rockets.ino
 Created:	5/1/2024 7:27:20 AM
 Author:	Bionicbone (YouTube / RC Groups)
*/

// the setup function runs once when you press reset or power the board
#include <ESP32_ESC_High_Resolution_Driver.h>

ESP32_ESC_HIGH_RESOLUTION_DRIVER ServoDriver = ESP32_ESC_HIGH_RESOLUTION_DRIVER();

int SERVO_Frequency = 50;

#define RETRACT LOW
#define EXTEND HIGH

// Key Setup
bool gunsPosition = RETRACT;

// Rx Control
uint16_t        rxControl_Value = 0;                      // Last read PWM value from the Rx in us
const uint16_t  rxControl_GunsActive = 1250;              // PWM Signal Activation Value in us
const uint8_t   rxControl_GunsActiveSpot = 200;           // PWM Signal Activation + - Spot in us 100-255 (100 absolute minimum)
// Dual Side Variables
const uint8_t   nacelle_Speed = 15;                       // 1-15 with 1 slowest and 15 fastest, too high and the servo will not keep up with the updates and not complete the full motion, or have irregular stopping itions  !!
const uint16_t  nacelle_TimeOut = 250;                    // after x ms of wait for hall effect to update time out so code can continue
const uint16_t  nacelle_MinServoPosition = 975;           // PWM Signal Lower Value in us
const uint16_t  nacelle_MaxServoPosition = 2025;          // PWM Signal Higher Value in us
const uint16_t  guns_TimeOut = 2500;                      // after x ms of wait for hall effect to update time out so code can continue
const uint16_t  guns_Retract = 1000;                      // 1000 - 1200,  1000 fastest speed in - guns_Speed
const uint16_t  guns_Stopped = 1475;                      // may need to adjust to be central of any movement
const uint16_t  guns_Extend = 2000;                       // 1350 - 1550, 1550 fastest speed out + guns_Speed
const uint8_t   led_BrightnessPWM = 150;                  // 0 - 255 highier number brighter
// Rx PWM Pin
const uint8_t   rxControl_Pin = 34;                       // PWM Signal from an Rx Channel (Not SBUS)                                                          
// Left Side ESP32 Pins                                                         
const uint8_t   leftNacelle_ServoPin = 13;
const uint8_t   leftNacelle_HallEffectOutPin = 12;
const uint8_t   leftNacelle_HallEffectInPin = 14;
const uint8_t   leftGuns_ServoPin = 27;
const uint8_t   leftGuns_HallEffectOutPin = 25;
const uint8_t   leftGuns_HallEffectInPin = 33;
const uint8_t   leftLed_Pin = 26;
// Right Side ESP32 Pins
const uint8_t   rightNacelle_ServoPin = 15;
const uint8_t   rightNacelle_HallEffectOutPin = 02;
const uint8_t   rightNacelle_HallEffectInPin = 04;
const uint8_t   rightGuns_ServoPin = 16;
const uint8_t   rightGuns_HallEffectOutPin = 05;
const uint8_t   rightGuns_HallEffectInPin = 18;
const uint8_t   rightLed_Pin = 17;


void setup() {
  Serial.begin(2000000);
  pinMode(rxControl_Pin, INPUT);
  
  // Set up Left Side
  pinMode(leftNacelle_HallEffectOutPin, INPUT_PULLUP);
  pinMode(leftNacelle_HallEffectInPin, INPUT_PULLUP);
  pinMode(leftGuns_HallEffectOutPin, INPUT_PULLUP);
  pinMode(leftGuns_HallEffectInPin, INPUT_PULLUP);
  pinMode(leftLed_Pin, OUTPUT);

  // Set up Right Side
  pinMode(rightNacelle_HallEffectOutPin, INPUT_PULLUP);
  pinMode(rightNacelle_HallEffectInPin, INPUT_PULLUP);
  pinMode(rightGuns_HallEffectOutPin, INPUT_PULLUP);
  pinMode(rightGuns_HallEffectInPin, INPUT_PULLUP);
  pinMode(rightLed_Pin, OUTPUT);

  // Set up MCPWM for Servos
  ServoDriver.ESC1_attach(leftNacelle_ServoPin, SERVO_Frequency);   // Left Nacelle
  ServoDriver.ESC2_attach(leftGuns_ServoPin, SERVO_Frequency);      // Left Guns
  ServoDriver.ESC3_attach(rightNacelle_ServoPin, SERVO_Frequency);  // Right Nacelle
  ServoDriver.ESC4_attach(rightGuns_ServoPin, SERVO_Frequency);     // Right Guns

  // Ensure LEDs are off
  analogWrite(leftLed_Pin, 0);
  analogWrite(rightLed_Pin, 0);
}

// the loop function runs over and over again until power down or reset
void loop() {
  // Measure length of High PWM Pulse from Rx
  rxControl_Value = pulseIn(rxControl_Pin, HIGH);         
  
  // If there is no PWM from the Rx the Tx may not be switched on so do nothing !!
  if (rxControl_Value > 900) {
    // If Tx is transmitting rxControl_GunsActive + - rxControl_GunsActiveSpot then activate the guns
    if (rxControl_Value >= rxControl_GunsActive - rxControl_GunsActiveSpot && rxControl_Value <= rxControl_GunsActive + rxControl_GunsActiveSpot) {
      // validate the guns are currently retracted
      if (gunsPosition == RETRACT) {
        NacelleMovement(EXTEND);
        // Set up a safety timer for nacelle_TimeOut ms, just in case
        unsigned long timeOut = millis() + nacelle_TimeOut;
        while (digitalRead(leftNacelle_HallEffectOutPin) != LOW && digitalRead(rightNacelle_HallEffectOutPin) != LOW && millis() <= timeOut);
        if (millis() >= timeOut) {
          Serial.println("TIMEOUT");
        }
        // Only extend the guns if the nacelle opened successfully
        else {                    
          LedControl(true);
          GunsMovement(EXTEND);
        }
      }
    }
    else {
      //ServoDriver.ESC1_set_us(1000);
      if (gunsPosition == EXTEND) {
        GunsMovement(RETRACT);
        // Set up a safety timer for guns_TimeOut ms, just in case
        unsigned long timeOut = millis() + guns_TimeOut;
        while (digitalRead(leftGuns_HallEffectInPin) != LOW && digitalRead(rightGuns_HallEffectInPin) != LOW && millis() <= timeOut);
        if (millis() >= timeOut) {
          Serial.println("TIMEOUT");
        }
        // Only close the nacelle if the guns retracted successfully
        else {                  
          NacelleMovement(RETRACT);
          LedControl(false);
        }
      }
    }
  }
}

void NacelleMovement(bool direction) {
  if (direction == EXTEND) {
    Serial.println("Nacelle's Extend");
    ServoDriver.ESC1_set_us(nacelle_MaxServoPosition);
    ServoDriver.ESC3_set_us(nacelle_MaxServoPosition);
    Serial.printf(" Left Nacelle us = %d, Out Mag = %d\n", nacelle_MaxServoPosition, digitalRead(leftNacelle_HallEffectOutPin));
    Serial.printf("Right Nacelle us = %d, Out Mag = %d\n", nacelle_MaxServoPosition, digitalRead(rightNacelle_HallEffectOutPin));
  }
  else {
    Serial.println("Nacelle's Retract");
    ServoDriver.ESC1_set_us(nacelle_MinServoPosition);
    ServoDriver.ESC3_set_us(nacelle_MinServoPosition);
    Serial.printf(" Left Nacelle us = %d, In Mag = %d\n", nacelle_MinServoPosition, digitalRead(leftNacelle_HallEffectInPin));
    Serial.printf("Right Nacelle us = %d, In Mag = %d\n", nacelle_MinServoPosition, digitalRead(rightNacelle_HallEffectInPin));
  }
}

void LedControl(bool active) {
  if (active == true) {
    Serial.println("LED's On");
    analogWrite(leftLed_Pin, led_BrightnessPWM);
    analogWrite(rightLed_Pin, led_BrightnessPWM);
  }
  else {
    Serial.println("LED's Off");
    analogWrite(leftLed_Pin, 0);
    analogWrite(rightLed_Pin, 0);
  }
}

void GunsMovement(bool direction) {
  unsigned long timeOut = millis() + guns_TimeOut;
  if (direction == EXTEND) {
    Serial.println("Gun's Extend");
    uint16_t usGuns = guns_Stopped;
    while (digitalRead(leftGuns_HallEffectOutPin) != LOW && digitalRead(rightGuns_HallEffectOutPin) != LOW && millis() <= timeOut) {
      ServoDriver.ESC2_set_us(guns_Extend);
      ServoDriver.ESC4_set_us(guns_Extend);
    }
  }
  else {
    Serial.println("Gun's Retract");
    uint16_t usGuns = guns_Stopped;
    while (digitalRead(leftGuns_HallEffectInPin) != LOW && digitalRead(rightGuns_HallEffectInPin) != LOW && millis() <= timeOut) {
      ServoDriver.ESC2_set_us(guns_Retract);
      ServoDriver.ESC4_set_us(guns_Retract);
    }
  }
  if (millis() >= timeOut) { Serial.println("TIMEOUT"); }
  else { gunsPosition = direction; }
 
  // Always set the guns stopped signal or the servo will get very hot :)
  ServoDriver.ESC2_set_us(guns_Stopped);
  ServoDriver.ESC4_set_us(guns_Stopped);
}