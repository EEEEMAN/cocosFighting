#include "Character.h"

USING_NS_CC;
using namespace stdext;

Character::Character(FightScene* scene, bool is1Pcha) : parentScene(scene), is1P(is1Pcha), is1PDir(is1Pcha)
{
	//ȭ�������ϱ�
	auto winSize = Director::getInstance()->getWinSize();

	//�������� �ʱ�ȭ
	stage = scene->getStage();

	//�������Ž��ʱ�ȭ
	bodyRect = Sprite::create("blackBox.png");
	bodyRect->setAnchorPoint(Vec2(0.5f, 0.0f));
	if (DEBUG_MODE == 0){
		bodyRect->setOpacity(0);
	}

	//���ִ¸��
	motions.insert(m_hashMap::value_type(MKEY_STAND, new Motion("eman/eman_stand.csb", true)));
	//�ɾ��ִ¸��
	motions.insert(m_hashMap::value_type(MKEY_WALK_FRONT, new Motion("eman/eman_walk_front.csb", true)));
	//�������� ��¸��
	motions.insert(m_hashMap::value_type(MKEY_JUMP_FRONT_UP, new Motion("eman/eman_jump_front_up.csb", true)));
	//�������� �ϰ����
	motions.insert(m_hashMap::value_type(MKEY_JUMP_FRONT_DOWN, new Motion("eman/eman_jump_front_down.csb", true)));
	//�������� ��¸��
	motions.insert(m_hashMap::value_type(MKEY_JUMP_UP, new Motion("eman/eman_jump_up.csb", true)));
	//�������� �ϰ����
	motions.insert(m_hashMap::value_type(MKEY_JUMP_DOWN, new Motion("eman/eman_jump_down.csb", true)));

	//��� �ʱ�ȭ
	neutral();
}
void Character::showLog() const{
	CCLOG("%d", bodyRect->getPositionX() < enemyCharacter->bodyRect->getPositionX());
}

void Character::setEnemy(Character* enemy){
	this->enemyCharacter = enemy;
}

void Character::update(float dt){
	//��� update�Լ� ȣ��
	//currentMotion->update(dt);

	//������� ������ ��������
	if (bodyRect->getPositionX() < enemyCharacter->bodyRect->getPositionX()){
		is1PDir = true;
		if (c_state == CharacterState::neutral) neutral();
	}
	else if (bodyRect->getPositionX() > enemyCharacter->bodyRect->getPositionX()){
		is1PDir = false;
		if (c_state == CharacterState::neutral) neutral();
	}

	//������ ��¿��� �ϰ�������ȯ�Ǹ� �ִϸ��̼� ����
	if (!onGround){
		if (vy > 0 && vy - G_GRAVITY <= 0){
			switch (c_state){
			case CharacterState::jump: doMotion(MKEY_JUMP_DOWN); break;
			case CharacterState::jumpFront: doMotion(MKEY_JUMP_FRONT_DOWN); break;
			case CharacterState::jumpBack: doMotion(MKEY_JUMP_FRONT_UP); break;
			}
		}
	}

	//y�� ó��
	vy -= G_GRAVITY;
	bodyRect->setPositionY(bodyRect->getPositionY() + vy);
	if (bodyRect->getPositionY() < stage->getMinY()){ //������Ҵ���üũ
		vy = 0;
		vx = 0;
		bodyRect->setPositionY(stage->getMinY());
		onGround = true;
	}
	//x�� ó��
	//�ӵ���ŭ ��ġ�̵�
	bodyRect->setPositionX(bodyRect->getPositionX() + vx);
	//ȭ�� ���̸� ����
	if (bodyRect->getPositionX() - (bodyRect->getContentSize().width * 0.5) < stage->getMinX()){//���ʳ�
		bodyRect->setPositionX(stage->getMinX() + (bodyRect->getContentSize().width * 0.5));
	}
	else if (bodyRect->getPositionX() + (bodyRect->getContentSize().width * 0.5) >= stage->getMaxX()){ //�����ʳ�
		bodyRect->setPositionX(stage->getMaxX() - (bodyRect->getContentSize().width * 0.5));
	}

	//Ű�Է� ó��
	auto btnm = ButtonManager::getInstance();
	//1P�� �������� ������ ����
	if (is1P){
		if (btnm->isPressed1P(ButtonData::BTN_UP) && btnm->isPressed1P(ButtonData::BTN_LEFT)){
			jumpLeft();
		}
		if (btnm->isPressed1P(ButtonData::BTN_UP) && btnm->isPressed1P(ButtonData::BTN_RIGHT)){
			jumpRight();
		}
		if (btnm->isPressed1P(ButtonData::BTN_UP)){
			jump();
		}
		if (btnm->isPressed1P(ButtonData::BTN_DOWN)){

		}
		if (btnm->isPressed1P(ButtonData::BTN_LEFT)){
			walkLeft();
		}
		if (btnm->isPressed1P(ButtonData::BTN_RIGHT)){
			walkRight();
		}
		if (btnm->getButtonData1P() == 0){
			if (onGround)
				neutral();
		}
	}
	//2P�� �������� ������ ����
	else{
	}
}

void Character::doMotion(char* motionKey){
	auto it = motions.find(motionKey);
	if (it != motions.end()){
		it->second->playMotion(bodyRect, is1PDir);
		currentMotion = it->second;
	}
}

void Character::neutral(){
	//���º���
	c_state = CharacterState::neutral;
	//�������
	doMotion(MKEY_STAND);
}

void Character::walkLeft(){
	if (!onGround) return;
	//���°� �ȱ���°� �ƴϸ� ����� ����
	if (c_state != CharacterState::moveBack){
		doMotion(MKEY_WALK_FRONT);
		c_state = CharacterState::moveBack;
	}
	//�ӵ���ŭ ��ġ�̵�
	bodyRect->setPositionX(bodyRect->getPositionX() - walkSpeed);
	//ȭ�� ���̸� ����
	if (bodyRect->getPositionX() - (bodyRect->getContentSize().width * 0.5) < stage->getMinX()){//���ʳ�
		bodyRect->setPositionX(stage->getMinX() + (bodyRect->getContentSize().width * 0.5));
	}
}

void Character::walkRight(){
	if (!onGround) return;
	//���°� �ȱ���°� �ƴϸ� ����� ����
	if (c_state != CharacterState::moveFront){
		doMotion(MKEY_WALK_FRONT);
		c_state = CharacterState::moveFront;
	}
	//�ӵ���ŭ ��ġ�̵�
	bodyRect->setPositionX(bodyRect->getPositionX() + walkSpeed);
	//ȭ�� ���̸� ����
	if (bodyRect->getPositionX() + (bodyRect->getContentSize().width * 0.5) >= stage->getMaxX()){ //�����ʳ�
		bodyRect->setPositionX(stage->getMaxX() - (bodyRect->getContentSize().width * 0.5));
	}

}

void Character::jump(){
	if (!onGround) return;
	//y�� �ӵ��� ����
	vy = jumpPower;
	doMotion(MKEY_JUMP_UP);
	c_state = CharacterState::jump;
	onGround = false;
}

void Character::jumpLeft(){
	if (!onGround) return;
	//�ӵ��� ����
	vy += jumpPower;
	vx -= jumpPowerX;
	//�������� �����ִٸ� �Ĺ�����
	if (is1PDir){
		doMotion(MKEY_JUMP_FRONT_DOWN);
		c_state = CharacterState::jumpBack;
	}
	//������ �����ִٸ� ��������
	else{
		doMotion(MKEY_JUMP_FRONT_UP);
		c_state = CharacterState::jumpFront;
	}
	onGround = false;
}

void Character::jumpRight(){
	if (!onGround) return;
	//�ӵ��� ����
	vy += jumpPower;
	vx += jumpPowerX;
	//�������� �����ִٸ� ��������
	if (is1PDir){
		doMotion(MKEY_JUMP_FRONT_UP);
		c_state = CharacterState::jumpFront;
	}
	//������ �����ִٸ� �Ĺ�����
	else{
		doMotion(MKEY_JUMP_FRONT_DOWN);
		c_state = CharacterState::jumpBack;
	}
	onGround = false;
}