#include "Motion.h"

USING_NS_CC;

Motion::Motion(char* fileName, bool loop = true)
{
	m_node = CSLoader::createNode(fileName);
	m_animation = CSLoader::createTimeline(fileName);

	//������尡 �ƴϸ� �����ڽ� �����
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
	m_animation->gotoFrameAndPlay(0, loop);
}

void Motion::playMotion(Node* m_parent, bool is1PDir){
	//���� �������� ��� ���
	auto child = m_parent->getChildByName(NAME_M_NODE);
	if (child){
		m_parent->removeChild(child);
	}

	//���⿡ �°� ����
	if (is1PDir) m_node->setScaleX(1);
	if (!is1PDir) m_node->setScaleX(-1);

	//���ο� ��� ����
	if (m_node && m_parent){
		m_node->setPosition(Vec2(m_parent->getContentSize().width / 2, 0));
		m_parent->addChild(m_node);
		m_node->runAction(m_animation);
	}
}

void Motion::update(float dt){
}