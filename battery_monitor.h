/*
 * Arduino based battery monitor for campers.
 *
 * BatteryMonitor.h
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
#ifndef _BatteryMonitor_H_
#define _BatteryMonitor_H_
#include "Arduino.h"
#include <tiny_ssd1306.h>

#include "sensor/voltage_sensor.h"
#include "sensor/current_sensor.h"
#include "sensor/consumption_counter.h"
#include "view/perspective_base.h"
#include "view/overview_perspective.h"
#include "view/value_container.h"

void updateContainer();
void printContainer();
uint8_t calculatePercentage(float total_voltage);

#endif /* _BatteryMonitor_H_ */
