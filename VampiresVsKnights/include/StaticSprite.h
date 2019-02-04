#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteInterface.h"

class StaticSprite : public SpriteInterface 
{
private:

	sf::Sprite* m_sprite;

public:

	StaticSprite(sf::Sprite* p_Sprite);
	~StaticSprite();
	void update(float p_time) override;
	void message(const std::string p_message) override;
	sf::Sprite* getSprite() override;
};