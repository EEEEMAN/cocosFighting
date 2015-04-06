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
	//������ ������ ������
	auto winSize = Director::getInstance()->getWinSize();

	//Ű �Է�
	auto k_listener = EventListenerKeyboard::create();
	k_listener->onKeyPressed = CC_CALLBACK_2(FightScene::f_onKeyPressed, this);
	k_listener->onKeyReleased = CC_CALLBACK_2(FightScene::f_onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(k_listener, this);

	//�������� �ʱ�ȭ
	stage = new Stage();
	auto backGround = stage->getBackGround();
	addChild(backGround);

	player1 = new Character(this, true);
	player2 = new Character(this, false);

	//1�÷��̾�
	player1->setEnemy(player2);
	auto bodyRect = player1->getBodyRect();
	bodyRect->setName(NAME_PLAYER1);
	bodyRect->setPosition(Vec2(backGround->getContentSize().width / 2 - 50, winSize.height / 2));
	backGround->addChild(bodyRect);

	//2�÷��̾�
	player2->setEnemy(player1);
	auto bodyRect2 = player2->getBodyRect();
	bodyRect2->setName(NAME_PLAYER2);
	bodyRect2->setPosition(Vec2(backGround->getContentSize().width / 2 + 50, winSize.height / 2));
	backGround->addChild(bodyRect2);

	setCameraPos(Vec2(backGround->getContentSize().width / 2, backGround->getContentSize().height / 2));

	//update�Լ� ȣ��
	this->scheduleUpdate();
	return true;
}

void FightScene::setCameraPos(cocos2d::Vec2 cPos){
	auto winSize = Director::getInstance()->getWinSize();
	//���ʳ� �˻�
	if (cPos.x - winSize.width / 2 < stage->getMinX()) cPos.x = stage->getMinX() + winSize.width / 2;
	//�����ʳ� �˻�
	if (cPos.x + winSize.width / 2 >= stage->getMaxX()) cPos.x = stage->getMaxX() - winSize.width / 2;
	//�Ʒ��ʳ� �˻�
	if (cPos.y - winSize.height / 2 < stage->getMinY()) cPos.y = stage->getMinY() + winSize.height / 2;
	//���� �� �˻�
	if (cPos.y + winSize.height / 2 >= stage->getMaxY()) cPos.y = stage->getMaxY() - winSize.height / 2;

	//ī�޶���ǥ�� ����ǥ�� ��ȯ
	Vec2 mPos = Vec2(-(cPos.x - winSize.width / 2), -(cPos.y - winSize.height / 2));

	//����
	stage->getBackGround()->setPosition(mPos);
}

void FightScene::update(float dt){
	player1->update(dt);
	player2->update(dt);
	stage->update(dt);
	//�������ڽ� �浹üũ
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
	else if (keyCode == btnm->btn1P_A){
		btnm->setButton1P(ButtonData::BTN_A);
		player1->punch();
	}
	else if (keyCode == btnm->btn1P_B){
		btnm->setButton1P(ButtonData::BTN_B);
	}
	else if (keyCode == btnm->btn1P_C){
		btnm->setButton1P(ButtonData::BTN_C);
	}
	else if (keyCode == btnm->btn1P_start){
		btnm->setButton1P(ButtonData::BTN_START);
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
	else if (keyCode == btnm->btn1P_A){
		btnm->resetButton1P(ButtonData::BTN_A);
	}
	else if (keyCode == btnm->btn1P_B){
		btnm->resetButton1P(ButtonData::BTN_B);
	}
	else if (keyCode == btnm->btn1P_C){
		btnm->resetButton1P(ButtonData::BTN_C);
	}
	else if (keyCode == btnm->btn1P_start){
		btnm->resetButton1P(ButtonData::BTN_START);
	}
}