#include "Stage.h"

USING_NS_CC;

Stage::Stage()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	backGround = Sprite::create("stage_back.png");
	backGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	stageWidth = backGround->getContentSize().width;
	stageHeight = backGround->getContentSize().height;
	minX = 0;
	maxX = stageWidth;
	minY = stageHeight * 0.2;
	maxY = stageHeight;
}


Stage::~Stage()
{
}
