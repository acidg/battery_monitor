/*
 * consumption_counter.cpp 
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

#include "consumption_counter.h"
#include "Arduino.h"

#define SECONDS_PER_HOUR 3600.0
#define MILLISECONDS_PER_HOUR SECONDS_PER_HOUR * 1000

ConsumptionCounter::ConsumptionCounter() {
	reset();
}

void ConsumptionCounter::update(float current_voltage, int16_t current_milliamps) {
	uint32_t now = millis();
	float seconds_since_last = (now - last_update) / 1000.0;
	mas_consumed += current_milliamps * seconds_since_last;
	mws_consumed += current_milliamps * current_voltage * seconds_since_last;
	last_update = now;
}

uint32_t ConsumptionCounter::get_consumed_mah() {
	return mas_consumed / SECONDS_PER_HOUR;
}
uint32_t ConsumptionCounter::get_consumed_mwh() {
	return mws_consumed / 3600.0;
}

void ConsumptionCounter::reset() {
	mas_consumed = 0;
	mws_consumed = 0;
	last_update = millis();
}

