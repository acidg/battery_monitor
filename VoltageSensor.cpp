/*
 * VoltageSensor.cpp
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

#include "VoltageSensor.h"
#include "config.h"

VoltageSensor::VoltageSensor(uint8_t pin, uint8_t samples) : AveragedAnalogReader(pin, samples) {};

float VoltageSensor::getVoltage() {
    return getAveragedValue() * FACTOR_VOLTAGE_DIVIDER;
}

uint8_t VoltageSensor::getPercents() {
    float voltage = getVoltage();

    if (voltage <= BATTERY_EMPTY_VOLTAGE) {
        return 0;
    }

    return voltage / BATTERY_EMPTY_VOLTAGE * 100;
}
