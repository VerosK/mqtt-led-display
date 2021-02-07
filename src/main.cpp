#include <Arduino.h>
#include <Homie.h>
#include "dot-display.hpp"

#define FIRMWARE_NAME "dot-display"
#define FIRMWARE_VERSION "0.0.6"

/* width of the display in pixels */
const unsigned int DISPLAY_WIDTH = 32; 

/* display conection - CLK -> D5, DATA IN -> D7, CS -> D8 */
DotDisplay the_display(/* clock*/ D5, /*data*/ D7, /*cs=*/D8);
HomieNode display_node("display", "display", "string");

void onHomieEvent(const HomieEvent &event)
{
  switch (event.type)
  {
  case HomieEventType::STANDALONE_MODE:
    the_display.drawSmallText("standalone");
    break;
  case HomieEventType::CONFIGURATION_MODE:
    the_display.drawSmallText("config");
    break;
  case HomieEventType::WIFI_CONNECTED:
    the_display.drawSmallText("on WiFi");
    break;
  case HomieEventType::WIFI_DISCONNECTED:
    the_display.drawSmallText("no WiFi");
    break;
  case HomieEventType::MQTT_READY:
    the_display.drawSmallText("ready");
    break;
  case HomieEventType::MQTT_DISCONNECTED:
    the_display.drawSmallText("no data");
    break;
  case HomieEventType::OTA_STARTED:
    the_display.drawSmallText("updating");
    break;
  case HomieEventType::OTA_SUCCESSFUL:
    the_display.drawSmallText("restarting");
    break;
  case HomieEventType::OTA_FAILED:
    the_display.drawSmallText("failed");
    break;

  case HomieEventType::OTA_PROGRESS:
    the_display.uploadProgress();
    break;
  default:
    break;
  }
}

bool setIntensityHandler(const HomieRange &range, const String &value)
{
  Homie.getLogger() << "IntensityReceived: start" << endl;
  uint8_t new_intensity;
  the_display.setIntensity(100);
  for (unsigned n = 0; n < value.length(); n++)
  {
    if (value[n] > '9')
      return true;
    if (value[n] < '0')
      return true;
  }
  if (value.toInt() > 255)
    return true;
  new_intensity = value.toInt();

  display_node.setProperty("intensity").send(String(new_intensity));
  the_display.setIntensity(new_intensity);
  return true;
}

bool setTextHandler(const HomieRange &range, const String &value)
{
  Homie.getLogger() << "TextReceived: start" << endl;

  String substr = value.substring(0, 32);

  the_display.drawText(substr.c_str());
  return true;
}

int c_to_hex(const unsigned char c) {
  /* convert character to hex int */
  if (c >= '0' && c <='9') return (c-'0');
  if (c >= 'A' && c <='F') return (c-'A'+10);
  if (c >= 'a' && c <='f') return (c-'a'+10);
  return 0;
}

bool setImageHandler(const HomieRange &range, const String &value)
{
  static uint8_t pixels[DISPLAY_WIDTH];  
  Homie.getLogger() << "ImageReceived: start" << endl;  
  // zero 
  memset(pixels, 0, sizeof(pixels));
  unsigned int x = 0;  
  uint8_t px = 0;
  
  the_display.startPixels();  
  for (x = 0; x < DISPLAY_WIDTH; x++) {
    if (value.length() < (2*x+1)) 
      break;    
    px = c_to_hex(value[2*x]) * 16 + c_to_hex(value[2*x+1]);            
    // Homie.getLogger() << px << ",";    
    for (uint8_t n = 0; n < 8; n++) {
      if (px & (1 << n)) {         
        the_display.drawPixel(x, n);
      }
    //  Homie.getLogger() << endl;
    }    
    // Homie.getLogger() << value[2*x] << "->" << c_to_hex(value[2*x]) << ",";    
  }  
  Homie.getLogger() << endl;
  the_display.flushPixels();
  return true;
}

void setup()
{
  the_display.begin();
  Serial.begin(115200);
  Serial << endl;

  Homie.getLogger() << "wifiReset: start" << endl;
  
  //WiFi.disconnect();
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  Homie.getLogger() << "wifiReset: done" << endl;

  //Homie.disableLogging();

  the_display.drawSmallText("booting");
  Homie_setFirmware(FIRMWARE_NAME, FIRMWARE_VERSION);
  display_node.advertise("intensity").settable(setIntensityHandler);
  display_node.advertise("text").settable(setTextHandler);
  display_node.advertise("image").settable(setImageHandler);  
  Homie.onEvent(onHomieEvent);
  Homie.setup();
}

void loop()
{
  Homie.loop();
  the_display.loop();
}