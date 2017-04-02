# Battery monitor for campers

This project monitors the voltage, current and remaining capacity of the battery of a camper.
Voltage is measured using a voltage divider, current with a 30A hall sensor.

## Hardware
* Sparkfun [Arduino Pro Micro](https://www.sparkfun.com/products/12640): (~3$ clones on ebay), or any other Arduino.
* OLED I²C 0.96" SSD1306 based display (e.g. Crius CO-16)
* Voltage divider (e.g. 10k and 5.6k Ohms) for measuring the voltage
* Hall sensor: ACS712 30A (breakout board from ebay ~5$) for measuring the current
