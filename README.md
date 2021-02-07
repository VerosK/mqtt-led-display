
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

* You can also send JSON to your device - see [Homie JSON configuration][homie-json-config].


## License

MIT - (as [Homie][homie] itself)


[homie]: https://github.com/homieiot/homie-esp8266
[homie-config]: https://homieiot.github.io/homie-esp8266/docs/3.0.1/quickstart/getting-started/#connecting-to-the-ap-and-configuring-the-device
[homie-json-config]: https://homieiot.github.io/homie-esp8266/docs/3.0.1/configuration/json-configuration-file/
