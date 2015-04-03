#ifndef __STAGE_H__
#define __STAGE_H__

#include "cocos2d.h"
#include "DefineData.h"

class Stage
{
private:
	int stageWidth;
	int stageHeight;
	int minX, maxX;
	int minY, maxY;
	cocos2d::Sprite* backGround = 0;
public:
	Stage();
	~Stage();
	inline int getStageWidth() const { return stageWidth; };
	inline int getStageHeight() const { return stageHeight; };
	inline int getMinX() const { return minX; };
	inline int getMaxX() const { return maxX; };
	inline int getMinY() const { return minY; };
	inline int getMaxY() const { return maxY; };
	inline cocos2d::Sprite* getBackGround() const { return backGround; };
};

#endif