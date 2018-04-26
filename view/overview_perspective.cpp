/*
 * overview_perspective.cpp 
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

#include "overview_perspective.h"

OverviewPerspective::OverviewPerspective(TinySSD1306* display) :
		PerspectiveBase(display) {
}

void OverviewPerspective::renderPerspective(ValueContainer* value_container) {
	float battery_empty_voltage =
			SettingsManager::getInstance()->get_discharge_end_voltage();
	float battery_full_voltage =
			SettingsManager::getInstance()->get_charge_end_voltage();
	float difference = value_container->total_voltage - battery_empty_voltage;

	if (difference < 0) {
		difference = 0;
	}

	uint8_t percentage = difference
			/ (battery_full_voltage - battery_empty_voltage) * 100;

	if (percentage > 100) {
		percentage = 100;
	}

	renderPercentage(percentage);
	renderBar(value_container->consuming_ma);
	renderDetails(value_container);
}

void OverviewPerspective::renderPercentage(uint8_t percentage) {
	char string[9];
	dtostrf(percentage, 8, 0, string);
	display->charF12x16(0, 0, "% ");
	display->charF12x16(24, 0, string);
}

void OverviewPerspective::renderDetails(ValueContainer* values) {
	char string[9];
	dtostrf(values->total_voltage, 8, 3, string);
	display->charF12x16(0, 2, "V ");
	display->charF12x16(24, 2, string);
	dtostrf(values->consuming_ma / 1000.0, 8, 2, string);
	display->charF12x16(0, 4, "A ");
	display->charF12x16(24, 4, string);
	dtostrf(values->mah_consumed / 1000.0, 8, 2, string);
	display->charF12x16(0, 6, "Ah");
	display->charF12x16(24, 6, string);
}

void OverviewPerspective::renderBar(int16_t current_ma) {
	// do nothing right now
}
