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

#include "BatteryMonitor.h"

#define LED 13

TinySSD1306 display(SSD1306_128x64);
VoltageSensor* voltage_sensor;
OverviewPerspective* overview;
ValueContainer container;
ConsumptionCounter ma_counter;
long last_ms = 0;

//The setup function is called once at startup of the sketch
void setup() {
    Serial.begin(115200);
    Wire.begin();

    display.beginI2C();
    display.clear();

    overview = new OverviewPerspective(&display);

    voltage_sensor = new VoltageSensor();

    Serial.println("Startup done");
    pinMode(LED, OUTPUT);
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
	overview->renderPerspective(&container);
	long now = millis();
	Serial.println(now - last_ms);
	last_ms = now;
}

void updateContainer() {
	container.cell0_voltage = voltage_sensor->getCellVoltage(MCP342x::channel1);
	container.cell1_voltage = voltage_sensor->getCellVoltage(MCP342x::channel1);
	container.cell2_voltage = voltage_sensor->getCellVoltage(MCP342x::channel1);
	container.cell3_voltage = voltage_sensor->getCellVoltage(MCP342x::channel1);

	container.total_voltage = voltage_sensor->getTotalVoltage();
	container.consuming_ma = voltage_sensor->getConsumptionsMilliamps();
	ma_counter.update(container.total_voltage, container.consuming_ma);
	container.mah_consumed = ma_counter.get_consumed_mah();
	container.mwh_consumed = ma_counter.get_consumed_mwh();
}
