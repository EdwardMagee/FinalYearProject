#pragma once

#include "GameInterface.h" 

class Scene;
class TextureHandler;

class GameOne : public GameInterface
{
private:

	Scene * m_currentScene;
	TextureHandler * m_textureHandler;

public:
	GameOne();
	~GameOne();
	void updateGame(float p_time) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleInput(int p_InputEvent) override;
	

};