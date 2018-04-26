/*
 * perspective_base.h
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

#ifndef VIEW_PERSPECTIVE_BASE_H_
#define VIEW_PERSPECTIVE_BASE_H_

#include <tiny_ssd1306.h>
#include "value_container.h"

class PerspectiveBase {
public:
	PerspectiveBase(TinySSD1306* display):display(display) {};
	virtual ~PerspectiveBase() {}
	/** Renders the perspective. */
	virtual void renderPerspective(ValueContainer* value_container) = 0;
protected:
	TinySSD1306* display;
};

#endif /* VIEW_PERSPECTIVE_BASE_H_ */
