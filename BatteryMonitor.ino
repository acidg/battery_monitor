/*********************************************************************

 *********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#define OLED_RESET 4
#define BATTERY_FULL_RAW_VALUE 1023

Adafruit_SSD1306 display(OLED_RESET);

uint16_t raw_voltage_value = 0;
uint16_t raw_current_value = 0;
uint8_t percentage = 0;

void setup() {
    Serial.begin(9600);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();

    pinMode(A0, INPUT);
    pinMode(A3, INPUT);
}

void loop() {
    raw_voltage_value = analogRead(A0);
    raw_current_value = analogRead(A3);

    percentage = 100 * raw_voltage_value/BATTERY_FULL_RAW_VALUE;

    update_percentage();
    update_bar();
//    update_details();
}

void update_percentage() {
    display.fillRect(0, 8, display.width(), display.height() - 16, BLACK);
    display.fillRect(0, 8, display.width() * percentage/100, display.height() - 16, WHITE);
    display.setTextColor(INVERSE);
    display.setTextWrap(false);
    display.setTextSize(1);
    display.setFont(&FreeSansBold24pt7b);

    if (percentage >= 100) {
        display.setCursor(5, 48);
        display.print("100%");
        display.display();
    } else if (percentage < 10) {
        display.setCursor(30, 48);
        display.print(percentage);
        display.print("%");
        display.display();
    } else {
        display.setCursor(18, 48);
        display.print(percentage);
        display.print("%");
        display.display();
    }
}

void update_details() {
    display.setTextColor(WHITE);
    display.setTextWrap(false);
    display.setTextSize(1);
    display.setFont();
    display.setCursor(0, 57);
    display.print("RAW: ");
    display.print(raw_voltage_value);
    display.display();
}

void update_bar() {
	int8_t value = (raw_current_value - 512) / 8;
	uint8_t middle = display.width() / 2;

	// reset display area
    display.fillRect(0, 0, display.width(), 7, BLACK);
    display.drawLine(display.width() / 2, 0, middle, 7, WHITE);

	if (value != 0) {
		uint8_t cursor_x = middle + value;
		if (value > 0) {
			display.fillRect(middle, 0, value, 3, WHITE);
			display.fillTriangle(cursor_x, 0, cursor_x, 5, cursor_x + 6, 0, WHITE);
		} else {
			display.fillRect(cursor_x, 0, abs(value), 3, WHITE);
			display.fillTriangle(cursor_x, 0, cursor_x, 5, cursor_x - 6, 0, WHITE);
		}
    }
	display.display();
}
