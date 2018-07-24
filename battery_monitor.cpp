/*
 * Arduino based battery monitor for campers.
 *
 * BatteryMonitor.cpp main file
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

#include "battery_monitor.h"

#define LED 13

TinySSD1306 display(SSD1306_128x64);
VoltageSensor* voltage_sensor;
CurrentSensor* current_sensor;
OverviewPerspective* overview;
ValueContainer container;
ConsumptionCounter ma_counter;
long last_ms = 0;

//The setup function is called once at startup of the sketch
void setup() {
    pinMode(LED, OUTPUT);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);

    Serial.begin(115200);
    Wire.begin();

    display.beginI2C();
    display.clear();

    overview = new OverviewPerspective(&display);

    voltage_sensor = new VoltageSensor();
    current_sensor = new CurrentSensor();

    Serial.println("Startup done");
    digitalWrite(LED, HIGH);

    Serial.print("Voltage factor: ");
    Serial.print(SettingsManager::getInstance()->get_total_voltage_factor());
    Serial.print(" Charge End: ");
    Serial.print(SettingsManager::getInstance()->get_charge_end_voltage());
    Serial.print(" Discharge End: ");
    Serial.println(SettingsManager::getInstance()->get_discharge_end_voltage());
}

// The loop function is called in an endless loop
void loop() {
	updateContainer();
	printContainer();
	overview->renderPerspective(&container);
	long now = millis();
	Serial.print(now - last_ms);
	Serial.println("ms");
	last_ms = now;
}

void updateContainer() {
	container.cell0_voltage = voltage_sensor->getCellVoltage(0);
	container.cell1_voltage = voltage_sensor->getCellVoltage(1);
	container.cell2_voltage = voltage_sensor->getCellVoltage(2);
	container.cell3_voltage = voltage_sensor->getCellVoltage(3);

	container.total_voltage = voltage_sensor->getTotalVoltage();

	container.percentage = calculatePercentage(container.total_voltage);
	container.consuming_ma = current_sensor->getCurrentMilliamps();
	ma_counter.update(container.total_voltage, container.consuming_ma);
	container.mah_consumed = ma_counter.get_consumed_mah();
	container.mwh_consumed = ma_counter.get_consumed_mwh();
}

void printContainer() {
	Serial.print(container.cell0_voltage);
	Serial.print("V\t");
	Serial.print(container.cell1_voltage);
	Serial.print("V\t");
	Serial.print(container.cell2_voltage);
	Serial.print("V\t");
	Serial.print(container.cell3_voltage);
	Serial.print("V\t");
	Serial.print(container.total_voltage);
	Serial.print("V\t");
	Serial.print(container.percentage);
	Serial.print("%\t");
	Serial.print(container.consuming_ma);
	Serial.print("mA\t");
	Serial.print(container.mah_consumed);
	Serial.print("mAh\t");
	Serial.print(container.mwh_consumed);
	Serial.print("mWh\t");
}

uint8_t calculatePercentage(float total_voltage) {
	float cell_voltage = total_voltage / 4;

	if (cell_voltage > 3.32) {
		return 99;
	}

	if (cell_voltage > 3.25) {
		return (50.0 / (3.32 - 3.25)) * (cell_voltage - 3.25) + 50;
	}

	if (cell_voltage > 3.22) {
		return (27.0 / (3.25 - 3.22)) * (cell_voltage - 3.22) + 23;
	}

	if (cell_voltage > 3.14) {
		return (23.0 / (3.22 - 3.14)) * (cell_voltage - 3.14);
	}

	return 0;
}
