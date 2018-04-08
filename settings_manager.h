/*
 * settings_manager.h
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

#ifndef SETTINGS_MANAGER_H_
#define SETTINGS_MANAGER_H_

#include <Arduino.h>
#include <EEPROM.h>
#include <stdint.h>

#define SETTINGS_EEPROM_ADDRESS 0
#define CELL_COUNT 4

/** Singleton class managing all settings. */
class SettingsManager {
public:
	static SettingsManager* getInstance();
	/** Returns the sample rate in samples per second */
	uint8_t get_sample_rate();
	/** Returns the sampling count for averaging analog readings. */
	uint8_t get_sample_count();
	/** Returns the charge end voltage in volts. */
	float get_charge_end_voltage();
	/** Returns the discharge end voltage in volts. */
	float get_discharge_end_voltage();
	/** Returns the total capacity of the battery in mAh. */
	uint16_t get_total_capacity();
	/** Returns the factor for calculating the total voltage. */
	float get_total_voltage_factor();

	/** Sets the sample rate in samples per second */
	void set_sample_rate(uint8_t sample_rate);
	/** Sets the sampling count for averaging analog readings. */
	void set_sample_count(uint8_t sample_count);
	/** Sets the charge end voltage in volts */
	void set_charge_end_voltage(float charge_end_voltage);
	/** Sets the discharge end voltage in volts */
	void set_discharge_end_voltage(float discharge_end_voltage);
	/** Sets the total capacity of the battery in mAh */
	void set_total_capacity(uint16_t total_capacity);
	/** Sets the factor for calculating the total voltage. */
	void set_total_voltage_factor(double total_voltage_factor);
private:
	SettingsManager();
	SettingsManager(const SettingsManager &);
	~SettingsManager();
	static SettingsManager* instance;
	/** Persists all settings to the EEPROM */
	void persist();
	/** Loads all settings from the EEPROM */
	void load();
	/** Struct containing all settings which are stored in the EEPROM. */
	struct SettingsContainer {
		uint8_t sample_rate = 4;
		uint8_t sample_count = 10;
		float charge_end_voltage = 13.3;
		float discharge_end_voltage = 12.0;
		uint32_t total_capacity_mah = 120000;
		float total_voltage_factor = 3.3;
	} container;
};

#endif /* SETTINGS_MANAGER_H_ */
