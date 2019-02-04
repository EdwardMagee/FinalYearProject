#include "..\include\GameOne.h"
#include "..\include\Scene.h"
#include "..\include\TextureHandler.h"

GameOne::GameOne(){
    m_textureHandler->instance()->insertTexture("Test", "../VampiresVsKnights/Assests/Sprites/Test.png");
	m_textureHandler->instance()->insertTexture("Owl", "../VampiresVsKnights/Assests/Sprites/Owl.jpg");
	m_currentScene = new Scene();
	
}

GameOne::~GameOne()
{
}

void GameOne::updateGame(float p_time)
{

}

void GameOne::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto object : m_currentScene->getSpriteVector())
	{
		target.draw(*object);
	}
}

void GameOne::handleInput(int p_InputEvent)
{
}
