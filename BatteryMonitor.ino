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
#define BATTERY_EMPTY_RAW_VALUE 856
#define VCC_INPUT 5.0
#define FACTOR_VOLTAGE_DIVIDER 0.014662757
#define FACTOR_CURRENT_SENSOR VCC_INPUT / 1024 / 0.066 // ACS712 has 0.066V/A sensitivity

/* Rows, heights and widths */
#define FIRST_ROW_HEIGHT 8
#define MIDDLE_ROW_X_START 8
#define END_ROW_X_START 57
#define MIDDLE_ROW_HEIGHT END_ROW_X_START - MIDDLE_ROW_X_START
#define END_ROW_HEIGHT 8
#define DISPLAY_X_MIDDLE SSD1306_LCDWIDTH / 2

Adafruit_SSD1306 display(OLED_RESET);

uint16_t raw_voltage_value = 0;
uint16_t raw_current_value = 0;
uint8_t percentage = 0;
double voltage = 0;
double current = 0;

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
	Serial.print("A0: ");
	Serial.print(raw_voltage_value);
	Serial.print(", A3: ");
	Serial.print(raw_current_value);

	percentage = 100 * raw_voltage_value / BATTERY_FULL_RAW_VALUE;

	voltage = raw_voltage_value * FACTOR_VOLTAGE_DIVIDER;
	current = ((int16_t) raw_current_value - 512) * FACTOR_CURRENT_SENSOR;

	Serial.print(", V: ");
	Serial.print(voltage);
	Serial.print(", ");
	Serial.print(percentage);
	Serial.print("%, Factor: ");
	Serial.print(FACTOR_CURRENT_SENSOR, 10);
	Serial.print(", A: ");
	Serial.println(current);

	update_percentage();
	update_bar();
	update_details();
}

void update_percentage() {
    display.fillRect(0, MIDDLE_ROW_X_START, display.width(), MIDDLE_ROW_HEIGHT, BLACK);
    display.fillRect(0, MIDDLE_ROW_X_START, display.width() * percentage/100, MIDDLE_ROW_HEIGHT, WHITE);
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
    display.fillRect(0, END_ROW_X_START, display.width(), END_ROW_HEIGHT, BLACK);
    display.setTextColor(WHITE);
    display.setTextWrap(false);
    display.setTextSize(1);
    display.setFont();

    display.setCursor(0, 57);
    display.print(voltage, 1);
    display.print("V ");
    display.print(current, 1);
    display.print("A ");

    display.display();
}

void update_bar() {
	int8_t value = (raw_current_value - 512) / 8;

	// reset display area
    display.fillRect(0, 0, display.width(), FIRST_ROW_HEIGHT - 1, BLACK);
    display.drawLine(display.width() / 2, 0, DISPLAY_X_MIDDLE, FIRST_ROW_HEIGHT - 1, WHITE);

	if (value != 0) {
		uint8_t cursor_x = DISPLAY_X_MIDDLE + value;
		if (value > 0) {
			display.fillRect(DISPLAY_X_MIDDLE, 0, value, 3, WHITE);
			display.fillTriangle(cursor_x, 0, cursor_x, FIRST_ROW_HEIGHT - 3, cursor_x + FIRST_ROW_HEIGHT - 3, 0, WHITE);
		} else {
			display.fillRect(cursor_x, 0, abs(value), 3, WHITE);
			display.fillTriangle(cursor_x, 0, cursor_x, FIRST_ROW_HEIGHT - 3, cursor_x - FIRST_ROW_HEIGHT + 3, 0, WHITE);
		}
    }
	display.display();
}
