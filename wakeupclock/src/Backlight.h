#pragma once
#include <Arduino.h>
class Backlight
{
public:
    Backlight(uint8_t backlightPin, uint8_t pwmChannel)
        : m_backlightPin(backlightPin){};

    void begin(uint8_t brightness = 255);
    void setBrightness(uint8_t brightness);

private:
    uint8_t m_backlightPin;
    uint8_t m_pwmChannel;
};
