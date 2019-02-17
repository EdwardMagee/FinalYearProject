#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteInterface.h"

class StaticSprite : public SpriteInterface 
{
private:

	sf::Sprite* m_sprite;
	sf::Texture m_texture;

public:

	StaticSprite(int p_col, int p_row, sf::Texture p_T);
	~StaticSprite();
	void update(float p_time) override;
	void message(const std::string p_message) override;
	sf::Sprite* getSprite() override;
	void setSpritePos(int p_col, int p_row) override;
};