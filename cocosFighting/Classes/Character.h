#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#define BODY_RECT_WIDTH 100

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "DefineData.h"
#include <hash_map>

#define MKEY_STAND "motionKey_stand"
#define MKEY_WALK_FRONT "motionKey_walk_front"
#define MKEY_JUMP_FRONT_UP "motionKey_jump_front_up"
#define MKEY_JUMP_FRONT_DOWN "motionKey_jump_front_down"
#define MKEY_JUMP_UP "motionKey_jump_up"
#define MKEY_JUMP_DOWN "motionKey_jump_down"
#define MKEY_CROUCH "motionKey_crouch"
#define MKEY_PUNCH "motionKey_punch"
#define MKEY_DAMAGE_HIGH "motionKey_damage_high"

class FightScene;
class Motion;

enum CharacterState{
	neutral = 0,
	moveFront = 1,
	moveBack = 2,
	jump = 3,
	jumpFront = 4,
	jumpBack = 5,
	crouch = 6,
	attack = 7,
	damage = 8
};

typedef stdext::hash_map<char*, Motion*> m_hashMap;

class Character
{
private:
	char name[16]; //ĳ���� �̸�
	unsigned int maxHp = 100; //�ִ�ü��
	unsigned int hp; //ü��
	cocos2d::Sprite* bodyRect; //�������ڽ�
	m_hashMap motions; //��ǵ��� �����ϰ� ����
	CharacterState c_state;
	Stage* stage; //�������� ����
	FightScene* parentScene; //�θ� ��
	Character* enemyCharacter; //��ĳ����
	bool onGround = true;//���� ��������� true
	Motion* currentMotion; //���� �������� ���

	int walkSpeed = 4; //�̵��ӵ�
	int jumpPower = 25;
	int jumpPowerX = 4; //����,�Ĺ������� �������� x�� �̵��ӵ�
public:
	const bool is1P; //1P���̸� true
	bool is1PDir; //�������� ���� �ִٸ� true
	int vx = 0; //x�� �ӵ�. ����� ������, ������ ����
	int vy = 0; //y�� �ӵ�. ����� ��, ������ �Ʒ�
private:
	void doMotion(char* motionKey); //���Ű�� �ش��ϴ� ��� ����
	void doMotion(char* motionKey, int delay); //���Ű�� �ش��ϴ� ����� delay��ŭ ������ ����
	void checkCharacterPos(); //ĳ���Ͱ� ȭ������� ������ �ʵ��� üũ
	void checkDirection(); //ĳ������ ������ ����
	void checkButton(const unsigned char btnData); //������ ��ư ó��
	void setJumpAndMovable(Motion* motion) const; //motion�� ����,�̵������ϰ� ����
public:
	Character(FightScene* scene, bool is1P);
	inline void setEnemy(Character* enemy){ this->enemyCharacter = enemy; };
	inline cocos2d::Sprite* getBodyRect() const{ return bodyRect; }
	inline CharacterState getState() const { return c_state; }
	inline bool is1Player() const { return is1P; }
	inline Motion* getCurrentMotion() const { return currentMotion; };
	void update(float d);
	void showLog() const;
	bool isHitEnemyAttack(); //������ �¾Ҵ��� üũ
	//���
	void neutral();
	void walkLeft();
	void walkRight();
	void jump();
	void jumpLeft();
	void jumpRight();
	void crouch();
	void punch();
	void damage(int delay, int damage);
};

#endif