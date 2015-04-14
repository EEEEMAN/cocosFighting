#include "Motion.h"

USING_NS_CC;

Motion::Motion(char* fileName, Character* parent, bool loop, int hitDelay, int hitDmg, float hitBack)
	: motionKey(fileName), character(parent), isLoop(loop), delay(0), currentDelay(0)
{
	m_node = CSLoader::createNode(fileName);
	m_node->setName(NAME_M_NODE);
	m_node->retain();
	m_animation = CSLoader::createTimeline(fileName);
	m_animation->setTag(TAG_M_ANIMATION);
	m_animation->retain();

	//������尡 �ƴϸ� �����ڽ� �����
	if (DEBUG_MODE == 0){
		auto childs = m_node->getChildren();
		for (int i = 0; i < childs.size(); i++){
			if (childs.at(i)->getName().find("Box") != std::string::npos){
				childs.at(i)->setVisible(false);
			}
		}
	}

	//�����ڽ� �ʱ�ȭ
	auto childs = m_node->getChildren();
	for (int i = 0; i < childs.size(); i++){
		if (childs.at(i)->getName().find("Box") != std::string::npos){
			if (childs.at(i)->getTag() == TAG_BLUEBOX){
				auto blueBox = new RectBox(dynamic_cast<Sprite*>(childs.at(i)), parent);
				blueBoxs.push_back(blueBox);
			}
			else if (childs.at(i)->getTag() == TAG_REDBOX){
				auto redBox = new RectBox(dynamic_cast<Sprite*>(childs.at(i)), parent, hitDelay, hitDmg);
				redBoxs.push_back(redBox);
			}
		}
	}

	//�ݺ��Ǵ� ����� �ƴϸ� �������� ��Ʈ�� ����� ���ư�
	if (!loop) m_animation->setLastFrameCallFunc(CC_CALLBACK_0(Motion::lastFrameFunc, this));
}

void Motion::playMotion(Node* m_parent, bool is1PDir){
	playMotion(m_parent, is1PDir, 0);
}

void Motion::playMotion(Node* m_parent, bool is1PDir, int p_delay){
	//���� �������� ��� ���
	stopMotion(m_parent);

	//���⿡ �°� ����
	if (is1PDir) m_node->setScaleX(1);
	if (!is1PDir) m_node->setScaleX(-1);

	//���ο� ��� ����
	if (m_node && m_parent){
		m_node->setPosition(Vec2(m_parent->getContentSize().width / 2, 0));
		m_parent->addChild(m_node);
		if (p_delay == 0){
			m_animation->gotoFrameAndPlay(0, isLoop);
		}
		else{
			delay = p_delay;
			currentDelay = 0;
			m_animation->gotoFrameAndPause(0);
		}
		m_node->runAction(m_animation);
	}
}

void Motion::stopMotion(Node* m_parent){
	auto child = m_parent->getChildByName(NAME_M_NODE);
	if (child){
		m_parent->removeChild(child);
	}
}

void Motion::update(float dt){
	if (currentDelay >= delay && delay != 0 && !m_animation->isPlaying()){
		m_animation->gotoFrameAndPlay(0, isLoop);
	}
	else{
		currentDelay++;
	}
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