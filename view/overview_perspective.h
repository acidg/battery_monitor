/*
 * overview_perspective.h 
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

#ifndef VIEW_OVERVIEW_PERSPECTIVE_H_
#define VIEW_OVERVIEW_PERSPECTIVE_H_

#include "perspective_base.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "value_container.h"
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include "../settings_manager.h"


/* Row heights */
#define FIRST_ROW_HEIGHT 8
#define MIDDLE_ROW_HEIGHT 48
#define END_ROW_HEIGHT SSD1306_LCDHEIGHT - FIRST_ROW_HEIGHT - MIDDLE_ROW_HEIGHT
#define DISPLAY_X_MIDDLE SSD1306_LCDWIDTH / 2

class OverviewPerspective : public PerspectiveBase {
public:
	OverviewPerspective(Adafruit_SSD1306* display);
	~OverviewPerspective() {}
	void renderPerspective(ValueContainer* value_container);
private:
	OverviewPerspective(OverviewPerspective&);
	void renderPercentage(uint8_t percentage);
	void renderDetails(float voltage, int16_t current_ma);
	void renderBar(int16_t current_ma);
};

#endif /* VIEW_OVERVIEW_PERSPECTIVE_H_ */
