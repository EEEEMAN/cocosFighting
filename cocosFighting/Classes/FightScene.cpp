#include "FightScene.h"

USING_NS_CC;

Scene* FightScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FightScene::create();
	scene->addChild(layer);
	return scene;
}

bool FightScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//윈도우 사이즈 가져옴
	auto winSize = Director::getInstance()->getWinSize();

	//키 입력
	auto k_listener = EventListenerKeyboard::create();
	k_listener->onKeyPressed = CC_CALLBACK_2(FightScene::f_onKeyPressed, this);
	k_listener->onKeyReleased = CC_CALLBACK_2(FightScene::f_onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(k_listener, this);

	//스테이지 초기화
	stage = new Stage();
	addChild(stage->getBackGround());

	player1 = new Character(this, true);
	player2 = new Character(this, false);

	//1플레이어
	player1->setEnemy(player2);
	auto bodyRect = player1->getBodyRect();
	bodyRect->setPosition(Vec2(winSize.width * 0.3, winSize.height / 2));
	stage->getBackGround()->addChild(bodyRect);

	//2플레이어
	player2->setEnemy(player1);
	auto bodyRect2 = player2->getBodyRect();
	bodyRect2->setPosition(Vec2(winSize.width  * 0.7, winSize.height / 2));
	stage->getBackGround()->addChild(bodyRect2);

	//update함수 호출
	this->scheduleUpdate();
	return true;
}

void FightScene::update(float dt){
	player1->update(dt);
	player2->update(dt);
	//몸판정박스 충돌체크
	auto rect1 = player1->getBodyRect();
	auto rect2 = player2->getBodyRect();
	while (rect1->getBoundingBox().intersectsRect(rect2->getBoundingBox())){
		if (rect1->getPositionX() < rect2->getPositionX()){
			rect1->setPositionX(rect1->getPositionX() - 1);
			rect2->setPositionX(rect2->getPositionX() + 1);
		}
		else if (rect1->getPositionX() > rect2->getPositionX()){
			rect1->setPositionX(rect1->getPositionX() + 1);
			rect2->setPositionX(rect2->getPositionX() - 1);
		}
		else{
			rect1->setPositionX(rect1->getPositionX() + player1->vx);
			rect2->setPositionX(rect2->getPositionX() + player2->vx);
		}
	}
}

void FightScene::f_onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	auto btnm = ButtonManager::getInstance();
	if (keyCode == k_code::KEY_D){
		player1->showLog();
		player2->showLog();
	}
	if (keyCode == btnm->btn1P_up){
		btnm->setButton1P(ButtonData::BTN_UP);
	}
	else if (keyCode == btnm->btn1P_down){
		btnm->setButton1P(ButtonData::BTN_DOWN);
	}
	else if (keyCode == btnm->btn1P_left){
		btnm->setButton1P(ButtonData::BTN_LEFT);
	}
	else if (keyCode == btnm->btn1P_right){
		btnm->setButton1P(ButtonData::BTN_RIGHT);
	}
}

void FightScene::f_onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	auto btnm = ButtonManager::getInstance();
	if (keyCode == btnm->btn1P_up){
		btnm->resetButton1P(ButtonData::BTN_UP);
	}
	else if (keyCode == btnm->btn1P_down){
		btnm->resetButton1P(ButtonData::BTN_DOWN);
	}
	else if (keyCode == btnm->btn1P_left){
		btnm->resetButton1P(ButtonData::BTN_LEFT);
	}
	else if (keyCode == btnm->btn1P_right){
		btnm->resetButton1P(ButtonData::BTN_RIGHT);
	}
}