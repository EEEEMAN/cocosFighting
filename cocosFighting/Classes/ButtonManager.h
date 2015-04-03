#ifndef __BUTTON_MANAGER_H__
#define __BUTTON_MANAGER_H__

#include "cocos2d.h"

typedef cocos2d::EventKeyboard::KeyCode k_code;

enum ButtonData{
	BTN_UP = (1 << 7),
	BTN_DOWN = (1 << 6),
	BTN_LEFT = (1 << 5),
	BTN_RIGHT = (1 << 4),
	BTN_A = (1 << 3),
	BTN_B = (1 << 2),
	BTN_C = (1 << 1),
	BTN_START = (1 << 0)
};

class ButtonManager
{
private:
	unsigned char buttonData1P = 0; //2진수로 왼쪽부터 위,아래,왼쪽,오른쪽,A,B,C,START. 0이면 안눌러짐, 1이면 눌러짐
public:
	k_code btn1P_up = k_code::KEY_UP_ARROW;
	k_code btn1P_down = k_code::KEY_DOWN_ARROW;
	k_code btn1P_left = k_code::KEY_LEFT_ARROW;
	k_code btn1P_right = k_code::KEY_RIGHT_ARROW;
	k_code btn1P_A = k_code::KEY_A;
	k_code btn1P_B = k_code::KEY_S;
	k_code btn1P_C = k_code::KEY_D;
	k_code btn1P_start = k_code::KEY_1;
private:
	ButtonManager();
public:
	static ButtonManager* getInstance();
	bool isPressed1P(const unsigned char value) const;
	void setButton1P(const unsigned char value);
	void resetButton1P(const unsigned char value);
	inline unsigned char getButtonData1P() const { return buttonData1P; };
};

#endif