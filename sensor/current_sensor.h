/*
 * current_sensor.h 
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

#ifndef SENSOR_CURRENT_SENSOR_H_
#define SENSOR_CURRENT_SENSOR_H_

#include <stdint.h>

class CurrentSensor {
public:
	CurrentSensor();
	virtual ~CurrentSensor();
	uint16_t getCurrentMilliamps();
};

#endif /* SENSOR_CURRENT_SENSOR_H_ */
