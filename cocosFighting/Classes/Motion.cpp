#include "Motion.h"

USING_NS_CC;

Motion::Motion(char* fileName)
{
	m_node = CSLoader::createNode(fileName);
	m_animation = CSLoader::createTimeline(fileName);

	m_node->setName(NAME_M_NODE);
	m_node->retain();
	m_animation->setTag(TAG_M_ANIMATION);
	m_animation->retain();
	m_animation->gotoFrameAndPlay(0, true);
}

Motion::Motion(char* fileName, bool loop)
{
	m_node = CSLoader::createNode(fileName);
	m_animation = CSLoader::createTimeline(fileName);

	m_node->setName(NAME_M_NODE);
	m_animation->setTag(TAG_M_ANIMATION);
	m_animation->gotoFrameAndPlay(0, loop);
}

void Motion::playMotion(Node* m_parent, bool is1PDir){
	//���� �������� ��� ���
	auto child = m_parent->getChildByName(NAME_M_NODE);
	if (child){
		//child->stopActionByTag(TAG_M_ANIMATION);
		m_parent->removeChild(child);
	}

	//���⿡ �°� ����
	if (!is1PDir) m_node->setScaleX(-1);

	//���ο� ��� ����
	if (m_node && m_parent){
		CCLOG("%s", m_node->getName());
		m_node->setPosition(Vec2(m_parent->getContentSize().width / 2, m_parent->getContentSize().height / 2));
		m_parent->addChild(m_node);
		m_node->runAction(m_animation);
	}
}