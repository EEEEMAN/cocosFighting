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
	char name[16]; //캐릭터 이름
	unsigned int maxHp = 100; //최대체력
	unsigned int hp; //체력
	cocos2d::Sprite* bodyRect; //몸판정박스
	m_hashMap motions; //모션들을 저장하고 관리
	CharacterState c_state;
	Stage* stage; //스테이지 정보
	FightScene* parentScene; //부모 씬
	Character* enemyCharacter; //적캐릭터
	bool onGround = true;//땅에 닿아있으면 true
	Motion* currentMotion; //현제 진행중인 모션

	int walkSpeed = 4; //이동속도
	int jumpPower = 25;
	int jumpPowerX = 4; //전방,후방점프를 했을때의 x측 이동속도
public:
	const bool is1P; //1P쪽이면 true
	bool is1PDir; //오른쪽을 보고 있다면 true
	int vx = 0; //x측 속도. 양수가 오른쪽, 음수가 왼쪽
	int vy = 0; //y측 속도. 양수가 위, 음수가 아래
private:
	void doMotion(char* motionKey); //모션키에 해당하는 모션 실행
	void doMotion(char* motionKey, int delay); //모션키에 해당하는 모션을 delay민큼 지연후 실행
	void checkCharacterPos(); //캐릭터가 화면밖으로 나가지 않도록 체크
	void checkDirection(); //캐릭터의 방향을 조정
	void checkButton(const unsigned char btnData); //눌러진 버튼 처리
	void setJumpAndMovable(Motion* motion) const; //motion을 점프,이동가능하게 변경
public:
	Character(FightScene* scene, bool is1P);
	inline void setEnemy(Character* enemy){ this->enemyCharacter = enemy; };
	inline cocos2d::Sprite* getBodyRect() const{ return bodyRect; }
	inline CharacterState getState() const { return c_state; }
	inline bool is1Player() const { return is1P; }
	inline Motion* getCurrentMotion() const { return currentMotion; };
	void update(float d);
	void showLog() const;
	bool isHitEnemyAttack(); //공격을 맞았는지 체크
	//모션
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