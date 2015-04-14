#include "ButtonManager.h"


ButtonManager::ButtonManager(){
}

ButtonManager* ButtonManager::getInstance(){
	static ButtonManager* instance;
	if (!instance){
		instance = new ButtonManager();
	}
	return instance;
}

bool ButtonManager::isPressed1P(const unsigned char value) const{
	unsigned char result = (buttonData1P & (unsigned char)value);
	return (result != 0 ? true : false);
}

void ButtonManager::setButton1P(const unsigned char value){
	buttonData1P |= (unsigned char)value;
}

void ButtonManager::resetButton1P(const unsigned char value){
	buttonData1P &= ~(unsigned char)value;
}

bool ButtonManager::isPressed(const unsigned char btnData, const unsigned char value) const{
	unsigned char result = (btnData & (unsigned char)value);
	return (result != 0 ? true : false);
}