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
	renderPercentage(value_container->percentage);
	renderBar(value_container->consuming_ma);
	renderDetails(value_container);
}

void OverviewPerspective::renderPercentage(uint8_t percentage) {
	char string[5];
	dtostrf(percentage, 2, 0, string);
	display->charF12x16(0, 0, string);
	display->charF12x16(28, 0, "%");
}

void OverviewPerspective::renderDetails(ValueContainer* values) {
	char string[9];
	dtostrf(values->total_voltage, 4, 2, string);
	display->charF12x16(48, 0, string);
	display->charF12x16(112, 0, "V");
	dtostrf(values->consuming_ma / 1000.0, 8, 2, string);
	display->charF12x16(0, 2, "A ");
	display->charF12x16(24, 2, string);
	dtostrf(values->mah_consumed / 1000.0, 8, 2, string);
	display->charF12x16(0, 4, "Ah");
	display->charF12x16(24, 4, string);

	dtostrf(values->cell0_voltage, 3, 2, string);
	display->charF6x8(0, 7, string);

	dtostrf(values->cell1_voltage, 3, 2, string);
	display->charF6x8(32, 7, string);

	dtostrf(values->cell2_voltage, 3, 2, string);
	display->charF6x8(64, 7, string);

	dtostrf(values->cell3_voltage, 3, 2, string);
	display->charF6x8(96, 7, string);
}

void OverviewPerspective::renderBar(int16_t current_ma) {
	// do nothing right now
}
