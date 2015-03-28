#include "Character.h"

USING_NS_CC;
using namespace stdext;

Character::Character()
{
	//ȭ�������ϱ�
	auto winSize = Director::getInstance()->getWinSize();

	//�����ʱ�ȭ
	is1PDir = true;

	//�̵��ӵ��ʱ�ȭ
	walkSpeed = 4;

	//�������Ž��ʱ�ȭ
	bodyRect = Sprite::create("blackBox.png");

	//���ִ¸��
	motions.insert(m_hashMap::value_type(MKEY_STAND, new Motion("eman/eman_stand.csb")));
	//�ɾ��ִ¸��
	motions.insert(m_hashMap::value_type(MKEY_WALK_FRONT, new Motion("eman/eman_walk_front.csb")));

	//��� �ʱ�ȭ
	neutral();
}

void Character::update(float dt){
	auto btnm = ButtonManager::getInstance();
	if (is1P){
		bool isNeutral = true;
		if (btnm->btn1P_up.isPressed){

		}
		if (btnm->btn1P_down.isPressed){

		}
		if (btnm->btn1P_left.isPressed){
			walkLeft();
			isNeutral = false;
		}
		if (btnm->btn1P_right.isPressed){
			walkRight();
			isNeutral = false;
		}

		if (isNeutral){
			neutral();
		}
	}
}

void Character::doMotion(char* motionKey){
	auto it = motions.find(motionKey);
	if (it != motions.end()){
		it->second->playMotion(bodyRect, is1PDir);
	}
}

void Character::neutral(){
	//���º���
	c_state = CharacterState::neutral;
	//�������
	doMotion(MKEY_STAND);
}

void Character::walkLeft(){
	//�������� �����ִٸ� ����
	if (is1PDir){
		//���°� �ȱ���°� �ƴϸ� ����� ����
		if (c_state != CharacterState::moveBack){
			doMotion(MKEY_WALK_FRONT);
			c_state = CharacterState::moveBack;
		}
		//�ӵ���ŭ ��ġ�̵�
		bodyRect->setPositionX(bodyRect->getPositionX() - walkSpeed);
	}
	//������ �����ִٸ� ����
	else{
		//���°� �ȱ���°� �ƴϸ� ����� ����
		if (c_state != CharacterState::moveFront){
			doMotion(MKEY_WALK_FRONT);
			c_state = CharacterState::moveFront;
		}
		//�ӵ���ŭ ��ġ�̵�
		bodyRect->setPositionX(bodyRect->getPositionX() + walkSpeed);
	}
}

void Character::walkRight(){
	//�������� �����ִٸ� ����
	if (is1PDir){
		//���°� �ȱ���°� �ƴϸ� ����� ����
		if (c_state != CharacterState::moveFront){
			doMotion(MKEY_WALK_FRONT);
			c_state = CharacterState::moveFront;
		}
		//�ӵ���ŭ ��ġ�̵�
		bodyRect->setPositionX(bodyRect->getPositionX() + walkSpeed);
	}
	//������ �����ִٸ� ����
	else{
		//���°� �ȱ���°� �ƴϸ� ����� ����
		if (c_state != CharacterState::moveBack){
			doMotion(MKEY_WALK_FRONT);
			c_state = CharacterState::moveBack;
		}
		//�ӵ���ŭ ��ġ�̵�
		bodyRect->setPositionX(bodyRect->getPositionX() - walkSpeed);
	}
}