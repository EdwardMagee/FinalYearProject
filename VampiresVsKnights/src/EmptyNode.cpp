#include "..\include\EmptyNode.h"
#include "..\include\StaticSprite.h"

EmptyNode::EmptyNode(int p_cost)
{
	m_movementCost = p_cost;
}

EmptyNode::~EmptyNode()
{
	delete m_sprite;
	m_sprite = nullptr;

	delete m_perant;
	m_perant = nullptr;
}

void EmptyNode::updateNode(float p_time)
{
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

std::string EmptyNode::checkNodeType()
{
	return "EmptyNode";
}
