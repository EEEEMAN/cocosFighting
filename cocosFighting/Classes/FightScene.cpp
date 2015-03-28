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

	auto background = Sprite::create("HelloWorld.png");
	background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	background->setScaleX(winSize.width / background->getContentSize().width);
	background->setScaleY(winSize.height / background->getContentSize().height);
	addChild(background);

	player1 = new Character();
	auto bodyRect = player1->getBodyRect();
	bodyRect->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	addChild(bodyRect);

	//update함수 호출
	this->scheduleUpdate();
	return true;
}

void FightScene::update(float dt){
	player1->update(dt);
}

void FightScene::f_onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	auto btnm = ButtonManager::getInstance();
	if (keyCode == btnm->btn1P_up.keyCode){
		btnm->btn1P_up.isPressed = true;
	}
	else if (keyCode == btnm->btn1P_down.keyCode){
		btnm->btn1P_down.isPressed = true;
	}
	else if (keyCode == btnm->btn1P_left.keyCode){
		btnm->btn1P_left.isPressed = true;
	}
	else if (keyCode == btnm->btn1P_right.keyCode){
		btnm->btn1P_right.isPressed = true;
	}
}

void FightScene::f_onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	auto btnm = ButtonManager::getInstance();
	if (keyCode == btnm->btn1P_up.keyCode){
		btnm->btn1P_up.isPressed = false;
	}
	else if (keyCode == btnm->btn1P_down.keyCode){
		btnm->btn1P_down.isPressed = false;
	}
	else if (keyCode == btnm->btn1P_left.keyCode){
		btnm->btn1P_left.isPressed = false;
	}
	else if (keyCode == btnm->btn1P_right.keyCode){
		btnm->btn1P_right.isPressed = false;
	}
}