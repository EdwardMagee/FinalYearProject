#include "..\include\NormalNode.h"
#include "..\include\StaticSprite.h"

NormalNode::NormalNode(int p_cost)
{
	m_movementCost = p_cost;
	m_spriteUnit = nullptr;
}

NormalNode::~NormalNode()
{
	delete m_sprite;
	m_sprite = nullptr;
}

void NormalNode::updateNode(float p_time)
{
	if(m_spriteUnit != nullptr)
	m_spriteUnit->setSpritePos(id.x, id.y);
}

sf::Sprite * NormalNode::getSprite()
{
	return m_sprite;
}

void NormalNode::constructNode(int p_col, int p_row, sf::Texture p_T)
{
	id.x = p_col;
	id.y = p_row;

	m_texture = p_T;
	m_sprite = new sf::Sprite;
	m_sprite->setTexture(m_texture);
	m_sprite->setPosition(p_col* 64 + 100, p_row * 64 + 50);
}

SpriteInterface * NormalNode::getSpriteAttachedToNode()
{
	return m_spriteUnit;
}

bool NormalNode::containSprite(SpriteInterface* p_sprite)
{
	if (m_spriteUnit != nullptr){
		return false;
	}
	else {
       m_spriteUnit = p_sprite;
	   return true;
	}

}

void NormalNode::removeSprite()
{
	m_spriteUnit = nullptr;
}

float NormalNode::getG()
{
	return 0.0f;
}

float NormalNode::getH()
{
	return 0.0f;
}

float NormalNode::getF()
{
	return 0.0f;
}

sf::Vector2i NormalNode::getID()
{
	return sf::Vector2i();
}

void NormalNode::setG(float p_g)
{
}

void NormalNode::setF(float p_f)
{
}

void NormalNode::setH(float p_H)
{
}
