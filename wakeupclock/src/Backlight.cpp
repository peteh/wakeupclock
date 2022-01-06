#include "Backlight.h"

void Backlight::begin(uint8_t brightness)
{
    pinMode(m_backlightPin, OUTPUT);

    // TODO move this somewhere more reasonable
#define PWM1_Ch 0
#define PWM1_Res 8
#define PWM1_Freq 1000
#define DEFAULT_BRIGHTNESS 255

    ledcAttachPin(m_backlightPin, m_pwmChannel);
    ledcSetup(m_pwmChannel, PWM1_Freq, PWM1_Res);

    setBrightness(brightness);
}

void Backlight::setBrightness(uint8_t brightness)
{
    ledcWrite(m_pwmChannel, brightness);
}