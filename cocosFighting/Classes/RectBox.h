#ifndef __RECT_BOX_H__
#define __RECT_BOX_H__

#include "cocos2d.h"
#include "DefineData.h"

class RectBox
{
private:
	bool isRed;
	Character* owner; //�����ڽ��� ����
	int hitDelay;
	int damage;
	cocos2d::Sprite* sprite;
public:
	bool isHit; //�̹� �浹�� �������� true
public:
	RectBox(cocos2d::Sprite* rectSprite, Character* ownerCha); //�Ķ�
	RectBox(cocos2d::Sprite* rectSprite, Character* ownerCha, int delay, int dmg); //����
	inline int getHitDelay() const{ return hitDelay; };
	inline int getDamage() const { return damage; };
	inline bool isRedBox() const { return isRed; };
	inline cocos2d::Sprite* getSprite() const { return sprite; };
};

#endif