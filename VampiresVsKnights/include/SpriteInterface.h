#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteState.h"

class NodeInterface;

class SpriteInterface 
{
public:

	 SpriteState getState() { return m_spriteState; }
	 virtual sf::Sprite* getSprite() { return m_sprite; };
	 virtual void setNode(NodeInterface* p_NI) { m_node = p_NI; };
	 virtual NodeInterface* getNode() { return m_node; };


	 virtual float getSpeed() { return m_speed; };
	 virtual float getAttack() { return m_attack;  };
	 virtual float getHealth() { return m_health; };

	 virtual bool isDoingDamage() = 0;
	 virtual void doDamage(bool p_bool) = 0;
	 virtual void setHealth(float p_damageTaken) = 0;
	 virtual void setSpritePos(int p_col, int p_row) = 0;

	 virtual void message(const std::string p_message) = 0;	 
	 virtual void update(float p_time) = 0;
protected:

	sf::Sprite* m_sprite;
	sf::Texture m_texture;
	NodeInterface* m_node;
	float m_speed;
	float m_attack;
	float m_health;
	bool m_isDoingDamage;
	
	SpriteState m_spriteState;
	
};