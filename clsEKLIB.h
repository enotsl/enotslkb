/**
 * @file    clsEKLIB.h
 * @author    Stone Lee
 * @date      7-2-2016
 *
 * @mainpage  clsEKLIB
 */

#ifndef CLSEKLIB_H_
#define CLSEKLIB_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "keycode.h"
#include "Mouse.h"

extern const int DelayTime;
extern const int LedPort;
extern const uint8_t fn_actions[][4];
extern const uint8_t modkey[][6];
extern const uint8_t macrokey[][99][3];
extern const char *textkey[];

class EKLIB
{
  public:
	EKLIB(uint8_t *userkeymaps, byte *rowpins, byte *colpins, byte rowscount, byte colscount);
	void init();
	void run();
	//
  private:
	uint8_t *Keymaps;
	byte *Rows;
	byte *Cols;
	byte RowsCount;
	byte ColsCount;

	int _pressedcount;
	int _releasedcount;
	int _keypressed[12][12];
	int _keyreleased[12][12];
	//
	unsigned long _keytimer[12][12];
	unsigned long _pressedtimer;
	unsigned long _releasedtimer;
	//
	int _layerindex;
	int _currentlayer;
	int _fnlayerindex;
	//
	void doPress(int row, int col);
	void doRelease(int row, int col);
	//
	void doMousePress(int key);
	void doMouseRelease(int key);
	void doMouseMove(int key);
	//
	void doAction(int fnkey, int pressed);
	void fnActions(int fnkey, int param, int idx, int pressed);
	void ACTION_LAYER_MOMENTARY(int param, int pressed);
	void ACTION_DEFAULT_LAYER_SET(int param, int pressed);
	void ACTION_BACKLIGHT_TOGGLE(int pressed);
	void ACTION_BACKLIGHT_DECREASE(int pressed);
	void ACTION_BACKLIGHT_INCREASE(int pressed);
	void ACTION_BACKLIGHT_BREATHING(int pressed);
	void ACTION_MODS_KEY(int idx, int pressed);
	void ACTION_PRINT_KEY(int idx, int pressed);
	void ACTION_MACRO_KEY(int idx, int pressed);
};

#endif /* CLSEKLIB_H_ */
