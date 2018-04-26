/*
 * voltage_sensor.cpp 
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

#include "voltage_sensor.h"
#include "Wire.h"

VoltageSensor::VoltageSensor() {
	settings_manager = SettingsManager::getInstance();

	mcp = new MCP342x(MCP_ADDRESS);

	MCP342x::generalCallReset();
	delay(1); // MC342x needs 300us to settle, wait 1ms

	// Check device present
	Wire.requestFrom(MCP_ADDRESS, 1);
	if (!Wire.available()) {
		Serial.print("No device found at address ");
		Serial.println(MCP_ADDRESS, HEX);
		while (1)
			;
	}
}

float VoltageSensor::getTotalVoltage() {
	float factor = settings_manager->get_total_voltage_factor();
	int16_t value = getAverageValue(MCP342x::channel1);
	Serial.print("Voltage: ");
	Serial.println(value);
	return value * MCP_VOLTAGE_PER_BIT * factor;
}

float VoltageSensor::getCellVoltage(MCP342x::Channel channel) {
	// TODO: fix this for the new ADC
	return getAverageValue(channel) * MCP_VOLTAGE_PER_BIT;
}

int16_t VoltageSensor::getConsumptionsMilliamps() {
	long value = 0;
	for (uint8_t i = 0; i < 10; i++) {
		value += analogRead(A6);
	}
	return (512 - value / 10) * MILLIAMPS_PER_BIT;
}

int16_t VoltageSensor::getAverageValue(MCP342x::Channel channel) {
	int32_t sum = 0;
	uint8_t sample_count = settings_manager->get_sample_count();

	for (uint8_t i = 0; i < sample_count; i++) {
		sum += readValue(channel);
	}

	return sum / sample_count;
}

int16_t VoltageSensor::readValue(MCP342x::Channel channel) {
	MCP342x::Config status;
	long result = 0;

	uint8_t err = mcp->convertAndRead(channel, MCP342x::oneShot,
			MCP342x::resolution12, MCP342x::gain1, 100000000, result, status);

	if (err) {
		Serial.print("Convert error: ");
		Serial.println(err);
	}

	return result;
}
