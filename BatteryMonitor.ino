/*
 * Arduino based battery monitor for campers.
 *
 * BatteryMonitor.ino main file
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

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#include "config.h"
#include "ADS1015.h"

/* Row heights */
#define FIRST_ROW_HEIGHT 8
#define MIDDLE_ROW_HEIGHT 48
#define END_ROW_HEIGHT SSD1306_LCDHEIGHT - FIRST_ROW_HEIGHT - MIDDLE_ROW_HEIGHT
#define DISPLAY_X_MIDDLE SSD1306_LCDWIDTH / 2

Adafruit_SSD1306 display(OLED_RESET);
ADS1015 ads;

void setup() {
    Serial.begin(9600);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
}

void loop() {
    updatePercentage();
    updateBar();
    updateDetails();
}

void updatePercentage() {
    uint8_t percents = ads.getVoltagePercents();

    display.fillRect(0, FIRST_ROW_HEIGHT, display.width(), MIDDLE_ROW_HEIGHT, BLACK);
    display.fillRect(0, FIRST_ROW_HEIGHT, display.width() * percents / 100, MIDDLE_ROW_HEIGHT, WHITE);
    display.setTextColor(INVERSE);
    display.setTextWrap(false);
    display.setTextSize(1);
    display.setFont(&FreeSansBold24pt7b);

    if (percents >= 100) {
        display.setCursor(5, 48);
        display.print("100%");
        display.display();
    } else if (percents < 10) {
        display.setCursor(30, 48);
        display.print(percents);
        display.print("%");
        display.display();
    } else {
        display.setCursor(18, 48);
        display.print(percents);
        display.print("%");
        display.display();
    }
}

void updateDetails() {
    display.fillRect(0, FIRST_ROW_HEIGHT + MIDDLE_ROW_HEIGHT, display.width(), END_ROW_HEIGHT, BLACK);
    display.setTextColor(WHITE);
    display.setTextWrap(false);
    display.setTextSize(1);
    display.setFont();

    display.setCursor(0, 57);
    display.print(ads.getVoltage(), 2);
    display.print("V ");
    display.print(ads.getCurrent(), 2);
    display.print("A ");

    display.display();
}

void updateBar() {
    int8_t value = (ads.getCurrent() - 512) / 8;

    // reset display area
    display.fillRect(0, 0, display.width(), FIRST_ROW_HEIGHT - 1, BLACK);
    display.drawLine(display.width() / 2, 0, DISPLAY_X_MIDDLE, FIRST_ROW_HEIGHT - 1, WHITE);

    if (value != 0) {
        uint8_t cursor_x = DISPLAY_X_MIDDLE + value;
        if (value > 0) {
            display.fillRect(DISPLAY_X_MIDDLE, 0, value, 3, WHITE);
            display.fillTriangle(cursor_x, 0, cursor_x, FIRST_ROW_HEIGHT - 3, cursor_x + FIRST_ROW_HEIGHT - 3, 0,
            WHITE);
        } else {
            display.fillRect(cursor_x, 0, abs(value), 3, WHITE);
            display.fillTriangle(cursor_x, 0, cursor_x, FIRST_ROW_HEIGHT - 3, cursor_x - FIRST_ROW_HEIGHT + 3, 0,
            WHITE);
        }
    }
    display.display();
}
