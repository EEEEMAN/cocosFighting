#include "RectBox.h"

RectBox::RectBox(cocos2d::Sprite* rectSprite, Character* ownerCha)
	: sprite(rectSprite), isHit(false), owner(ownerCha), hitDelay(0), damage(0), isRed(false)
{
}

RectBox::RectBox(cocos2d::Sprite* rectSprite, Character* ownerCha, int delay, int dmg)
	: sprite(rectSprite), isHit(false), owner(ownerCha), hitDelay(delay), damage(dmg), isRed(true)
{
}