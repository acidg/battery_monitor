/*
 * config.h
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

#ifndef CONFIG_H_
#define CONFIG_H_

#define OLED_RESET 4
#define VOLTAGE_SENSOR_PIN A3
#define CURRENT_SENSOR_PIN A0
#define VCC_INPUT 5.0

/* Battery specifics */
#define BATTERY_FULL_VOLTAGE 14.6
#define BATTERY_EMPTY_VOLTAGE 12.0
#define SENSOR_AVG_COUNT 10

#endif /* CONFIG_H_ */
