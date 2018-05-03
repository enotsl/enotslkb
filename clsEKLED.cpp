/**
 * @file    clsEKLED.cpp
 * @author    Enotsl Lee
 * @date      5-3-2018
 *
 * @mainpage  clsEKLED
 */

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>
#include "clsEKLED.h"

/**
 * @name EKLED constructor
 * @param pin Led pin number
 */
EKLED::EKLED(int pin)
{
	_pin = pin;
	_brightness = 255;
	_fadeamount = 5;
	_brightnessLevel = Led_BrightnessLevel
		_brightnessLevelIdx = Led_BrightnessLevel;
	_brightnessLevelUnit = 255 / _brightnessLevel;
	//
	_ledshowstyle = 0;
	_ledstatus = 0;
	_lastactivetimer = millis();
	//
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, HIGH);

	_ledval = EEPROM.read(0);
	_brightnessLevelIdx = _ledval;
	analogWrite(_pin, _brightnessLevelUnit * _brightnessLevelIdx);
	Serial.begin(9600);
}

void EKLED::toggle()
{
	if (_ledshowstyle == 0)
	{
		if (_brightnessLevelIdx > 0)
		{
			_brightnessLevelIdx = 0;
		}
		else
		{
			_brightnessLevelIdx = _brightnessLevel;
		}
		analogWrite(_pin, _brightnessLevelUnit * _brightnessLevelIdx);
		_ledval = EEPROM.read(0);
		Serial.print("_ledval=");
		Serial.print(_ledval);
		Serial.println("------------");
		EEPROM.write(0, _brightnessLevelIdx);
	}
	else if (_ledshowstyle == 1)
	{
		ledon();
		_ledshowstyle = 0;
	}
}

void EKLED::ledon()
{
	_ledval = EEPROM.read(0);
	_brightnessLevelIdx = _ledval;
	analogWrite(_pin, _brightnessLevelUnit * _brightnessLevelIdx);
}

void EKLED::ledoff()
{
	_brightnessLevelIdx = 0;
	analogWrite(_pin, _brightnessLevelUnit * _brightnessLevelIdx);
}

void EKLED::brightup()
{
	_brightnessLevelIdx++;
	if (_brightnessLevelIdx > _brightnessLevel)
	{
		_brightnessLevelIdx = _brightnessLevel;
	}
	analogWrite(_pin, _brightnessLevelUnit * _brightnessLevelIdx);
	EEPROM.write(0, _brightnessLevelIdx);
}

void EKLED::brightdown()
{
	_brightnessLevelIdx--;
	if (_brightnessLevelIdx < 1)
	{
		_brightnessLevelIdx = 1;
	}
	analogWrite(_pin, _brightnessLevelUnit * _brightnessLevelIdx);
	EEPROM.write(0, _brightnessLevelIdx);
}

void EKLED::breathinglight()
{
	//_brightnessLevelIdx = _brightnessLevel;
	if (_brightnessLevelIdx > 0)
	{
		if ((millis() - _ledtimer) >= 30)
		{
			analogWrite(_pin, _brightness);
			_brightness = _brightness + _fadeamount;
			if (_brightness > 255)
			{
				_brightness = 255;
			}
			if (_brightness < 0)
			{
				_brightness = 0;
			}
			if (_brightness == 0 || _brightness == 255)
			{
				//��������������ʱ���з�ת
				_fadeamount = _fadeamount * -1;
			}
			_ledtimer = millis();
		}
	}
}

void EKLED::active()
{
	_lastactivetimer = millis();
	if (_ledstatus > 0)
	{
		ledon();
		_ledstatus = 0;
	}
}

void EKLED::setshowstyle(int idx)
{
	_ledshowstyle = idx;
}

void EKLED::run()
{
	if (_ledstatus == 0)
	{
		if ((millis() - _lastactivetimer) >= 30000)
		{
			_ledshowstyle = 1;
			_ledstatus = 1;
		}
	}
	if (_ledstatus == 1)
	{
		if ((millis() - _lastactivetimer) >= 60000)
		{
			ledoff();
			_ledshowstyle = 0;
			_ledstatus = 2;
		}
	}
	if (_ledshowstyle == 1)
	{
		breathinglight();
	}
}
