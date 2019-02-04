#pragma once

#include "SceneInterface.h"
#include "TextureHandler.h"

class Scene : public SceneInterface
{
private:
	sf::Sprite * temp;
	std::vector<sf::Sprite*> m_spriteVector;
	TextureHandler * m_textureHandler;

public:
	
	void updateScene(float p_time) override;
	bool loadLevel(std::string p_level) override;
	std::vector<sf::Sprite*> getSpriteVector() override;
	
	Scene();
	~Scene();

};