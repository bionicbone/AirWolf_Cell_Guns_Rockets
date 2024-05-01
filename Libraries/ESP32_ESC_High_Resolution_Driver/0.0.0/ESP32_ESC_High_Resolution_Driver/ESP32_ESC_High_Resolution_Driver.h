// ESP32_ESC_High_Resolution_Driver.h

/* Header for ESP32_ESC_High_Resolution_Driver
 *
 * Copyright (C) 2023  Kevin Guest
 *
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
 * This header file describes the public API for SerialDebug.
 *
 */

 //Servo Settings
const int SERVO_CALIBRATION = 8.266666;
const int SERVO_MIN = 704;
const int SERVO_CENTER = 1448;
const int SERVO_MAX = 2192;

#ifndef _ESP32_ESC_HIGH_RESOLUTION_DRIVER_h
#define _ESP32_ESC_HIGH_RESOLUTION_DRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef ESP32_ESC_HIGH_RESOLUTION_DRIVER_H
#define ESP32_ESC_HIGH_RESOLUTION_DRIVER_H

#ifndef ESP32
#error "this library is only for ESP32"
#endif

class ESP32_ESC_HIGH_RESOLUTION_DRIVER {
public:
	// Attach ESC, for RC ESC use 50 Hz
	void ESC1_attach(uint8_t gpioPIN, uint32_t frequencyHz);
	void ESC2_attach(uint8_t gpioPIN, uint32_t frequencyHz);
	void ESC3_attach(uint8_t gpioPIN, uint32_t frequencyHz);
	void ESC4_attach(uint8_t gpioPIN, uint32_t frequencyHz);

	// Stop ESC
	void ESC_stop();

	// for RC ESC use 5% to 10% (1ms - 2ms @50 Hz)
	void ESC1_setPWM(float speed);
	void ESC2_setPWM(float speed);
	void ESC3_setPWM(float speed);
	void ESC4_setPWM(float speed);


	void ESC1_set_us(uint16_t speed_us);
	void ESC2_set_us(uint16_t speed_us);
	void ESC3_set_us(uint16_t speed_us);
	void ESC4_set_us(uint16_t speed_us);

	uint8_t processSerialInput(uint8_t currentStep, uint8_t position);

	// ESC Calibrate
	void ESC_calibrate();

	// Servo Calibrate
	void Servo_calibrate();

	float convert_us_to_PWM(uint16_t us);

	uint16_t convert_PWM_to_us(float PWM);

	void Servo_calibrate_us(uint16_t speed_us);

};



#endif  // ESP32MotorControl_H
#endif

