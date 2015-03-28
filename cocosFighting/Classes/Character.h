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
	char name[16]; //캐릭터 이름
	unsigned int maxHp = 100; //최대체력
	unsigned int hp; //체력
	cocos2d::Sprite* bodyRect; //몸판정박스
	m_hashMap motions; //모션들을 저장하고 관리
	int walkSpeed; //이동속도
	CharacterState c_state;
	bool is1P; //1P쪽이면 true
public:
	bool is1PDir; //오른쪽을 보고 있다면 true
private:
	void doMotion(char* motionKey); //모션키에 해당하는 모션 실행
public:
	Character();
	//void commandHandle(); //커맨드입력을 처리
	inline cocos2d::Sprite* getBodyRect() const{ return bodyRect; }
	inline CharacterState getState() const { return c_state; }
	inline bool is1Player() const { return is1P; }
	void update(float d);
	//모션
	void neutral();
	void walkLeft();
	void walkRight();
};

#endif