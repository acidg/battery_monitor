/*
 * settings_manager.cpp
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

#include "settings_manager.h"

#include <Arduino.h>

SettingsManager *SettingsManager::instance = 0;

SettingsManager::SettingsManager() {
}

SettingsManager* SettingsManager::getInstance() {
	if (instance == 0) {
		instance = new SettingsManager();
	}
	return instance;
}

uint8_t SettingsManager::get_sample_rate() {
	return container.sample_rate;
}

uint8_t SettingsManager::get_sample_count() {
	return container.sample_count;
}

float SettingsManager::get_charge_end_voltage() {
	return container.charge_end_voltage;
}

float SettingsManager::get_discharge_end_voltage() {
	return container.discharge_end_voltage;
}

uint16_t SettingsManager::get_total_capacity() {
	return container.total_capacity_mah;
}

float SettingsManager::get_total_voltage_factor() {
	return container.total_voltage_factor;
}

void SettingsManager::set_sample_rate(uint8_t sample_rate) {
	container.sample_rate = sample_rate;
	persist();
}

void SettingsManager::set_sample_count(uint8_t sample_count) {
	container.sample_count = sample_count;
	persist();
}

void SettingsManager::set_charge_end_voltage(float charge_end_voltage) {
	container.charge_end_voltage = charge_end_voltage;
	persist();
}

void SettingsManager::set_discharge_end_voltage(float discharge_end_voltage) {
	container.discharge_end_voltage = discharge_end_voltage;
	persist();
}

void SettingsManager::set_total_capacity(uint16_t total_capacity) {
	container.total_capacity_mah = total_capacity;
	persist();
}

void SettingsManager::set_total_voltage_factor(double total_voltage_factor) {
	container.total_voltage_factor = total_voltage_factor;
	persist();
}

void SettingsManager::persist() {
	container = EEPROM.put(SETTINGS_EEPROM_ADDRESS, container);
}

void SettingsManager::load() {
	if (EEPROM.read(SETTINGS_EEPROM_ADDRESS) == 0) {
		persist();
	}
	container = EEPROM.get(SETTINGS_EEPROM_ADDRESS, container);
}
