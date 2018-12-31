#pragma once
#include <SFML/Graphics.hpp>

class Game : public sf::Drawable
{
private:


public:
	void UpdateGame(float time);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void HandleInput(int pInputEvent);
	

};