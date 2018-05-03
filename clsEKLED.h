/**
 * @file    clsEKLED.h
 * @author    Enotsl Lee
 * @date      5-3-2018
 *
 * @mainpage  clsEKLED
 */

#ifndef CLSEKLED_H_
#define CLSEKLED_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>

#define DEBUG 1
#define Led_BrightnessLevel 5;

class EKLED
{
  public:
    EKLED(int pin);
    void toggle();
    void ledon();
    void ledoff();
    void brightup();
    void brightdown();
    void breathinglight();
    void active();
    void setshowstyle(int idx);
    void run();

  private:
    int _pin;
    int _brightness;
    int _fadeamount;
    int _brightnessLevel;
    int _brightnessLevelIdx;
    int _brightnessLevelCount;
    int _brightnessLevelUnit;
    //
    int _ledval;
    int _ledshowstyle;
    int _ledstatus;

    unsigned long _ledtimer;
    unsigned long _lastactivetimer;
};

#endif /* CLSEKLED_H_ */
