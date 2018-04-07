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

OverviewPerspective::OverviewPerspective(Adafruit_SSD1306* display) : PerspectiveBase(display) {}

void OverviewPerspective::renderPerspective(ValueContainer* value_container) {
	uint8_t percentage = SettingsManager::getInstance()->get_charge_end_voltage() / value_container->total_voltage;

	if (percentage > 100) {
		percentage = 100;
	}

	renderPercentage(percentage);
	renderBar(value_container->current_ma);
	renderDetails(value_container->total_voltage, value_container->current_ma);
}

void OverviewPerspective::renderPercentage(uint8_t percentage) {
    display->fillRect(0, FIRST_ROW_HEIGHT, display->width(), MIDDLE_ROW_HEIGHT, BLACK);
    display->fillRect(0, FIRST_ROW_HEIGHT, display->width() * percentage / 100, MIDDLE_ROW_HEIGHT, WHITE);
    display->setTextColor(INVERSE);
    display->setTextWrap(false);
    display->setTextSize(1);
    display->setFont(&FreeSansBold24pt7b);

    if (percentage >= 100) {
        display->setCursor(5, 48);
        display->print("100%");
        display->display();
    } else if (percentage < 10) {
        display->setCursor(30, 48);
        display->print(percentage);
        display->print("%");
        display->display();
    } else {
        display->setCursor(18, 48);
        display->print(percentage);
        display->print("%");
        display->display();
    }
}

void OverviewPerspective::renderDetails(float voltage, int16_t current_ma) {
    display->fillRect(0, FIRST_ROW_HEIGHT + MIDDLE_ROW_HEIGHT, display->width(), END_ROW_HEIGHT, BLACK);
    display->setTextColor(WHITE);
    display->setTextWrap(false);
    display->setTextSize(1);
    display->setFont();

    display->setCursor(0, 57);
    display->print(voltage, 2);
    display->print("V ");
    display->print(current_ma/1000.0, 2);
    display->print("A ");

    display->display();
}

void OverviewPerspective::renderBar(int16_t current_ma) {
    int8_t value = current_ma / 30000 * SSD1306_LCDWIDTH;

    // reset display area
    display->fillRect(0, 0, display->width(), FIRST_ROW_HEIGHT - 1, BLACK);
    display->drawLine(display->width() / 2, 0, DISPLAY_X_MIDDLE, FIRST_ROW_HEIGHT - 1, WHITE);

    if (value != 0) {
        uint8_t cursor_x = DISPLAY_X_MIDDLE + value;
        if (value > 0) {
            display->fillRect(DISPLAY_X_MIDDLE, 0, value, 3, WHITE);
            display->fillTriangle(cursor_x, 0, cursor_x, FIRST_ROW_HEIGHT - 3, cursor_x + FIRST_ROW_HEIGHT - 3, 0,
            WHITE);
        } else {
            display->fillRect(cursor_x, 0, abs(value), 3, WHITE);
            display->fillTriangle(cursor_x, 0, cursor_x, FIRST_ROW_HEIGHT - 3, cursor_x - FIRST_ROW_HEIGHT + 3, 0,
            WHITE);
        }
    }
    display->display();
}
