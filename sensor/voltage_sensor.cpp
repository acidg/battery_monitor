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

	ads1015.begin();
	ads1015.setGain(GAIN_TWOTHIRDS);
}

float VoltageSensor::getTotalVoltage() {
	float factor = settings_manager->get_total_voltage_factor();
	uint16_t value = getAverageValue(CELL1);
	return value * VOLTAGE_PER_BIT * factor;
}

float VoltageSensor::getCellVoltage(Cell cell) {
	// TODO: fix this for the new ADC
	return getAverageValue(CELL1) * VOLTAGE_PER_BIT;
}

int16_t VoltageSensor::getConsumptionsMilliamps() {
	return ads1015.readADC_Differential_2_3() * MILLIAMPS_PER_BIT;
}

uint16_t VoltageSensor::getAverageValue(uint8_t channel) {
	uint32_t sum = 0;
	uint8_t sample_count = settings_manager->get_sample_count();

	for (uint8_t i = 0; i < sample_count; i++) {
		sum += ads1015.readADC_SingleEnded(channel);
	}

	return sum / sample_count;
}
