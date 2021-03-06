#include <U8g2lib.h>

class DotDisplay
{
private:
    U8G2_MAX7219_32X8_1_4W_SW_SPI display;

public:
    DotDisplay(uint8_t clock, uint8_t data, uint8_t cs) : 
    display(
        /* rotation =*/U8G2_R0,
        /* clock=*/clock, /* data=*/data, /* cs=*/cs,
        /* dc=*/U8X8_PIN_NONE, /* reset=*/U8X8_PIN_NONE){};
    
    void begin()
    {
        this->display.begin();
        this->display.setContrast(8);
    };
    void loop();
    void drawSmallText(const char *text);
    void drawText(const char *text);
    void setIntensity(uint8_t n)
    {
        this->display.setContrast(n);
    }
    void drawBitmap(uint8_t width, uint8_t height, const uint8_t *bitmap);

    void startPixels() { this->display.clearBuffer(); this->display.setDrawColor(1); }
    void flushPixels() { this->display.sendBuffer(); }
    void drawPixel(uint8_t x, uint8_t y);        
    void uploadProgress();
};