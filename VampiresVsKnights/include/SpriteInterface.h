#pragma once
#include <SFML/Graphics.hpp>

class SpriteInterface 
{
public:
     virtual sf::Sprite* getSprite() = 0;
	 virtual void update(float p_time) = 0;
	 virtual void setSpritePos(int p_col, int p_row) = 0;

protected:

	virtual void message(const std::string p_message) = 0;
	
};