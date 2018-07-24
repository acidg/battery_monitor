/*
 * voltage_sensor.h 
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

#ifndef SENSOR_VOLTAGE_SENSOR_H_
#define SENSOR_VOLTAGE_SENSOR_H_

#include <Arduino.h>

#include "../settings_manager.h"

#define VOLTAGE_PER_BIT 0.004882813F // 10 bit for 5.0 -> 1 bit = 4.882813
#define VOLTAGE_DIVIDER_FACTOR 3.0F
#define VOLTAGE_FACTOR VOLTAGE_PER_BIT * VOLTAGE_DIVIDER_FACTOR

class VoltageSensor {
public:
	VoltageSensor();
	virtual ~VoltageSensor() {};
	float getCellVoltage(uint8_t cell);
	float VoltageSensor::getTotalVoltage();
private:
	SettingsManager* settings_manager;
	float getAverageValue(uint8_t cell);
};

#endif /* SENSOR_VOLTAGE_SENSOR_H_ */
