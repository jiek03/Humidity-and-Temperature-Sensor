# Humidity and Temperature Sensor

<h4>Authors of this code:</h4>

- Hugo Alpízar Alvarez
- Javier Alejandro Pérez Garza
- Gustavo Lozano Villarreal
- Sergio Ismael herrera Martínez

## Code Explanation
We use a NodeMcu (ESP8266) microcontroller, a LCD screen 16X4 and a DHT22 sensor to turn on different LED lights depending on the temperature:

- Below 30°C, the yellow LED turns on.
- Above 40°C, the red LED turns on.
- Between those ranges the green LED turns on.

Also, by designing the correct circuit, the LCD screen will be showing the humidity and temperature every 5 seconds.
