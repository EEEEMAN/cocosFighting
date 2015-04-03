#ifndef __MOTION_H__
#define __MOTION_H__

#define NAME_M_NODE "m_node"
#define TAG_M_ANIMATION 1000

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "DefineData.h"

class Motion
{
private:
	cocos2d::Node* m_node;
	cocostudio::timeline::ActionTimeline* m_animation;
public:
	Motion(char* fileName, bool loop);
	void playMotion(cocos2d::Node* m_parent, bool is1PDir);
	void update(float dt);
};

#endif