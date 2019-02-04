#pragma once
#include <SFML/Graphics.hpp>

class SpriteInterface : public sf::Drawable
{
private:


protected:

	virtual void update(float p_time) = 0;
	virtual void message(const std::string p_message) = 0;
	virtual sf::Sprite* getSprite() = 0;
};