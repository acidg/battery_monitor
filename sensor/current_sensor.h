/*
 * current_sensor.h 
 *
 * Copyright (C) 2017  Benedikt Schlagberger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SENSOR_CURRENT_SENSOR_H_
#define SENSOR_CURRENT_SENSOR_H_

#include <Arduino.h>
#include <Adafruit_ADS1015.h>

#include "../settings_manager.h"

#define ADS_ADDRESS 0x48
#define ADS_MILLIVOLTS_PER_BIT 3.0F // 12 bit for +/- 4.096V -> 1 bit = 3mV
#define ACS712_VOLTAGE_PER_AMP 0.066F
#define CURRENT_FACTOR (1.0F / ACS712_VOLTAGE_PER_AMP) * ADS_MILLIVOLTS_PER_BIT
#define MILLIAMP_OFFSET 0

class CurrentSensor {
public:
	CurrentSensor();
	virtual ~CurrentSensor() {};
	int16_t getCurrentMilliamps();
private:
	SettingsManager* settings_manager;
	Adafruit_ADS1115* ads;
	int16_t getAverageValue();
};

#endif /* SENSOR_CURRENT_SENSOR_H_ */
