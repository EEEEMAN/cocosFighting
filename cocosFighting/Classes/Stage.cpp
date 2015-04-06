#include "Stage.h"

USING_NS_CC;

Stage::Stage()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	backGround = Sprite::create("stage_back.png");
	backGround->setAnchorPoint(Vec2(0, 0));
	stageWidth = backGround->getContentSize().width;
	stageHeight = backGround->getContentSize().height;
	minX = 0;
	maxX = stageWidth;
	minY = 0;
	maxY = stageHeight;
	groundPos = stageHeight * 0.2;
}

void Stage::update(float dt){
	if (!backGround) { CCLOG("background is null"); return; }
	auto player1 = dynamic_cast<cocos2d::Sprite*>(backGround->getChildByName(NAME_PLAYER1));
	if (!player1) { CCLOG("player1 is null"); return; }
	auto player2 = dynamic_cast<cocos2d::Sprite*>(backGround->getChildByName(NAME_PLAYER2));
	if (!player2) { CCLOG("player2 is null"); return; }

	//1p와 2p사이의 중간지점을 구함
	float centerX = 0;
	float centerY = 0;
	if (player1->getPositionX() > player2->getPositionX()){ //1p가 왼쪽에 있을경우
		centerX = player1->getPositionX() + (player2->getPositionX() - player1->getPositionX()) / 2;
	}
	else{ //2p가 왼쪽에 있을경우
		centerX = player2->getPositionX() + (player1->getPositionX() - player2->getPositionX()) / 2;
	}
	if (player1->getPositionY() > player2->getPositionY()){ //1p가 아래에 있을경우
		centerY = player1->getPositionY() + (player2->getPositionY() - player1->getPositionY()) / 2;
	}
	else{ //2p가 아래에 있을경우
		centerY = player2->getPositionY() + (player1->getPositionY() - player2->getPositionY()) / 2;
	}

	if (centerX != 0 && centerY != 0){
		dynamic_cast<FightScene*>(backGround->getParent())->setCameraPos(Vec2(centerX, centerY));
	}
}