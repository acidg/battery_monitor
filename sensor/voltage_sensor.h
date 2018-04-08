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
#include <Adafruit_ADS1015.h>

#include "../settings_manager.h"
#define VOLTAGE_PER_BIT 0.003
#define MILLIAMPS_PER_BIT VOLTAGE_PER_BIT * 1000 / 0.066// Voltage/bit * Milliamps/Voltage

enum Cell : uint8_t {
	CELL0 = 0,
	CELL1 = 1,
	CELL2 = 2,
	CELL3 = 3
};

class VoltageSensor {
public:
	VoltageSensor();
	float getTotalVoltage();
	float getCellVoltage(Cell cell);
	int16_t getConsumptionsMilliamps();
	virtual ~VoltageSensor() {};
private:
	Adafruit_ADS1015 ads1015;
	SettingsManager* settings_manager;
	uint16_t getAverageValue(uint8_t channel);
};

#endif /* SENSOR_VOLTAGE_SENSOR_H_ */
