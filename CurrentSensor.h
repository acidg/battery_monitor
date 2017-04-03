/*
 * CurrentSensor.h
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

#ifndef CURRENTSENSOR_H_
#define CURRENTSENSOR_H_

#include "AveragedAnalogReader.h"

#define FACTOR_CURRENT_SENSOR VCC_INPUT / 1024 / 0.066 // ACS712 has 0.066V/A sensitivity

class CurrentSensor: public AveragedAnalogReader {
public:
    CurrentSensor(uint8_t pin, uint8_t samples);
    float getCurrent();
};

#endif /* CURRENTSENSOR_H_ */
