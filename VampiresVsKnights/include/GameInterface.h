#pragma once
#include <SFML/Graphics.hpp>
#include "EndState.h"

class GameInterface : public sf::Drawable
{
private:


protected:
	virtual void updateGame(float p_time) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void handleInput(int p_InputEvent) = 0;
	virtual EndState isOver() = 0;
	virtual void loadLevel() = 0;

};