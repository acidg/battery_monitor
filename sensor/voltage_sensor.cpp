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

VoltageSensor::VoltageSensor() {
	settings_manager = SettingsManager::getInstance();
}

float VoltageSensor::getCellVoltage(uint8_t cell) {
	if (cell == 0) {
		return getAverageValue(0);
	}

	return getAverageValue(cell) - getAverageValue(cell - 1);
}

float VoltageSensor::getTotalVoltage() {
	return getAverageValue(3);
}

uint16_t VoltageSensor::getAverageValue(uint8_t cell) {
	uint8_t analog_pin = 0;

	switch (cell) {
	case 0:
		analog_pin = A0;
		break;
	case 1:
		analog_pin = A1;
		break;
	case 2:
		analog_pin = A2;
		break;
	case 3:
		analog_pin = A3;
		break;
	default:
		return 0;
	}

	int32_t sum = 0;
	uint8_t sample_count = settings_manager->get_sample_count();

	for (uint8_t i = 0; i < sample_count; i++) {
		sum += analogRead(analog_pin);
	}

	return sum / sample_count;
}
