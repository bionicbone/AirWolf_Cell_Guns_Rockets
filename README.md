**RC Airwolf Project**

**NOTE: See TODO - While statements MUST be recoded once both side are connected to the ESP32 to ensure the safety code works correctly and parts cannot crash in the event on an error**

ESP32 code to operate the Nacelle's, Nacelle LEDs, Gun's on the left and right side of the helicopter.

Parts required are:
* Two Normal Servo's for the Nacelle's
* Two 360 Servo's for the Gun's
* Four Hall Effect Sensors, one for each of the Nacelle's in position and one for each out position. As well as one for each gun's in position, and one for the out position.
* Two LEDs

NOTE1: The Nacelle Hall Effect sensor's does not need to be precisely positioned, the normal servo can be set for perfect alignment, the sensor's simply provide correct operational feedback to ensure normal flow without parts crashing into each other and burning servos out.  
NOTE2: The Gun Hall Effect sensor's **MUST** be precisely positioned to feedback to the micro controller when to stop the 360 servo.

![ESP32 Wiring](https://github.com/bionicbone/AirWolf_Cell_Guns_Rockets/blob/master/ESP32%20Wiring%20Diagram.jpg)


**Setting the Rx Activation Zone**  
In the below code, the guns are activated when the Tx/Rx signal is between 1050 and 1450 
```
// Rx Control
const uint16_t  rxControl_GunsActive = 1250;              // PWM Signal Activation Value in us
const uint8_t   rxControl_GunsActiveSpot = 200;           // PWM Signal Activation + - Spot in us 100-255 (100 absolute minimum)
```


**Setting up the Servo Parameters**  
NOTE: Read the comments on the right for important information  
The Nacelle servo position can be precisely set using the Min/Max ServoPosition constants  
TimeOut constants are to stop the servos burning out if they do not reach the desired position in x milliseconds, they can be altered but consider the consequences  
gun_Stopped is the value for the Guns 360 Servo that puts it in a stopped position  
guns_Retract and guns_Extend can be altered, but be aware that certain safety checks are considered in my ESP32_ESC_HIGH_RESOLUTION_DRIVER library to protect the servos so extend parameters may not work  
led_Brightness is a bit obvious, but consider it is best not to drive the ESP32 pins so hard, and they are only 3.3v and 20mA maximum tolerant. 

```
const uint8_t   nacelle_Speed = 15;                       // 1-15 with 1 slowest and 15 fastest, too high and the servo will not keep up with the updates and not complete the full motion, or have irregular stopping itions  !!
const uint16_t  nacelle_TimeOut = 250;                    // after x ms of wait for hall effect to update time out so code can continue
const uint16_t  nacelle_MinServoPosition = 975;           // PWM Signal Lower Value in us
const uint16_t  nacelle_MaxServoPosition = 2025;          // PWM Signal Higher Value in us
const uint16_t  guns_TimeOut = 2500;                      // after x ms of wait for hall effect to update time out so code can continue
const uint16_t  guns_Retract = 1000;                      // 1000 - 1200,  1000 fastest speed in - guns_Speed
const uint16_t  guns_Stopped = 1475;                      // may need to adjust to be central of any movement
const uint16_t  guns_Extend = 2000;                       // 1350 - 1550, 1550 fastest speed out + guns_Speed
const uint8_t   led_BrightnessPWM = 150;                  // 0 - 255 highier number brighter
```
