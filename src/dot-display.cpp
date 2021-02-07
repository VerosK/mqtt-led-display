#include "dot-display.hpp"

void DotDisplay::drawSmallText(const char *text)
{
    this->display.clearBuffer();
    this->display.setDrawColor(1);
    this->display.setFont(u8g2_font_4x6_mr);    
    this->display.setDrawColor(1);
    this->display.drawStr(0, 7, text);
    this->display.sendBuffer();
}

void DotDisplay::drawText(const char *text)
{
    this->display.clearBuffer();
    this->display.setDrawColor(1);
    this->display.setFont(u8g2_font_5x8_mr);
    this->display.setDrawColor(1);
    this->display.drawStr(0, 7, text);
    this->display.sendBuffer();
}

void DotDisplay::loop()
{
    static unsigned int next_change = 0;
    static int color = 0;
    if (millis() > next_change)
    {
        this->display.setDrawColor(color);
        this->display.drawPixel(31, 0);
        this->display.sendBuffer();
        if (color)
        {
            next_change = millis() + 100;
        }
        else
        {
            next_change = millis() + 9900;
        }
        color = (color + 1) % 2;
    }
}

void DotDisplay::uploadProgress()
{
    static int phase = 0;
    phase = (phase + 1) % 32;

    this->display.setDrawColor(2); // XOR
    this->display.drawPixel(phase, 0);
    this->display.sendBuffer();
}

void DotDisplay::drawBitmap(uint8_t width, uint8_t height, const uint8_t *bitmap) 
{
    this->display.setColorIndex(1); // bitmap is drawn
    this->display.setBitmapMode(0); // bitmap is not transparent
    this->display.drawXBM(0, 0, width, height, bitmap);
    this->display.sendBuffer();
}

void DotDisplay::drawPixel(uint8_t x, uint8_t y) {
    this->display.drawPixel(x, y);
}