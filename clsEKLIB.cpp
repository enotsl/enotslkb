/**
 * @file    clsEKLIB.cpp
 * @author    Stone Lee
 * @date      7-2-2016
 *
 * @mainpage  clsEKLIB
 */

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "./clsEKLIB.h"
#include "./clsEKLED.h"
#include "Keyboard.h"
#include "Mouse.h"

EKLED keyboardLed(LedPort);
/**
 * @name EKLIB constructor
 * @param pin Led pin number
 */
EKLIB::EKLIB(uint8_t *userkeymaps, byte *rowpins, byte *colpins, byte rowscount, byte colscount)
{
	Rows = rowpins;
	Cols = colpins;
	Keymaps = userkeymaps;
	RowsCount = rowscount;
	ColsCount = colscount;
	//定义按下扫描循环次数
	_pressedcount = 1;
	//定义抬起扫描循环次数
	_releasedcount = 1;
	//定义前沿消抖参数1
	_keypressed[12][12];
	//定义后沿消抖参数1
	_keyreleased[12][12];
	//时间数组
	_keytimer[12][12];
	_pressedtimer = millis();
	_releasedtimer = millis();
	//
	_layerindex = 0;
	_currentlayer = 0;
	_fnlayerindex = 0;
}

void EKLIB::init()
{
	Serial.begin(9600);
	for (int row = 0; row < RowsCount; row++)
	{
		//为行端口定义为输出口，用于矩阵扫描时输出
		pinMode(Rows[row], OUTPUT);
	}

	for (int col = 0; col < ColsCount; col++)
	{
		//为列端口定义为上拉输入口，用于矩阵扫描时读取状态
		pinMode(Cols[col], INPUT_PULLUP);
	}

	Keyboard.begin();
	Mouse.begin();
}

void EKLIB::run()
{
	//整个程序的运行周期
	int row;
	int col;

	for (int row = 0; row < RowsCount; row++)
	{
		//设置该行为输出行
		//Serial.println(row);
		pinMode(Rows[row], OUTPUT);
		//为该行端口输出低电平
		digitalWrite(Rows[row], LOW);
		for (int col = 0; col < ColsCount; col++)
		{
			if (digitalRead(Cols[col]) == LOW)
			{ //检测该列是否低电平（本来是高电平的，如果按键按下和列的低电平连接上，则变为低电平）
				//        Serial.print("row=");
				//        Serial.print(row);
				//        Serial.print(" and ");
				//        Serial.print("col=");
				//        Serial.println(col);
				//        Serial.println("------------");
				if (_keypressed[row][col] < _pressedcount)
				{
					_keypressed[row][col] = _pressedcount;
					_keyreleased[row][col] = 0;
					_keytimer[row][col] = millis();
					break;
				}
				//判断是按下，如果消抖延时循环次数，未达到则为循环次数+1,同时无论是不是，都将该按键的抬起延时按下循环次数清0
			}
			else
			{
				if (_keyreleased[row][col] < _pressedcount && _keypressed[row][col] > 0 && millis() - _keytimer[row][col] > DelayTime)
				{
					_keyreleased[row][col] = _releasedcount;
					_keypressed[row][col] = 0;
				}
				//如果没有判断出低电平,再次判断之前这个按键是否已经按下,如果是则为抬起延时+1延时清0，如果不是则不执行操作
			}
			//检测该列是否低电平（本来是高电平的，如果按键按下和列的低电平连接上，则变为低电平）
			if (digitalRead(Cols[col]) == LOW)
			{
				if (_keypressed[row][col] < _pressedcount)
				{
					_keypressed[row][col] = _pressedcount;
					_keyreleased[row][col] = 0;
					_keytimer[row][col] = millis();
					break;
				}
				//判断是按下，如果消抖延时循环次数，未达到则为循环次数+1,同时无论是不是，都将该按键的抬起延时按下循环次数清0
			}
			else
			{
				if (_keyreleased[row][col] < _pressedcount && _keypressed[row][col] > 0 && millis() - _keytimer[row][col] > DelayTime)
				{
					_keyreleased[row][col] = _releasedcount;
					_keypressed[row][col] = 0;
				}
				//如果没有判断出低电平,再次判断之前这个按键是否已经按下,如果是则为抬起延时+1延时清0，如果不是则不执行操作
			}
		}
		//为该行端口输出高电平
		digitalWrite(Rows[row], HIGH);
		//为停止该行输出高电平
		pinMode(Rows[row], INPUT);
		//跳出循环
		if (_keypressed[row][col] == _pressedcount)
		{
			break;
		}
	}

	//以下输出部分
	if ((millis() - _pressedtimer) >= 1)
	{ //按下输出周期
		for (int row = 0; row < RowsCount; row++)
		{
			for (int col = 0; col < ColsCount; col++)
			{
				//判断这列按键之前是否按下或按下间隔达到消抖延时 || _keytimer[col]==0
				if (_keypressed[row][col] == _pressedcount)
				{
					keyboardLed.active();
					doPress(row, col);
					_keypressed[row][col] = _pressedcount + 1; //将输出用按下消抖变成比延时+1,直到按键抬起激
				}
			}
		}
		_pressedtimer = millis();
	}

	if ((millis() - _releasedtimer) >= 1)
	{ //释放输出周期
		for (int row = 0; row < RowsCount; row++)
		{
			for (int col = 0; col < ColsCount; col++)
			{
				if (_keyreleased[row][col] == _releasedcount)
				{
					doRelease(row, col);
					_keytimer[row][col] = 0;
					_keypressed[row][col] = 0;
					_keyreleased[row][col] = _pressedcount + 1;
					//这里是输出按键用的，循环判断消抖是否达到预设值，达到则输出对应矩阵下的按键码操作。
				}
			}
			_releasedtimer = millis();
		}
	}
	//
	keyboardLed.run();
}

void EKLIB::doPress(int row, int col)
{
	//判断所按按键是否功能层键
	//int key = keymaps[_layerindex][row][col];

	int key = Keymaps[_layerindex * RowsCount * ColsCount + row * ColsCount + col];
	//   Serial.print("PRESS key=");
	//   Serial.println(key);
	//   Keyboard.press(key);
	if (key >= 245)
	{
		doAction(key, 1);
		Keyboard.press(key);
		//   }else if(key<=244 && key>= 242){
		//   		doMousePress(key);
		//   }else if(key<=17 && key>=20){
		//   		doMouseMove(key);
	}
	else
	{
		Keyboard.press(key);
	}

	//   switch (key) {
	//     case KC_FN0:
	//       _fnlayerindex = 1;
	//       break;
	//   }
	//   //
	//	 if(_fnlayerindex == 1){
	//	 		 int _pkey = keymaps[_fnlayerindex][row][col];
	//	     if(_pkey == KC_FN1){
	//	        keyboardLed.toggle();
	//	     }
	//	     else if(_pkey == KC_FN2){
	//	        keyboardLed.brightup();
	//	     }
	//	     else if(_pkey == KC_FN3){
	//	        keyboardLed.brightdown();
	//	     }
	//	     else if(_pkey == KC_FN4){
	//	        keyboardLed.setshowstyle(1);
	//	     }
	//	     else if(_pkey == KC_FN5){
	//			    if (!Mouse.isPressed(MOUSE_LEFT)) {
	//			      Mouse.press(MOUSE_LEFT);
	//			    }
	//	     }
	//	     else{
	//	        Keyboard.press(_pkey);
	//	     }
	//   }else{
	//	 		Keyboard.press(key);
	//	 }
}

void EKLIB::doRelease(int row, int col)
{
	//int key = keymaps[_layerindex][row][col];
	int key = Keymaps[_layerindex * RowsCount * ColsCount + row * ColsCount + col];
	//   Serial.print("RELEASE key=");
	//   Serial.println(key);
	//   Keyboard.release(key);
	if (key >= 245)
	{
		doAction(key, 0);
		Keyboard.release(key);
		//   }else if(key<=244 && key>= 242){
		//   		doMouseRelease(key);
		//   }else if(key<=17 && key>=20){
		//   		doMouseMove(key);
	}
	else
	{
		Keyboard.release(key);
	}

	//  switch (keymaps[0][row][col]) { //判断所按按键是否功能层键
	//    case KC_FN0:
	//      _fnlayerindex = 0;
	//      break;
	//    case KC_FN5:
	//	    if (Mouse.isPressed(MOUSE_LEFT)) {
	//	      Mouse.release(MOUSE_LEFT);
	//	    }
	//      break;
	//    default:
	//      //Keyboard.release(keymaps[0][row][col]);
	//      //Keyboard.release(keymaps[1][row][col]);
	//      	//Serial.print("sizeof=");
	//      	//Serial.print(sizeof(keymaps)/sizeof(int));
	//			  int idx;
	//				for (int idx = 0; idx < 10; idx++) {
	//					Keyboard.release(keymaps[idx][row][col]);
	//				}
	//  }
}

// void EKLIB::doMousePress(int key){
// 	if(key == 244){
//     if (!Mouse.isPressed(MOUSE_LEFT)) {
//       Mouse.press(MOUSE_LEFT);
//     }
//   }else if(key == 243){
//     if (!Mouse.isPressed(MOUSE_MIDDLE)) {
//       Mouse.press(MOUSE_MIDDLE);
//     }
//   }else if(key == 242){
//     if (!Mouse.isPressed(MOUSE_RIGHT)) {
//       Mouse.press(MOUSE_RIGHT);
//     }
//   }
// }

// void EKLIB::doMouseRelease(int key){
// 	if(key == 244){
//     if (Mouse.isPressed(MOUSE_LEFT)) {
//       Mouse.release(MOUSE_LEFT);
//     }
//   }else if(key == 243){
//     if (Mouse.isPressed(MOUSE_MIDDLE)) {
//       Mouse.release(MOUSE_MIDDLE);
//     }
//   }else if(key == 242){
//     if (Mouse.isPressed(MOUSE_RIGHT)) {
//       Mouse.release(MOUSE_RIGHT);
//     }
//   }
// }

// void EKLIB::doMouseMove(int key){
// 		Serial.println(key);
// 		Mouse.move(100, 100, 0);
// }

void EKLIB::doAction(int fnkey, int pressed)
{
	int idx;
	for (int idx = 0; idx < 10; idx++)
	{
		if (fnkey == fn_actions[idx][0])
		{
			Serial.println(fn_actions[idx][0]);
			fnActions(fn_actions[idx][1], fn_actions[idx][2], fn_actions[idx][3], pressed);
			break;
		}
	}
}

void EKLIB::fnActions(int fnkey, int param, int idx, int pressed)
{
	switch (fnkey)
	{
	case 0:
		ACTION_LAYER_MOMENTARY(param, pressed);
		break;
	case 1:
		ACTION_DEFAULT_LAYER_SET(param, pressed);
		break;
	case 2:
		ACTION_BACKLIGHT_TOGGLE(pressed);
		break;
	case 3:
		ACTION_BACKLIGHT_INCREASE(pressed);
		break;
	case 4:
		ACTION_BACKLIGHT_DECREASE(pressed);
		break;
	case 5:
		ACTION_BACKLIGHT_BREATHING(pressed);
		break;
	case 6:
		ACTION_MODS_KEY(idx, pressed);
		break;
	case 7:
		ACTION_PRINT_KEY(idx, pressed);
		break;
	case 8:
		ACTION_MACRO_KEY(idx, pressed);
		break;
	}
}

//执行函数0
void EKLIB::ACTION_LAYER_MOMENTARY(int param, int pressed)
{
	if (pressed == 1)
	{
		_layerindex = param;
	}
	else
	{
		_layerindex = _currentlayer;
	}
}
//执行函数1
void EKLIB::ACTION_DEFAULT_LAYER_SET(int param, int pressed)
{
	if (pressed == 1)
	{
		if (_layerindex != param)
		{
			_layerindex = param;
			_currentlayer = param;
		}
	}
}
//执行函数2
void EKLIB::ACTION_BACKLIGHT_TOGGLE(int pressed)
{
	if (pressed == 1)
	{
		keyboardLed.toggle();
	}
}
//执行函数3
void EKLIB::ACTION_BACKLIGHT_INCREASE(int pressed)
{
	if (pressed == 1)
	{
		keyboardLed.brightup();
	}
}
//执行函数4
void EKLIB::ACTION_BACKLIGHT_DECREASE(int pressed)
{
	if (pressed == 1)
	{
		keyboardLed.brightdown();
	}
}
//执行函数5
void EKLIB::ACTION_BACKLIGHT_BREATHING(int pressed)
{
	if (pressed == 1)
	{
		keyboardLed.setshowstyle(1);
	}
}
//执行函数6
void EKLIB::ACTION_MODS_KEY(int idx, int pressed)
{
	for (int i = 0; i < 6; i++)
	{
		int _key = modkey[idx][i];
		if (_key != 0)
		{
			if (pressed == 1)
			{
				Keyboard.press(_key);
			}
			else
			{
				Keyboard.releaseAll();
			}
		}
	}
}
//执行函数7
void EKLIB::ACTION_PRINT_KEY(int idx, int pressed)
{
	if (pressed == 1)
	{
		Serial.println(textkey[idx]);
		Keyboard.print(textkey[idx]);
		delay(200);
	}
}
//执行函数8
void EKLIB::ACTION_MACRO_KEY(int idx, int pressed)
{
	if (pressed == 1)
	{
	}
}
