#ifndef __RECT_BOX_H__
#define __RECT_BOX_H__

#include "cocos2d.h"
#include "DefineData.h"

class RectBox
{
private:
	bool isRed;
	Character* owner; //판정박스의 주인
	int hitDelay;
	int damage;
	cocos2d::Sprite* sprite;
public:
	bool isHit; //이미 충돌이 끝났으면 true
public:
	RectBox(cocos2d::Sprite* rectSprite, Character* ownerCha); //파랑
	RectBox(cocos2d::Sprite* rectSprite, Character* ownerCha, int delay, int dmg); //빨강
	inline int getHitDelay() const{ return hitDelay; };
	inline int getDamage() const { return damage; };
	inline bool isRedBox() const { return isRed; };
	inline cocos2d::Sprite* getSprite() const { return sprite; };
};

#endif