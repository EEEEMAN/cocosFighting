#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Motion.h"
#include "ButtonManager.h"
#include "cocostudio\CocoStudio.h"

class FightScene : public cocos2d::Layer
{
private:
	Character* player1;
	Character* player2;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(FightScene);
	virtual void update(float dt);
	//Å°ÀÔ·Â
	virtual void f_onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void f_onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
};

#endif