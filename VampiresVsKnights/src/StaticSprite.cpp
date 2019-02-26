#include "../include/StaticSprite.h"
#include "../include/NodeInterface.h"
#include <iostream>

StaticSprite::StaticSprite(int p_col, int p_row, sf::Texture p_T, float p_speed){

	m_texture = p_T;
	m_sprite = new sf::Sprite;
	m_sprite->setTexture(m_texture);
	m_sprite->setPosition((p_col * 64) + 100, (p_row * 64) + 50);
	m_speed = p_speed;

}

StaticSprite::~StaticSprite(){
	delete m_sprite;
	m_sprite = nullptr;
}

void StaticSprite::update(float p_time)
{
	//std::cout << m_sprite->getPosition().x << std::endl;
	setSpritePos(m_node->getID().x, m_node->getID().y);

}

void StaticSprite::message(const std::string p_message)
{
}

sf::Sprite* StaticSprite::getSprite(){
	return m_sprite;
}

void StaticSprite::setSpritePos(int p_col, int p_row)
{
	m_sprite->setPosition((p_col * 64) + 100, (p_row * 64) + 50);
}

void StaticSprite::setNode(NodeInterface * p_NI)
{
	m_node = p_NI;
}

NodeInterface * StaticSprite::getNode()
{
	return m_node;
}

float StaticSprite::getSpeed()
{
	return m_speed;
}
