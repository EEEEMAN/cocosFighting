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