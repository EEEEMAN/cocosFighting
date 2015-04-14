#include "Character.h"

USING_NS_CC;
using namespace stdext;

Character::Character(FightScene* scene, bool is1Pcha) : parentScene(scene), is1P(is1Pcha), is1PDir(is1Pcha), stage(scene->getStage())
{
	//ȭ�������ϱ�
	auto winSize = Director::getInstance()->getWinSize();

	//�������Ž��ʱ�ȭ
	bodyRect = Sprite::create("blackBox.png");
	bodyRect->setAnchorPoint(Vec2(0.5f, 0.0f));
	if (DEBUG_MODE == 0){
		bodyRect->setOpacity(0);
	}

	//���ִ¸��
	auto m_stand = new Motion("eman/eman_stand.csb", this, true, 0, 0, 0);
	setJumpAndMovable(m_stand);
	m_stand->addCancelMotion(MKEY_PUNCH);
	m_stand->addCancelMotion(MKEY_DAMAGE_HIGH);
	motions.insert(m_hashMap::value_type(MKEY_STAND, m_stand));
	//�ȴ¸��
	auto m_walk = new Motion("eman/eman_walk_front.csb", this, true, 0, 0, 0);
	setJumpAndMovable(m_walk);
	m_walk->addCancelMotion(MKEY_PUNCH);
	m_walk->addCancelMotion(MKEY_DAMAGE_HIGH);
	motions.insert(m_hashMap::value_type(MKEY_WALK_FRONT, m_walk));
	//�������� ��¸��
	auto m_jumpFrontUp = new Motion("eman/eman_jump_front_up.csb", this, true, 0, 0, 0);
	m_jumpFrontUp->addCancelMotion(MKEY_STAND);
	m_jumpFrontUp->addCancelMotion(MKEY_DAMAGE_HIGH);
	motions.insert(m_hashMap::value_type(MKEY_JUMP_FRONT_UP, m_jumpFrontUp));
	//�������� �ϰ����
	auto m_jumpFrontDown = new Motion("eman/eman_jump_front_down.csb", this, true, 0, 0, 0);
	m_jumpFrontDown->addCancelMotion(MKEY_STAND);
	m_jumpFrontDown->addCancelMotion(MKEY_DAMAGE_HIGH);
	motions.insert(m_hashMap::value_type(MKEY_JUMP_FRONT_DOWN, m_jumpFrontDown));
	//�������� ��¸��
	auto m_jumpUp = new Motion("eman/eman_jump_up.csb", this, true, 0, 0, 0);
	m_jumpUp->addCancelMotion(MKEY_DAMAGE_HIGH);
	motions.insert(m_hashMap::value_type(MKEY_JUMP_UP, m_jumpUp));
	//�������� �ϰ����
	auto m_jumpDown = new Motion("eman/eman_jump_down.csb", this, true, 0, 0, 0);
	m_jumpDown->addCancelMotion(MKEY_STAND);
	m_jumpDown->addCancelMotion(MKEY_DAMAGE_HIGH);
	motions.insert(m_hashMap::value_type(MKEY_JUMP_DOWN, m_jumpDown));
	//�ɴ¸��
	auto m_crouch = new Motion("eman/eman_crouch.csb", this, true, 0, 0, 0);
	m_crouch->addCancelMotion(MKEY_STAND);
	m_crouch->addCancelMotion(MKEY_DAMAGE_HIGH);
	motions.insert(m_hashMap::value_type(MKEY_CROUCH, m_crouch));
	//��ġ���
	auto m_punch = new Motion("eman/eman_punch.csb", this, false, 0, 0, 0);
	m_punch->addCancelMotion(MKEY_STAND);
	m_punch->addCancelMotion(MKEY_DAMAGE_HIGH);
	motions.insert(m_hashMap::value_type(MKEY_PUNCH, m_punch));
	//������ ���
	auto m_damage_high = new Motion("eman/eman_damage_high.csb", this, false, 0, 0, 0);
	m_damage_high->addCancelMotion(MKEY_STAND);
	m_damage_high->addCancelMotion(MKEY_DAMAGE_HIGH);
	motions.insert(m_hashMap::value_type(MKEY_DAMAGE_HIGH, m_damage_high));

	//��� �ʱ�ȭ
	c_state = CharacterState::neutral;
	doMotion(MKEY_STAND);
}
void Character::showLog() const{
}

void Character::update(float dt){
	//��� update�Լ� ȣ��
	//if (currentMotion->hasDelay())
	currentMotion->update(dt);

	checkDirection();

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
		if (c_state == CharacterState::jump || c_state == CharacterState::jumpBack || c_state == CharacterState::jumpFront)
			neutral();
	}

	//x�� ó��
	bodyRect->setPositionX(bodyRect->getPositionX() + vx);	//�ӵ���ŭ ��ġ�̵�
	checkCharacterPos();	//ȭ�� ���̸� ����

	//Ű�Է� ó��
	auto btnm = ButtonManager::getInstance();
	if (is1P){	//1P�� �������� ������ ����
		checkButton(btnm->getButtonData1P());
	}
	else{	//2P�� �������� ������ ����
		checkButton(btnm->getButtonData2P());
	}
	isHitEnemyAttack();
}

void Character::checkButton(const unsigned char btnData){
	auto btnm = ButtonManager::getInstance();
	if (btnm->isPressed(btnData, ButtonData::BTN_UP) && btnm->isPressed(btnData, ButtonData::BTN_LEFT)){
		jumpLeft();
	}
	else if (btnm->isPressed(btnData, ButtonData::BTN_UP) && btnm->isPressed(btnData, ButtonData::BTN_RIGHT)){
		jumpRight();
	}
	else if (btnm->isPressed(btnData, ButtonData::BTN_UP)){
		jump();
	}
	else if (btnm->isPressed(btnData, ButtonData::BTN_DOWN)){
		crouch();
	}
	else if (c_state == CharacterState::crouch){
		neutral();
	}
	else if (btnm->isPressed(btnData, ButtonData::BTN_LEFT)){
		walkLeft();
	}
	else if (btnm->isPressed(btnData, ButtonData::BTN_RIGHT)){
		walkRight();
	}
	else if (btnData == 0){
		if (onGround && c_state != CharacterState::attack && c_state != CharacterState::damage)
			neutral();
	}
}

void Character::checkDirection(){
	//������� ������ ��������
	if (bodyRect->getPositionX() < enemyCharacter->bodyRect->getPositionX() && !is1PDir){
		is1PDir = true;
		if (c_state == CharacterState::neutral) doMotion(MKEY_STAND);
	}
	else if (bodyRect->getPositionX() > enemyCharacter->bodyRect->getPositionX() && is1PDir){
		is1PDir = false;
		if (c_state == CharacterState::neutral) doMotion(MKEY_STAND);
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

bool Character::isHitEnemyAttack(){
	auto blueBoxs = currentMotion->getBlueBoxs();
	auto redBoxs = enemyCharacter->getCurrentMotion()->getRedBoxs();
	if (!blueBoxs || !redBoxs) return false;
	if (blueBoxs->size() == 0 || redBoxs->size() == 0) return false;

	for (int bi = 0; bi < blueBoxs->size(); bi++){
		for (int ri = 0; ri < redBoxs->size(); ri++){
			auto blueBox = blueBoxs->at(bi);
			auto redBox = redBoxs->at(ri);
			if (redBox->getSprite()->getOpacity() == 0) continue;
			if (blueBox->getSprite()->getOpacity() == 0) continue;
			if (parentScene->isCollisionWorldSpace(blueBox->getSprite(), redBox->getSprite())){
				damage(redBox->getHitDelay(), redBox->getDamage());
				return true;
			}
		}
	}
	return false;
}

void Character::doMotion(char* motionKey){
	auto it = motions.find(motionKey);
	if (it != motions.end()){
		it->second->playMotion(bodyRect, is1PDir);
		currentMotion = it->second;
	}
}

void Character::doMotion(char* motionKey, int delay){
	auto it = motions.find(motionKey);
	if (it != motions.end()){
		it->second->playMotion(bodyRect, is1PDir, delay);
		currentMotion = it->second;
	}
}

void Character::setJumpAndMovable(Motion* motion) const{
	motion->addCancelMotion(MKEY_STAND);
	motion->addCancelMotion(MKEY_JUMP_FRONT_UP);
	motion->addCancelMotion(MKEY_JUMP_FRONT_DOWN);
	motion->addCancelMotion(MKEY_JUMP_UP);
	motion->addCancelMotion(MKEY_WALK_FRONT);
	motion->addCancelMotion(MKEY_CROUCH);
}

void Character::neutral(){
	if (!onGround) return;
	if (!currentMotion->isCancelable(MKEY_STAND)) return;
	if (c_state != CharacterState::neutral){
		//���º���
		c_state = CharacterState::neutral;
		//�������
		doMotion(MKEY_STAND);
	}
}

void Character::walkLeft(){
	if (!onGround) return;
	if (currentMotion->isCancelable(MKEY_WALK_FRONT)){
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
}

void Character::walkRight(){
	if (!onGround) return;
	if (currentMotion->isCancelable(MKEY_WALK_FRONT)){
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
}

void Character::jump(){
	if (!onGround) return;
	if (currentMotion->isCancelable(MKEY_JUMP_UP)){
		//y�� �ӵ��� ����
		vy = jumpPower;
		doMotion(MKEY_JUMP_UP);
		c_state = CharacterState::jump;
		onGround = false;
	}
}

void Character::jumpLeft(){
	if (!onGround) return;
	if (currentMotion->isCancelable(MKEY_JUMP_FRONT_DOWN) || currentMotion->isCancelable(MKEY_JUMP_FRONT_UP)){
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
}

void Character::jumpRight(){
	if (!onGround) return;
	if (currentMotion->isCancelable(MKEY_JUMP_FRONT_DOWN) || currentMotion->isCancelable(MKEY_JUMP_FRONT_UP)){
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
}

void Character::crouch(){
	if (!onGround) return;
	if (!currentMotion->isCancelable(MKEY_CROUCH)) return;

	c_state = CharacterState::crouch;
	doMotion(MKEY_CROUCH);
}

void Character::punch(){
	if (!onGround) return;
	if (currentMotion->isCancelable(MKEY_PUNCH)){
		c_state = CharacterState::attack;
		doMotion(MKEY_PUNCH);
	}
}

void Character::damage(int delay, int damage){
	if (currentMotion->isCancelable(MKEY_DAMAGE_HIGH)){
		c_state = CharacterState::damage;
		doMotion(MKEY_DAMAGE_HIGH, delay);
	}
}