#include "..\include\GameOne.h"
#include "..\include\Scene.h"
#include "..\include\TextureHandler.h"

#include<SFML\Graphics.hpp>

GameOne::GameOne(){
    m_textureHandler->instance()->insertTexture("Harold", "../VampiresVsKnights/Assests/Sprites/Harold.png");
	m_textureHandler->instance()->insertTexture("Owl", "../VampiresVsKnights/Assests/Sprites/Owl.jpg");
	m_textureHandler->instance()->insertTexture("Normal", "../VampiresVsKnights/Assests/Sprites/Normal.png");
	m_textureHandler->instance()->insertTexture("Empty", "../VampiresVsKnights/Assests/Sprites/Empty.png");
	m_textureHandler->instance()->insertTexture("space", "../VampiresVsKnights/Assests/Sprites/space.jpg");
	m_textureHandler->instance()->insertTexture("Bat", "../VampiresVsKnights/Assests/Sprites/Bat.png");
	m_textureHandler->instance()->insertTexture("Micheal", "../VampiresVsKnights/Assests/Sprites/Micheal.png");
	m_textureHandler->instance()->insertTexture("Slow", "../VampiresVsKnights/Assests/Sprites/Slow.png");
	m_textureHandler->instance()->insertTexture("Speed", "../VampiresVsKnights/Assests/Sprites/Speed.png");
	m_textureHandler->instance()->insertTexture("Splash", "../VampiresVsKnights/Assests/Sprites/Splash.png");
	m_textureHandler->instance()->insertTexture("Vampire", "../VampiresVsKnights/Assests/Sprites/Vampire.png");

	m_currentScene = new Scene();
	m_backgroundTexture = m_textureHandler->instance()->getTexture("space");
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(0.8, 0.8);
	m_over = false;
}

GameOne::~GameOne()
{
	delete m_currentScene;
	m_currentScene = nullptr;
}

void GameOne::updateGame(float p_time)
{
	m_currentScene->updateScene(p_time);

	if (m_currentScene->getGameOver())
	{
		m_over = true;
	}
}

void GameOne::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_backgroundSprite);

	for (auto object : m_currentScene->getSpriteVector())
	{
		target.draw(*object);
	}
}

void GameOne::handleInput(int p_InputEvent)
{
	switch (p_InputEvent)
	{
	case sf::Keyboard::Left:
		std::cout << "yes" << std::endl;
		m_currentScene->increaseCounter();
		break;
	case sf::Keyboard::Right:
		std::cout << "yes!!" << std::endl;
		m_currentScene->increaseOtherCounter();
		break;

	default:
		break;
	}

}

bool GameOne::isOver()
{
	return m_over;
}
