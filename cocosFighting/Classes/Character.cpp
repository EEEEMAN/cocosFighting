#include "Character.h"

USING_NS_CC;
using namespace stdext;

Character::Character()
{
	//화면사이즈구하기
	auto winSize = Director::getInstance()->getWinSize();

	//방향초기화
	is1PDir = true;

	//이동속도초기화
	walkSpeed = 4;

	//몸판정팍스초기화
	bodyRect = Sprite::create("blackBox.png");

	//서있는모션
	motions.insert(m_hashMap::value_type(MKEY_STAND, new Motion("eman/eman_stand.csb")));
	//앉아있는모션
	motions.insert(m_hashMap::value_type(MKEY_WALK_FRONT, new Motion("eman/eman_walk_front.csb")));

	//모션 초기화
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
	//상태변경
	c_state = CharacterState::neutral;
	//모션적용
	doMotion(MKEY_STAND);
}

void Character::walkLeft(){
	//오른쪽을 보고있다면 후진
	if (is1PDir){
		//상태가 걷기상태가 아니면 모션을 취함
		if (c_state != CharacterState::moveBack){
			doMotion(MKEY_WALK_FRONT);
			c_state = CharacterState::moveBack;
		}
		//속도만큼 위치이동
		bodyRect->setPositionX(bodyRect->getPositionX() - walkSpeed);
	}
	//왼쪽을 보고있다면 전진
	else{
		//상태가 걷기상태가 아니면 모션을 취함
		if (c_state != CharacterState::moveFront){
			doMotion(MKEY_WALK_FRONT);
			c_state = CharacterState::moveFront;
		}
		//속도만큼 위치이동
		bodyRect->setPositionX(bodyRect->getPositionX() + walkSpeed);
	}
}

void Character::walkRight(){
	//오른쪽을 보고있다면 전진
	if (is1PDir){
		//상태가 걷기상태가 아니면 모션을 취함
		if (c_state != CharacterState::moveFront){
			doMotion(MKEY_WALK_FRONT);
			c_state = CharacterState::moveFront;
		}
		//속도만큼 위치이동
		bodyRect->setPositionX(bodyRect->getPositionX() + walkSpeed);
	}
	//왼쪽을 보고있다면 후진
	else{
		//상태가 걷기상태가 아니면 모션을 취함
		if (c_state != CharacterState::moveBack){
			doMotion(MKEY_WALK_FRONT);
			c_state = CharacterState::moveBack;
		}
		//속도만큼 위치이동
		bodyRect->setPositionX(bodyRect->getPositionX() - walkSpeed);
	}
}