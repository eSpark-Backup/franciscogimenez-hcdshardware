#include "RgbLedLogic.hpp"
#include "Libraries/Adafruit_NeoPixel.h"
#include "Pinout.h"
#include "Config.h"

Adafruit_NeoPixel m_Pixels(NEOPIXEL_NUMBER_OF_RGBS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

RgbLedLogic::RgbLedLogic()
{
    m_Pixels.begin();
}

RgbLedLogic::~RgbLedLogic()
{

}

void RgbLedLogic::SetDiodeColor(int diode, Color color)
{
    m_Pixels.setPixelColor(diode, m_Pixels.Color(color.red, color.green, color.blue));
    m_Pixels.show();
}

void RgbLedLogic::TurnOffAllLeds()
{
    m_Pixels.clear();
    m_Pixels.show();
}