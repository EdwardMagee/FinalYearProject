#include "..\include\NormalNode.h"
#include "..\include\StaticSprite.h"

NormalNode::NormalNode(int p_cost)
{
	m_movementCost = p_cost;
	//m_spriteUnit = nullptr;
	//m_
}

NormalNode::~NormalNode()
{
	delete m_sprite;
	m_sprite = nullptr;
}

void NormalNode::updateNode(float p_time)
{
	//if (m_spriteUnit != nullptr) {
	//	m_spriteUnit->setSpritePos(m_id.x, m_id.y);
	//}
}

sf::Sprite * NormalNode::getSprite()
{
	return m_sprite;
}

void NormalNode::constructNode(int p_x, int p_y, sf::Texture p_T)
{
	m_id.x = p_x;
	m_id.y = p_y;

	m_texture = p_T;
	m_sprite = new sf::Sprite;
	m_sprite->setTexture(m_texture);
	m_sprite->setPosition(p_x* 64 + 100, p_y * 64 + 50);
}

//SpriteInterface * NormalNode::getSpriteAttachedToNode()
//{
//	return m_spriteUnit;
//}

/*bool NormalNode::containSprite(SpriteInterface* p_sprite)
{
	if (m_spriteUnit != nullptr){
		return false;
	}
	else {
       m_spriteUnit = p_sprite;
	   return true;
	}

}*/

//void NormalNode::removeSprite()
//{
//	m_spriteUnit = nullptr;
//}

//float NormalNode::getG()
//{
//	return m_gValue;
//}

//float NormalNode::getH()
//{
//	return m_hValue;
//}

//float NormalNode::getF()
//{
//	return m_fValue;
//}

//float NormalNode::getTerrainCost()
//{
//	return m_movementCost;
//}

//sf::Vector2i NormalNode::getID()
//{
//	return m_id;
//}

//void NormalNode::setG(float p_g)
//{
//	m_gValue = p_g;
//}

//void NormalNode::setF(float p_f)
//{
//	m_fValue = p_f;
//}

//void NormalNode::setH(float p_H)
//{
//	m_hValue = p_H;
//}

//void NormalNode::setDiagonal(bool p_b)
//{
//	m_isDiagonal = p_b;
//}

//NodeInterface * NormalNode::getPerant()
//{
//	return m_perant;
//}

//void NormalNode::setPerant(NodeInterface * p_NI)
//{
//	m_perant = p_NI;
//}

std::string NormalNode::checkNodeType()
{
	return "NormalNode";
}

//bool NormalNode::isDiagonal()
//{
//	return m_isDiagonal;
//}
