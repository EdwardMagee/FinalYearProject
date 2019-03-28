#include "../include/StaticSprite.h"
#include "../include/NodeInterface.h"
#include <iostream>

StaticSprite::StaticSprite(int p_col, int p_row, sf::Texture p_T, float p_speed, float p_health, float p_damage){

	m_spriteState = SpriteState::WaitingState;
	m_texture = p_T;
	m_sprite = new sf::Sprite;
	m_sprite->setTexture(m_texture);
	m_sprite->setPosition((p_col * 64) + 100, (p_row * 64) + 50);
	m_speed = p_speed;
	m_attack = p_damage;
	m_health = p_health;

}

StaticSprite::~StaticSprite(){
	delete m_sprite;
	m_sprite = nullptr;

	delete m_node;
	m_node = nullptr;
}

void StaticSprite::update(float p_time)
{
	setSpritePos(m_node->getID().x, m_node->getID().y);
}

void StaticSprite::message(const std::string p_message)
{
	if (p_message == "Attack")
	{
		m_spriteState = SpriteState::AttackingState;
	}
	else if (p_message == "Wait")
	{
		m_spriteState = SpriteState::WaitingState;
	}
	else if (p_message == "Escape")
	{
		m_spriteState = SpriteState::FleeingState;
	}
	else if (p_message == "Heal")
	{
		m_spriteState = SpriteState::HealState;
	}

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


void StaticSprite::setHealth(float p_damageTaken)
{
	m_health = m_health - p_damageTaken;
}

bool StaticSprite::isDoingDamage()
{
	return m_isDoingDamage;
}

void StaticSprite::doDamage(bool p_bool)
{
	m_isDoingDamage = p_bool;
}
