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

#ifndef AVERAGEDANALOGREADER_H_
#define AVERAGEDANALOGREADER_H_

#include "Arduino.h"
#include "config.h"

/**
 * Class for reading from an analog input. The result is averaged over multiple measurements. The amount of averaged
 * measurements can be set with the samples parameter.
 */
class AveragedAnalogReader {
  public:
    AveragedAnalogReader(uint8_t pin, uint8_t samples) : pin(pin), sample_count(samples) {};
  protected:
    uint16_t getAveragedValue();
  private:
    uint8_t pin;
    uint8_t sample_count;
};

#endif /* AVERAGEDANALOGREADER_H_ */
