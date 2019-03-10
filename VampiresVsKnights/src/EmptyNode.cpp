#include "..\include\EmptyNode.h"
#include "..\include\StaticSprite.h"

EmptyNode::EmptyNode(int p_cost)
{
	m_movementCost = p_cost;
	m_spriteUnit = nullptr;
}

EmptyNode::~EmptyNode()
{
	delete m_sprite;
	m_sprite = nullptr;
}

void EmptyNode::updateNode(float p_time)
{
	if (m_spriteUnit != nullptr)
		m_spriteUnit->setSpritePos(m_id.x, m_id.y);
}

sf::Sprite * EmptyNode::getSprite()
{
	return m_sprite;
}

void EmptyNode::constructNode(int p_x, int p_y, sf::Texture p_T)
{
	m_id.x = p_x;
	m_id.y = p_y;

	m_texture = p_T;
	m_sprite = new sf::Sprite;
	m_sprite->setTexture(m_texture);
	m_sprite->setPosition(p_x * 64 + 100, p_y * 64 + 50);
}

SpriteInterface * EmptyNode::getSpriteAttachedToNode()
{
	return m_spriteUnit;
}

bool EmptyNode::containSprite(SpriteInterface* p_sprite)
{
	if (m_spriteUnit != nullptr) {
		return false;
	}
	else {
		m_spriteUnit = p_sprite;
		return true;
	}

}

void EmptyNode::removeSprite()
{
	m_spriteUnit = nullptr;
}

//float EmptyNode::getG()
//{
//	return m_gValue;
//}

//float EmptyNode::getH()
//{
//	return m_hValue;
//}

//float EmptyNode::getF()
//{
//	return m_fValue;
//}

//float EmptyNode::getTerrainCost()
//{
//	return m_movementCost;
//}

//sf::Vector2i EmptyNode::getID()
//{
//	return m_id;
//}

//void EmptyNode::setG(float p_g)
//{
//	m_gValue = p_g;
//}

//void EmptyNode::setF(float p_f)
//{
//	m_fValue = p_f;
//}

//void EmptyNode::setH(float p_H)
//{
//	m_hValue = p_H;
//}

//void EmptyNode::setDiagonal(bool p_b)
//{
//	m_isDiagonal = p_b;
//}

//NodeInterface * EmptyNode::getPerant()
//{
//	return m_perant;
//}

//void EmptyNode::setPerant(NodeInterface * p_NI)
//{
//	 m_perant = p_NI;
//}

std::string EmptyNode::checkNodeType()
{
	return "EmptyNode";
}

//bool EmptyNode::isDiagonal()
//{
//	return m_isDiagonal;
//}
