#include "Motion.h"

USING_NS_CC;

Motion::Motion(char* fileName, Character* parent, bool loop) : motionKey(fileName), character(parent), isLoop(loop)
{
	m_node = CSLoader::createNode(fileName);
	m_animation = CSLoader::createTimeline(fileName);

	//디버깅모드가 아니면 판정박스 지우기
	if (DEBUG_MODE == 0){
		auto childs = m_node->getChildren();
		for (int i = 0; i < childs.size(); i++){
			if (childs.at(i)->getName().find("Box") != std::string::npos){
				childs.at(i)->setVisible(false);
			}
		}
	}

	m_node->setName(NAME_M_NODE);
	m_node->retain();
	m_animation->setTag(TAG_M_ANIMATION);
	m_animation->retain();

	//반복되는 모션이 아니면 마지막에 뉴트럴 포즈로 돌아감
	if (!loop) m_animation->setLastFrameCallFunc(CC_CALLBACK_0(Motion::lastFrameFunc, this));
}

void Motion::playMotion(Node* m_parent, bool is1PDir){
	//현제 진행중인 모션 취소
	auto child = m_parent->getChildByName(NAME_M_NODE);
	if (child){
		m_parent->removeChild(child);
	}

	//방향에 맞게 반전
	if (is1PDir) m_node->setScaleX(1);
	if (!is1PDir) m_node->setScaleX(-1);

	//새로운 모션 시작
	if (m_node && m_parent){
		m_node->setPosition(Vec2(m_parent->getContentSize().width / 2, 0));
		m_parent->addChild(m_node);
		m_animation->gotoFrameAndPlay(0, isLoop);
		m_node->runAction(m_animation);
	}
}

void Motion::update(float dt){
}

void Motion::lastFrameFunc(){
	character->neutral();
}

void Motion::addCancelMotion(std::string motionKey){
	cancelableList.push_back(motionKey);
}

bool Motion::isCancelable(std::string motionKey) const{
	for (int i = 0; i < cancelableList.size(); i++){
		if (cancelableList.at(i).compare(motionKey) == 0){
			return true;
		}
	}
	return false;
}