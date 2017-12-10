/*
 * AveragedAnalogReader.cpp
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

#include "ADS1015.h"

#define VOLTAGE_PER_BIT 0.003
#define PORT_CURRENT 0
#define PORT_VOLTAGE 1

#define FACTOR_CURRENT_SENSOR 0.066 // ACS712 has 0.066V/A sensitivity
#define FACTOR_VOLTAGE_DIVIDER 0.003662109 // = Maximum voltage (15V) / 4096

void ADS1015::begin() {
	ads1015.startComparator_SingleEnded(PORT_CURRENT, 1000);
	ads1015.startComparator_SingleEnded(PORT_VOLTAGE, 1000);
}

double ADS1015::getVoltage() {
	return getAverageValue(PORT_VOLTAGE) * VOLTAGE_PER_BIT
			* (VOLTAGE_DIVIDER_R1 + VOLTAGE_DIVIDER_R2) / VOLTAGE_DIVIDER_R2;
}

uint8_t ADS1015::getVoltagePercents() {
	float percentage = (getVoltage() - BATTERY_EMPTY_VOLTAGE)
			/ (BATTERY_FULL_VOLTAGE - BATTERY_EMPTY_VOLTAGE) * 100;

	if (percentage > 100) {
		return 100;
	} else if (percentage < 0) {
		return 0;
	} else {
		return (uint8_t) percentage;
	}
}

double ADS1015::getCurrent() {
	return (getAverageValue(PORT_CURRENT) * VOLTAGE_PER_BIT - (VCC_INPUT / 2)) / FACTOR_CURRENT_SENSOR;
}

uint16_t ADS1015::getAverageValue(uint8_t channel) {
	uint32_t sum = 0;

	for (uint8_t i = 0; i < SENSOR_AVG_COUNT; i++) {
		sum += ads1015.readADC_SingleEnded(channel);
	}

	return sum / SENSOR_AVG_COUNT;
}
