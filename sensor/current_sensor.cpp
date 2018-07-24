/*
 * current_sensor.cpp 
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

#include "current_sensor.h"

CurrentSensor::CurrentSensor() {
	settings_manager = SettingsManager::getInstance();
	ads = new Adafruit_ADS1115(ADS_ADDRESS);
	ads->setGain(GAIN_ONE);
}

int16_t CurrentSensor::getCurrentMilliamps() {
	return getAverageValue() * CURRENT_FACTOR - MILLIAMP_OFFSET;
}


int16_t CurrentSensor::getAverageValue() {
	int32_t sum = 0;
	uint8_t sample_count = settings_manager->get_sample_count();

	for (uint8_t i = 0; i < sample_count; i++) {
		sum += ads->readADC_Differential_0_1();
	}

	return sum / sample_count;
}
