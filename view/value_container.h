/*
 * ValueContainer.h 
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

#ifndef SENSOR_VALUE_CONTAINER_H_
#define SENSOR_VALUE_CONTAINER_H_

#include <stdint.h>

struct ValueContainer {
	float total_voltage;
	float cell0_voltage;
	float cell1_voltage;
	float cell2_voltage;
	float cell3_voltage;
	int32_t mah_consumed;
	int32_t wh_consumed;
	int16_t current_ma;
};

#endif /* SENSOR_VALUE_CONTAINER_H_ */
