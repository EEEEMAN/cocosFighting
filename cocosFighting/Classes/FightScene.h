#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#define NAME_PLAYER1 "player1"
#define NAME_PLAYER2 "player2"

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "DefineData.h"

class Character;
class Stage;

class FightScene : public cocos2d::Layer
{
private:
	Character* player1;
	Character* player2;
	Stage* stage;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(FightScene);
	virtual void update(float dt);
	void setCameraPos(cocos2d::Vec2 pos); //카메라 위치를 조정
	bool isCollisionWorldSpace(cocos2d::Sprite*, cocos2d::Sprite*) const; //두 상자가 충돌하는지 검사해주는 함수
	cocos2d::Rect convertBoxToWorldSpaceRect(const cocos2d::Sprite* box) const;
	inline Stage* getStage() const { return stage; };
	inline Character* getPlayer1() const { return player1; };
	inline Character* getPlayer2() const { return player2; };
	//키입력
	virtual void f_onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void f_onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
};

#endif