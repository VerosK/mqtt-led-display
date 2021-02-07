
# MQTT LED display

This code shows random text on MAX7219 based LED matrix display driven by ESP8266 (or other 
microcontroller).

Content of the display is provided over MQTT connection.  The configuration and connection part is handled by 
[Homie][homie] .

## Wiring

ESP8266 (NodeMCU, D1)
 
* CLK -  D5
* DIN -  D7
* CS  -  D8

## Configuration

Device configuration is handled by [Homie configuration][homie-config]. 

* If the LED is on, the device is waiting for configuration. Connect to device WiFi, and upload your configuration 
  to http://192.168.123.1 

* You can also send JSON to your device over HTTP - see [Homie JSON configuration][homie-json-config].

* You can also save `homie/config.json` JSON to spiffs filesystem of the device. Make copy of 
  `data/homie/config.json.example`  to `data/homie/config.json` and update the values according
  to [Homie JSON configuration][homie-json-config]. Flash the image to your device - PlatformIO
  will probably do it by default.

## License

MIT - (as [Homie][homie] itself)


[homie]: https://github.com/homieiot/homie-esp8266
[homie-config]: https://homieiot.github.io/homie-esp8266/docs/3.0.1/quickstart/getting-started/#connecting-to-the-ap-and-configuring-the-device
[homie-json-config]: https://homieiot.github.io/homie-esp8266/docs/3.0.1/configuration/json-configuration-file/
