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
#include <MCP342x.h>

#include "../settings_manager.h"
#define MCP_VOLTAGE_PER_BIT 0.001 // total peak to peak voltage of sensor / 2^resolution = 4.096 / 2^12
#define RESISTOR1 51
#define RESISTOR2 43
#define MCP_VOLTAGE_DIVIDER_FACTOR (RESISTOR1 + RESISTOR2) / RESISTOR1
#define MCP_VOLTAGE_FACTOR MCP_VOLTAGE_PER_BIT * MCP_VOLTAGE_DIVIDER_FACTOR
#define MCP_RESOLUTION 12
#define MCP_ONE_SHOT_MODE 0
#define MCP_ADDRESS 0x68

class VoltageSensor {
public:
	VoltageSensor();
	virtual ~VoltageSensor() {};
	float getCellVoltage(MCP342x::Channel channel);
private:
	SettingsManager* settings_manager;
	MCP342x* mcp;
	int16_t getAverageValue(MCP342x::Channel channel);
	int16_t readValue(MCP342x::Channel channel);
};

#endif /* SENSOR_VOLTAGE_SENSOR_H_ */
