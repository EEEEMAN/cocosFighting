#ifndef __MOTION_H__
#define __MOTION_H__

#define NAME_M_NODE "m_node"
#define TAG_M_ANIMATION 1000

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "DefineData.h"
#include <vector>

class Motion
{
private:
	cocos2d::Node* m_node;
	cocostudio::timeline::ActionTimeline* m_animation;
	Character* character;
	const std::string motionKey;
	std::vector<std::string> cancelableList;
	bool isLoop;
public:
	Motion(char* fileName, Character* parent, bool loop);
	void playMotion(cocos2d::Node* m_parent, bool is1PDir);
	void lastFrameFunc();
	void addCancelMotion(std::string motionKey);
	bool isCancelable(std::string motionKey) const;
	void update(float dt);
	inline const std::string getMotionKey() const { return motionKey; };
};

#endif