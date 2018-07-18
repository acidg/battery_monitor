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

#define ADS_VOLTAGE_ADDRESS 0x49
#define ADS_VOLTAGE_PER_BIT 0.003F // 12 bit for +/- 6.144V -> 1 bit = 3mV
#define ADS_VOLTAGE_DIVIDER_FACTOR 3.0F
#define ADS_VOLTAGE_FACTOR ADS_MV_PER_BIT * ADS_VOLTAGE_DIVIDER_FACTOR

class VoltageSensor {
public:
	VoltageSensor();
	virtual ~VoltageSensor() {};
	float getCellVoltage(uint8_t cell);
private:
	SettingsManager* settings_manager;
	Adafruit_ADS1015* ads;
	uint16_t getAverageValue(uint8_t cell);
};

#endif /* SENSOR_VOLTAGE_SENSOR_H_ */
