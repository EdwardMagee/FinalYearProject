#include "..\include\NormalNode.h"
#include "..\include\StaticSprite.h"

NormalNode::NormalNode(int p_cost)
{
	m_movementCost = p_cost;

}

NormalNode::~NormalNode()
{
	delete m_sprite;
	m_sprite = nullptr;

	delete m_perant;
	m_perant = nullptr;
}

void NormalNode::updateNode(float p_time)
{
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

std::string NormalNode::checkNodeType()
{
	return "NormalNode";
}
