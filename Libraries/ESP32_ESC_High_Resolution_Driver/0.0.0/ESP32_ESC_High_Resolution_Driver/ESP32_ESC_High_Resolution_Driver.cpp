/**************************************************************************************************************
 * Library   : ESP32_ESC_High_Resolution_Driver - Library for ESC driver used in RC applications for Arduino. *
 * Programmer: Kevin Guest (AKA TheBionicbone)                                                                *
 * Comments  : Library for ESC like the type used in RC applications.                                         *
 * 					                                                                                                  *
 * Versions  :                                                                                                *
 * 1.0.0  	2023-04-12		Initial Release                                                                     *
 **************************************************************************************************************/

//  %%%%  NOTE THIS NEEDS WORK !!! %%%%
//  Quickly Updated so I can run 4 servos


 /*
	* Source for ESP32_ESC_High_Resolution_Driver

	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, version 3.
	*
	* This program is distributed in the hope that it will be useful, but
	* WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	* General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program. If not, see <http://www.gnu.org/licenses/>.
	*
	* This file contains the code for ESP32_ESC_High_Resolution_Driver library.
	*
	*/

#include "ESP32_ESC_High_Resolution_Driver.h"
#include "driver/mcpwm.h"

int16_t servo_LiveCalibration_us = 0;

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC1_setPWM(float speed) {
	if (speed >= 4 && speed <= 11) {
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, speed);
		mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
	}
	else {
		mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A);
	}
}

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC2_setPWM(float speed) {
	if (speed >= 4 && speed <= 11) {
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, speed);
		mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
	}
	else {
		mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B);
	}
}

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC3_setPWM(float speed) {
	if (speed >= 4 && speed <= 11) {
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A, speed);
		mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
	}
	else {
		mcpwm_set_signal_low(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A);
	}
}

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC4_setPWM(float speed) {
	if (speed >= 4 && speed <= 11) {
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B, speed);
		mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
	}
	else {
		mcpwm_set_signal_low(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B);
	}
}




void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC1_set_us(uint16_t speed_us) {
	if (speed_us >= 890 && speed_us <= 2110) {
		ESC1_setPWM(convert_us_to_PWM(speed_us));
	}
}

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC2_set_us(uint16_t speed_us) {
	if (speed_us >= 890 && speed_us <= 2110) {
		ESC2_setPWM(convert_us_to_PWM(speed_us));
	}
}

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC3_set_us(uint16_t speed_us) {
	if (speed_us >= 890 && speed_us <= 2110) {
		ESC3_setPWM(convert_us_to_PWM(speed_us));
	}
}

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC4_set_us(uint16_t speed_us) {
	if (speed_us >= 890 && speed_us <= 2110) {
		ESC4_setPWM(convert_us_to_PWM(speed_us));
	}
}



void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC1_attach(uint8_t gpioPIN, uint32_t frequencyHz) {
	// Attach motor 0 input pins.
	mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, gpioPIN);

	// Initial MCPWM configuration
	mcpwm_config_t cfg;
	cfg.frequency = frequencyHz;
	cfg.cmpr_a = 0;
	cfg.counter_mode = MCPWM_UP_COUNTER;
	cfg.duty_mode = MCPWM_DUTY_MODE_0;

	// Configure PWM0A & PWM0B with above settings
	mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &cfg);
}

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC2_attach(uint8_t gpioPIN, uint32_t frequencyHz) {
	// Attach motor 0 input pins.
	mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, gpioPIN);

	// Initial MCPWM configuration
	mcpwm_config_t cfg;
	cfg.frequency = frequencyHz;
	cfg.cmpr_b = 0;
	cfg.counter_mode = MCPWM_UP_COUNTER;
	cfg.duty_mode = MCPWM_DUTY_MODE_0;

	// Configure PWM0A & PWM0B with above settings
	mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &cfg);
}

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC3_attach(uint8_t gpioPIN, uint32_t frequencyHz) {
	// Attach motor 0 input pins.
	mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0A, gpioPIN);

	// Initial MCPWM configuration
	mcpwm_config_t cfg;
	cfg.frequency = frequencyHz;
	cfg.cmpr_a = 0;
	cfg.counter_mode = MCPWM_UP_COUNTER;
	cfg.duty_mode = MCPWM_DUTY_MODE_0;

	// Configure PWM0A & PWM0B with above settings
	mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_0, &cfg);
}

void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC4_attach(uint8_t gpioPIN, uint32_t frequencyHz) {
	// Attach motor 0 input pins.
	mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0B, gpioPIN);

	// Initial MCPWM configuration
	mcpwm_config_t cfg;
	cfg.frequency = frequencyHz;
	cfg.cmpr_b = 0;
	cfg.counter_mode = MCPWM_UP_COUNTER;
	cfg.duty_mode = MCPWM_DUTY_MODE_0;

	// Configure PWM0A & PWM0B with above settings
	mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_0, &cfg);
}


void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC_stop() {
	ESC1_setPWM(0);
	ESC2_setPWM(0);
	ESC3_setPWM(0);
	ESC4_setPWM(0);
}


float ESP32_ESC_HIGH_RESOLUTION_DRIVER::convert_us_to_PWM(uint16_t us) {
	return (float)us / (1000000 / mcpwm_get_frequency(MCPWM_UNIT_0, MCPWM_TIMER_0)) * 100;
}

uint16_t ESP32_ESC_HIGH_RESOLUTION_DRIVER::convert_PWM_to_us(float PWM) {
	return PWM / 100 * (1000000 / mcpwm_get_frequency(MCPWM_UNIT_0, MCPWM_TIMER_0));
}


// ESC Calibrate
void ESP32_ESC_HIGH_RESOLUTION_DRIVER::ESC_calibrate() {
	String reply = "";
LOOP1:
	Serial.println("Calibrating ESCs can be DANGEROUS !!!");
	Serial.println("The motor can start up at FULL SPEED without warning");
	Serial.println("Type I UNDERSTAND to continue");
	while (!Serial.available());
	reply = Serial.readString();
	Serial.println(reply);
	if (reply.substring(0, 12) != "I UNDERSTAND" || reply.length() != 14) goto LOOP1;

LOOP2:
	Serial.println("REMOVE PROPELLERS !! - Type OK1 to continue");
	while (!Serial.available());
	reply = Serial.readString();
	Serial.println(reply);
	if (reply.substring(0, 3) != "OK1" || reply.length() != 5) goto LOOP2;
	
LOOP3:
	Serial.println("Switch off Power to the ESC - Type OK2 to continue");
	while (!Serial.available());
	reply = Serial.readString();
	Serial.println(reply);
	if (reply.substring(0, 3) != "OK2" || reply.length() != 5) goto LOOP3;

	// Simulate RC Maximum Throttle Signal
	ESC1_setPWM(10); 
	vTaskDelay(1000);

LOOP4:
	Serial.println("Switch on Power to the ESC");
	Serial.println("Wait for BEEPs to stop");
	Serial.println("Type OK3 to continue");
	while (!Serial.available());
	reply = Serial.readString();
	Serial.println(reply);
	if (reply.substring(0, 3) != "OK3" || reply.length() != 5) goto LOOP4;
	
	// Simulate RC Minimum Throttle Signal
	ESC1_setPWM(4.85); 
	vTaskDelay(1000);

	Serial.println("Wait for ESC BEEPs, then switch off Power to the ESC");
	vTaskDelay(2000);
	Serial.println("Calibraton should be completed");
}


// Calibrate Servo
void ESP32_ESC_HIGH_RESOLUTION_DRIVER::Servo_calibrate() {
	uint8_t step = 0;
	uint16_t servoPosition = 0;
	uint16_t minPosition = 0;
	uint16_t maxPosition = 0;
	uint16_t centerPosition = 0;
	uint16_t holdPosition = 0;
	uint16_t offset = 0;
	Serial.println("Calibrating Servo Started...");

	while (step >= 0 || step <= 4) {
		switch (step) {

		case 0:
			servoPosition = 1000; holdPosition = servoPosition + servo_LiveCalibration_us;
			minPosition = holdPosition;
			Serial.printf("minPosition = %d \n", minPosition);
			Servo_calibrate_us(servoPosition);
			Serial.println("Type ---, --, - or +, ++, +++ to move the horn as far to the nearest edge as possible, without going too far. Type y when done.");
			step = processSerialInput(step, servoPosition);
			break;

		case 1:
			servoPosition = 2000; holdPosition = servoPosition + servo_LiveCalibration_us;
			maxPosition = holdPosition;
			Serial.printf("maxPosition = %d \n", maxPosition);
			Servo_calibrate_us(servoPosition);
			Serial.println("Type ---, --, - or +, ++, +++ to move the horn as far to the nearest edge as possible, without going too far. Type y when done.");
			step = processSerialInput(step, servoPosition);
			break;

		case 2:
			servoPosition = (minPosition + maxPosition) / 2;
			Servo_calibrate_us(servoPosition);
			Serial.println("Remove servo horn and place closest to 90 degrees, type y when done.");
			step = processSerialInput(step, servoPosition);
			break;

		case 3:
			servoPosition = (minPosition + maxPosition) / 2; holdPosition = servoPosition + servo_LiveCalibration_us;
			centerPosition = holdPosition;
			Serial.printf("Fine Tune 90 degree Position = %d \n", centerPosition);
			Servo_calibrate_us(servoPosition);
			Serial.println("Type ---, --, - or +, ++, +++ to align to true 90 degrees, type y when done.");
			step = processSerialInput(step, servoPosition);
			break;

		case 4:
			// Calculate the maximum offset for an equal deflection both ways from the center (90 degrees point)
			if (centerPosition - minPosition < maxPosition - centerPosition) {
				offset = centerPosition - minPosition;
			}
			else {
				offset = maxPosition - centerPosition;
			}
			minPosition = centerPosition - offset;
			maxPosition = centerPosition + offset;
			Serial.printf("In ESP32_ESC_High_Resolution_Driver.h overwrite the follow code with these settings:");
			Serial.printf("\n//Servo Settings\n");
			Serial.printf("const int SERVO_CALIBRATION = %f; \n", (float)(centerPosition - minPosition) / 90);
			Serial.printf("const int SERVO_MIN = %d; \n", minPosition);
			Serial.printf("const int SERVO_CENTER = %d; \n", centerPosition);
			Serial.printf("const int SERVO_MAX = %d; \n", maxPosition);

			//// Demonstrate what the new settings will do
			//for (int ii = 0; ii < 10; ii++) {
			//	for (int i = minPosition; i < maxPosition; i++) ESC1_setServoPWM(convert_us_to_PWM(i));
			//	delay(1000);
			//	ESC1_setServoPWM(convert_us_to_PWM(centerPosition));
			//	delay(1000);
			//	for (int i = maxPosition; i > minPosition; i--) ESC1_setServoPWM(convert_us_to_PWM(i));
			//	delay(1000);
			//	ESC1_setServoPWM(convert_us_to_PWM(centerPosition));
			//	delay(1000);
			//}
			break;


		default:
			Serial.println("ERROR occured, starting again !!");
			step = 0;
			break;


		}
	}
}

	uint8_t ESP32_ESC_HIGH_RESOLUTION_DRIVER::processSerialInput(uint8_t currentStep, uint8_t position) {
		while (!Serial.available());
		String reply = Serial.readString();
		Serial.println(reply);
		if (reply.substring(0, 3) == "---") servo_LiveCalibration_us -= 100;
		else if (reply.substring(0, 3) == "+++") servo_LiveCalibration_us += 100;
		else if (reply.substring(0, 2) == "--") servo_LiveCalibration_us -= 10;
		else if (reply.substring(0, 2) == "++") servo_LiveCalibration_us += 10;
		else if (reply.substring(0, 1) == "-") servo_LiveCalibration_us -= 1;
		else if (reply.substring(0, 1) == "+") servo_LiveCalibration_us += 1;
		else if (reply.substring(0, 1) == "y") {
			servo_LiveCalibration_us = 0; 
			currentStep++; }
		return currentStep;
}


	//void ESP32_ESC_HIGH_RESOLUTION_DRIVER::Servo_calibrate_us(uint16_t speed_us) {
	//	if (speed_us >= 200 && speed_us <= 2800) {
	//		ESC1_setServoPWM(convert_us_to_PWM(speed_us + servo_LiveCalibration_us));
	//	}
	//}


