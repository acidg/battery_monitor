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

#include "../settings_manager.h"

#define ACS712_MILLIAMPS_PER_VOLT 1000 / 0.066F
#define ARDUINO_VOLTS_PER_BIT 5.0F / 1024.0F
#define MILLIAMPS_PER_BIT ACS712_MILLIAMPS_PER_VOLT * ARDUINO_VOLTS_PER_BIT
#define CURRENT_OFFSET 50

class CurrentSensor {
public:
	CurrentSensor();
	virtual ~CurrentSensor() {};
	int16_t getCurrentMilliamps();
private:
	SettingsManager* settings_manager;
};

#endif /* SENSOR_CURRENT_SENSOR_H_ */
