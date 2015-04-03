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

class FightScene;
class Motion;

enum CharacterState{
	neutral = 0,
	moveFront = 1,
	moveBack = 2,
	jump = 3,
	jumpFront = 4,
	jumpBack = 5
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
public:
	Character(FightScene* scene, bool is1P);
	void setEnemy(Character* enemy);
	inline cocos2d::Sprite* getBodyRect() const{ return bodyRect; }
	inline CharacterState getState() const { return c_state; }
	inline bool is1Player() const { return is1P; }
	void update(float d);
	void showLog() const;
	//���
	void neutral();
	void walkLeft();
	void walkRight();
	void jump();
	void jumpLeft();
	void jumpRight();
};

#endif