#ifndef __BUTTON_MANAGER_H__
#define __BUTTON_MANAGER_H__

#include "cocos2d.h"

typedef cocos2d::EventKeyboard::KeyCode k_code;

class CustomButton{
public:
	CustomButton(k_code code, bool isp) : keyCode(code), isPressed(isp){};
	k_code keyCode;
	bool isPressed;
};

class ButtonManager
{
public:
	CustomButton btn1P_up = CustomButton(k_code::KEY_UP_ARROW, false);
	CustomButton btn1P_down = CustomButton(k_code::KEY_DOWN_ARROW, false);
	CustomButton btn1P_left = CustomButton(k_code::KEY_LEFT_ARROW, false);
	CustomButton btn1P_right = CustomButton(k_code::KEY_RIGHT_ARROW, false);
	CustomButton btn1P_A = CustomButton(k_code::KEY_A, false);
	CustomButton btn1P_B = CustomButton(k_code::KEY_S, false);
	CustomButton btn1P_C = CustomButton(k_code::KEY_D, false);
	CustomButton btn1P_start = CustomButton(k_code::KEY_1, false);
private:
	ButtonManager();
public:
	static ButtonManager* getInstance();
};

#endif