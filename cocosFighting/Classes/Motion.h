#ifndef __MOTION_H__
#define __MOTION_H__

#define NAME_M_NODE "m_node"
#define TAG_M_ANIMATION 1000

#define TAG_BLUEBOX 1000
#define TAG_REDBOX 2000

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "DefineData.h"
#include <vector>

class RectBox;

class Motion
{
private:
	cocos2d::Node* m_node;
	cocostudio::timeline::ActionTimeline* m_animation;
	Character* character;
	const std::string motionKey;
	std::vector<std::string> cancelableList;
	bool isLoop = true;;
	std::vector<RectBox*> blueBoxs;
	std::vector<RectBox*> redBoxs;
	int delay; //일정 딜레이 후에 애니메이션을 시작하도록 함. 0이면 딜레이가 없음
	int currentDelay; //현재 경과한 시간
public:
	Motion(char* fileName, Character* parent, bool loop, int delay, int damage, float hitBack);
	void playMotion(cocos2d::Node* m_parent, bool is1PDir);
	void playMotion(cocos2d::Node* m_parent, bool is1PDir, int p_delay);
	void stopMotion(cocos2d::Node* m_parent);
	void lastFrameFunc();
	void addCancelMotion(std::string motionKey);
	bool isCancelable(std::string motionKey) const;
	void update(float dt); //일정 딜레이 후에 애니메이션을 시작하도록 함
	inline const std::string getMotionKey() const { return motionKey; };
	inline std::vector<RectBox*>* getBlueBoxs() { return &blueBoxs; };
	inline std::vector<RectBox*>* getRedBoxs() { return &redBoxs; };
};

#endif