#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteInterface.h"

class NodeInterface;

class StaticSprite : public SpriteInterface 
{
private:

	

public:

	StaticSprite(int p_col, int p_row, sf::Texture p_T, float p_speed, float p_health, float p_damage);
	~StaticSprite();
	void update(float p_time) override;
	void message(const std::string p_message) override;
	sf::Sprite* getSprite() override;
	void setSpritePos(int p_col, int p_row) override;
	void setNode(NodeInterface* p_NI) override;
	NodeInterface* getNode() override;
	//float getSpeed() override;
   // float getAttack() override;
	//float getHealth() override;
	void setHealth(float p_damageTaken) override;
	bool isDoingDamage() override;
	void doDamage(bool p_bool) override;
};