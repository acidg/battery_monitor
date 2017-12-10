/*
 * AveragedAnalogReader.h
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

#ifndef ADS1015_H_
#define ADS1015_H_

#include "Arduino.h"
#include "config.h"
#include "Adafruit_ADS1015.h"

/**
 * Class for reading values from the ADS1015
 */
class ADS1015 {
  public:
	void begin();
	double getVoltage();
    uint8_t getVoltagePercents();
	double getCurrent();
  private:
    Adafruit_ADS1015 ads1015;
    uint16_t getAverageValue(uint8_t channel);
};

#endif /* ADS1015_H_ */
