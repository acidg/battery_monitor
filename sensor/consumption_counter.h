/*
 * consumption_counter.h 
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

#ifndef SENSOR_CONSUMPTION_COUNTER_H_
#define SENSOR_CONSUMPTION_COUNTER_H_

#include <stdint.h>

class ConsumptionCounter {
public:
	ConsumptionCounter();
	~ConsumptionCounter() {};
	/** Updates the counted milli amps. */
	void update(float current_voltage, int16_t current_milliamps);
	/** Returns the amount of consumed milli ampere hours (mAh). */
	uint32_t get_consumed_mah();
	/** Returns the amount of consumed milli watt seconds (mWh). */
	uint32_t get_consumed_mwh();
	/** Resets the counter */
	void reset();
private:
	/** Amount of consumed milli amp seconds. */
	int32_t mas_consumed;
	/** Amount of consumed milli watt seconds. */
	int32_t mws_consumed;
	/** Milliseconds since start the last update happened. */
	uint32_t last_update;
};

#endif /* SENSOR_CONSUMPTION_COUNTER_H_ */
