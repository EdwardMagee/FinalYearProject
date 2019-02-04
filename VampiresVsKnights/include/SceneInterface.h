#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class SceneInterface 
{
private:


protected:
	virtual void updateScene(float p_time) = 0;
	virtual bool loadLevel(std::string p_level) = 0;
	virtual std::vector<sf::Sprite*> getSpriteVector() = 0;


};