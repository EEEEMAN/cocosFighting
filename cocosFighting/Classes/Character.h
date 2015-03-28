#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#define BODY_RECT_WIDTH 100

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "Motion.h"
#include "ButtonManager.h"
#include <hash_map>

#define MKEY_STAND "motionKey_stand"
#define MKEY_WALK_FRONT "motionKey_walk_front"

enum CharacterState{
	neutral = 0,
	moveFront = 1,
	moveBack = 2
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
	int walkSpeed; //�̵��ӵ�
	CharacterState c_state;
	bool is1P; //1P���̸� true
public:
	bool is1PDir; //�������� ���� �ִٸ� true
private:
	void doMotion(char* motionKey); //���Ű�� �ش��ϴ� ��� ����
public:
	Character();
	//void commandHandle(); //Ŀ�ǵ��Է��� ó��
	inline cocos2d::Sprite* getBodyRect() const{ return bodyRect; }
	inline CharacterState getState() const { return c_state; }
	inline bool is1Player() const { return is1P; }
	void update(float d);
	//���
	void neutral();
	void walkLeft();
	void walkRight();
};

#endif