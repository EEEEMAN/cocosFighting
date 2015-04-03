#include "Character.h"

USING_NS_CC;
using namespace stdext;

Character::Character(FightScene* scene, bool is1Pcha) : parentScene(scene), is1P(is1Pcha), is1PDir(is1Pcha)
{
	//화면사이즈구하기
	auto winSize = Director::getInstance()->getWinSize();

	//스테이지 초기화
	stage = scene->getStage();

	//몸판정팍스초기화
	bodyRect = Sprite::create("blackBox.png");
	bodyRect->setAnchorPoint(Vec2(0.5f, 0.0f));
	if (DEBUG_MODE == 0){
		bodyRect->setOpacity(0);
	}

	//서있는모션
	motions.insert(m_hashMap::value_type(MKEY_STAND, new Motion("eman/eman_stand.csb", true)));
	//앉아있는모션
	motions.insert(m_hashMap::value_type(MKEY_WALK_FRONT, new Motion("eman/eman_walk_front.csb", true)));
	//전방점프 상승모션
	motions.insert(m_hashMap::value_type(MKEY_JUMP_FRONT_UP, new Motion("eman/eman_jump_front_up.csb", true)));
	//전방점프 하강모션
	motions.insert(m_hashMap::value_type(MKEY_JUMP_FRONT_DOWN, new Motion("eman/eman_jump_front_down.csb", true)));
	//수직점프 상승모션
	motions.insert(m_hashMap::value_type(MKEY_JUMP_UP, new Motion("eman/eman_jump_up.csb", true)));
	//수직점프 하강모션
	motions.insert(m_hashMap::value_type(MKEY_JUMP_DOWN, new Motion("eman/eman_jump_down.csb", true)));

	//모션 초기화
	neutral();
}
void Character::showLog() const{
	CCLOG("%d", bodyRect->getPositionX() < enemyCharacter->bodyRect->getPositionX());
}

void Character::setEnemy(Character* enemy){
	this->enemyCharacter = enemy;
}

void Character::update(float dt){
	//모션 update함수 호출
	//currentMotion->update(dt);

	//상대쪽을 보도록 방향조정
	if (bodyRect->getPositionX() < enemyCharacter->bodyRect->getPositionX()){
		is1PDir = true;
		if (c_state == CharacterState::neutral) neutral();
	}
	else if (bodyRect->getPositionX() > enemyCharacter->bodyRect->getPositionX()){
		is1PDir = false;
		if (c_state == CharacterState::neutral) neutral();
	}

	//점프중 상승에서 하강으로전환되면 애니매이션 변경
	if (!onGround){
		if (vy > 0 && vy - G_GRAVITY <= 0){
			switch (c_state){
			case CharacterState::jump: doMotion(MKEY_JUMP_DOWN); break;
			case CharacterState::jumpFront: doMotion(MKEY_JUMP_FRONT_DOWN); break;
			case CharacterState::jumpBack: doMotion(MKEY_JUMP_FRONT_UP); break;
			}
		}
	}

	//y측 처리
	vy -= G_GRAVITY;
	bodyRect->setPositionY(bodyRect->getPositionY() + vy);
	if (bodyRect->getPositionY() < stage->getMinY()){ //땅에닿았는지체크
		vy = 0;
		vx = 0;
		bodyRect->setPositionY(stage->getMinY());
		onGround = true;
	}
	//x측 처리
	//속도만큼 위치이동
	bodyRect->setPositionX(bodyRect->getPositionX() + vx);
	//화면 끝이면 정지
	if (bodyRect->getPositionX() - (bodyRect->getContentSize().width * 0.5) < stage->getMinX()){//왼쪽끝
		bodyRect->setPositionX(stage->getMinX() + (bodyRect->getContentSize().width * 0.5));
	}
	else if (bodyRect->getPositionX() + (bodyRect->getContentSize().width * 0.5) >= stage->getMaxX()){ //오른쪽끝
		bodyRect->setPositionX(stage->getMaxX() - (bodyRect->getContentSize().width * 0.5));
	}

	//키입력 처리
	auto btnm = ButtonManager::getInstance();
	//1P쪽 게이지바 주인을 조작
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
	//2P쪽 게이지바 주인을 조작
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
	//상태변경
	c_state = CharacterState::neutral;
	//모션적용
	doMotion(MKEY_STAND);
}

void Character::walkLeft(){
	if (!onGround) return;
	//상태가 걷기상태가 아니면 모션을 취함
	if (c_state != CharacterState::moveBack){
		doMotion(MKEY_WALK_FRONT);
		c_state = CharacterState::moveBack;
	}
	//속도만큼 위치이동
	bodyRect->setPositionX(bodyRect->getPositionX() - walkSpeed);
	//화면 끝이면 정지
	if (bodyRect->getPositionX() - (bodyRect->getContentSize().width * 0.5) < stage->getMinX()){//왼쪽끝
		bodyRect->setPositionX(stage->getMinX() + (bodyRect->getContentSize().width * 0.5));
	}
}

void Character::walkRight(){
	if (!onGround) return;
	//상태가 걷기상태가 아니면 모션을 취함
	if (c_state != CharacterState::moveFront){
		doMotion(MKEY_WALK_FRONT);
		c_state = CharacterState::moveFront;
	}
	//속도만큼 위치이동
	bodyRect->setPositionX(bodyRect->getPositionX() + walkSpeed);
	//화면 끝이면 정지
	if (bodyRect->getPositionX() + (bodyRect->getContentSize().width * 0.5) >= stage->getMaxX()){ //오른쪽끝
		bodyRect->setPositionX(stage->getMaxX() - (bodyRect->getContentSize().width * 0.5));
	}

}

void Character::jump(){
	if (!onGround) return;
	//y측 속도를 증가
	vy = jumpPower;
	doMotion(MKEY_JUMP_UP);
	c_state = CharacterState::jump;
	onGround = false;
}

void Character::jumpLeft(){
	if (!onGround) return;
	//속도를 증가
	vy += jumpPower;
	vx -= jumpPowerX;
	//오른쪽을 보고있다면 후방점프
	if (is1PDir){
		doMotion(MKEY_JUMP_FRONT_DOWN);
		c_state = CharacterState::jumpBack;
	}
	//왼쪽을 보고있다면 전방점프
	else{
		doMotion(MKEY_JUMP_FRONT_UP);
		c_state = CharacterState::jumpFront;
	}
	onGround = false;
}

void Character::jumpRight(){
	if (!onGround) return;
	//속도를 증가
	vy += jumpPower;
	vx += jumpPowerX;
	//오른쪽을 보고있다면 전방점프
	if (is1PDir){
		doMotion(MKEY_JUMP_FRONT_UP);
		c_state = CharacterState::jumpFront;
	}
	//왼쪽을 보고있다면 후방점프
	else{
		doMotion(MKEY_JUMP_FRONT_DOWN);
		c_state = CharacterState::jumpBack;
	}
	onGround = false;
}