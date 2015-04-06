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
	motions.insert(m_hashMap::value_type(MKEY_STAND, new Motion("eman/eman_stand.csb", this, true)));
	//�ȴ¸��
	auto m_walk = new Motion("eman/eman_walk_front.csb", this, true);
	setJumpAndMovable(m_walk);
	m_walk->addCancelMotion(MKEY_PUNCH);
	motions.insert(m_hashMap::value_type(MKEY_WALK_FRONT, m_walk));
	//�������� ��¸��
	motions.insert(m_hashMap::value_type(MKEY_JUMP_FRONT_UP, new Motion("eman/eman_jump_front_up.csb", this, true)));
	//�������� �ϰ����
	motions.insert(m_hashMap::value_type(MKEY_JUMP_FRONT_DOWN, new Motion("eman/eman_jump_front_down.csb", this, true)));
	//�������� ��¸��
	motions.insert(m_hashMap::value_type(MKEY_JUMP_UP, new Motion("eman/eman_jump_up.csb", this, true)));
	//�������� �ϰ����
	motions.insert(m_hashMap::value_type(MKEY_JUMP_DOWN, new Motion("eman/eman_jump_down.csb", this, true)));
	//��ġ���
	motions.insert(m_hashMap::value_type(MKEY_PUNCH, new Motion("eman/eman_punch.csb", this, false)));

	//��� �ʱ�ȭ
	neutral();
}
void Character::showLog() const{
	CCLOG("x:%f, y:%f, cx:%f, cy:%f", bodyRect->getPositionX(), bodyRect->getPositionY(), bodyRect->convertToWorldSpace(bodyRect->getPosition()).x, bodyRect->convertToWorldSpace(bodyRect->getPosition()).y);
	CCLOG("bx:%f, by:%f", bodyRect->getParent()->convertToWorldSpace(bodyRect->getPosition()).x, bodyRect->getParent()->convertToWorldSpace(bodyRect->getPosition()).y);
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
	if (bodyRect->getPositionY() < stage->getGroundPos()){ //������Ҵ���üũ
		vy = 0;
		vx = 0;
		bodyRect->setPositionY(stage->getGroundPos());
		onGround = true;
	}
	//x�� ó��
	//�ӵ���ŭ ��ġ�̵�
	bodyRect->setPositionX(bodyRect->getPositionX() + vx);
	//ȭ�� ���̸� ����
	checkCharacterPos();

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
			if (onGround && c_state != CharacterState::attack)
				neutral();
		}
	}
	//2P�� �������� ������ ����
	else{
	}
}

void Character::checkCharacterPos(){
	auto winSize = Director::getInstance()->getWinSize();
	auto worldPos = bodyRect->getParent()->convertToWorldSpace(bodyRect->getPosition());
	//���ʳ�
	if (worldPos.x - (bodyRect->getContentSize().width * 0.5) < 0){
		worldPos.x = (bodyRect->getContentSize().width * 0.5);
		bodyRect->setPosition(bodyRect->getParent()->convertToNodeSpace(worldPos));
	}
	//�����ʳ�
	else if (worldPos.x + (bodyRect->getContentSize().width * 0.5) > winSize.width){
		worldPos.x = winSize.width - (bodyRect->getContentSize().width * 0.5);
		bodyRect->setPosition(bodyRect->getParent()->convertToNodeSpace(worldPos));
	}
}

void Character::doMotion(char* motionKey){
	auto it = motions.find(motionKey);
	if (it != motions.end()){
		it->second->playMotion(bodyRect, is1PDir);
		currentMotion = it->second;
	}
}

void Character::setJumpAndMovable(Motion* motion) const{
	motion->addCancelMotion(MKEY_JUMP_FRONT_UP);
	motion->addCancelMotion(MKEY_JUMP_UP);
	motion->addCancelMotion(MKEY_WALK_FRONT);
}

void Character::neutral(){
	if (c_state != CharacterState::neutral){
		//���º���
		c_state = CharacterState::neutral;
		//�������
		doMotion(MKEY_STAND);
	}
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
	checkCharacterPos();
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
	checkCharacterPos();

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

void Character::punch(){
	if (onGround && c_state != CharacterState::attack){
		c_state = CharacterState::attack;
		doMotion(MKEY_PUNCH);
	}
}